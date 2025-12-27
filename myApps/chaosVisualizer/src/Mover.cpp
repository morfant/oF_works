// Mover.cpp
#include "Mover.h"
#include "Blackhole.h"
#include "Seed.h"
#include "ofMain.h"

static ofVec2f computeBlackholeForceAt(const ofVec2f& position,
	const std::vector<Blackhole>& blackholes,
	float forceBaseScale) {
	ofVec2f totalForce(0, 0);

	for (const auto & b : blackholes) {
		ofVec2f dir = b.pos - position;
		float distSq = dir.lengthSquared();
		float minDist = 1.0f;
		if (distSq < minDist * minDist) {
			distSq = minDist * minDist;
		}
		if (distSq > 0.0001f) {
			dir.normalize();
			float base = (10.0f * forceBaseScale) / distSq;
			float s = b.strength;
			totalForce += dir * base * s;
		}
	}

	return totalForce;
}

Mover::Mover(float x, float y, float m)
    : pos(x, y), vel(ofRandom(-1, 1), ofRandom(-1, 1)), acc(0, 0), diameter(40), mass(m) {
	if (USE_SOFT_BODY) {
		initSoftBody(SOFT_POINT_COUNT, diameter * 0.5f);
	}
}

void Mover::setPosition(const ofVec2f& newPos) {
	ofVec2f delta = newPos - pos;
	pos = newPos;
	if (USE_SOFT_BODY && !softPoints.empty()) {
		translateSoftPoints(delta);
		syncCenterFromSoftPoints();
	}
}
            
void Mover::applyForce(const ofVec2f& force) {
	if (USE_SOFT_BODY && !softPoints.empty()) {
		ofVec2f perPoint = force / mass;
		for (auto & p : softPoints) {
			p.acc += perPoint;
		}
		return;
	}
    acc += force / mass;
}

void Mover::applyBlackholeForce(const std::vector<Blackhole>& blackholes, float forceBaseScale) {
	if (USE_SOFT_BODY && !softPoints.empty()) {
		for (auto & p : softPoints) {
			ofVec2f force = computeBlackholeForceAt(p.pos, blackholes, forceBaseScale);
			p.acc += force / mass;
		}
		return;
	}

	ofVec2f totalForce = computeBlackholeForceAt(pos, blackholes, forceBaseScale);
	applyForce(totalForce);
}

void Mover::attract(const ofVec2f& target) {
    ofVec2f force = target - pos;
    float distance = ofClamp(force.length(), 5, 25);
    force.normalize();
    float strength = (G * mass) / (distance * distance);
    applyForce(force * strength);
}

void Mover::checkEdges(bool blocked) {
    float radius = diameter * 0.5;
    if (!blocked) {
        if (pos.x - radius > width) pos.x = 0 - radius;
        else if (pos.x + radius < 0) pos.x = width + radius;

        if (pos.y - radius > height) pos.y = 0 - radius;
        else if (pos.y + radius < 0) pos.y = height + radius;
    } else {
        if (pos.x + radius >= width) {
            pos.x = width - radius;
            vel.x *= -1;
        } else if (pos.x - radius <= 0) {
            pos.x = radius;
            vel.x *= -1;
        }

        if (pos.y + radius >= height) {
            pos.y = height - radius;
            vel.y *= -1;
        } else if (pos.y - radius <= 0) {
            pos.y = radius;
            vel.y *= -1;
        }
    }
}

// 원형 경계 안에서 튕기기 (Ball::bounceOnCircleBoundary 에서 가져온 로직)
void Mover::bounceOnCircleBoundary(const ofVec2f& center, float R) {
	if (USE_SOFT_BODY && !softPoints.empty()) {
		for (auto & p : softPoints) {
			ofVec2f d = p.pos - center;
			float dist = d.length();

			if (dist > R) {
				if (dist == 0.0f) {
					continue;
				}
				ofVec2f n = d / dist;
				float dot = p.vel.dot(n);
				p.vel = p.vel - 2.0f * dot * n;
				p.pos = center + n * R;
			}
		}
		syncCenterFromSoftPoints();
		return;
	}

    ofVec2f d = pos - center;
    float dist = d.length();
    float radius = diameter * 0.5f;

    if (dist > R - radius) {
        if (dist == 0.0f) return;
        ofVec2f n = d / dist;
        float dot = vel.dot(n);
        // 속도를 법선 방향 기준으로 반사
        vel = vel - 2.0f * dot * n;
        // 경계선 안쪽으로 위치 보정
        pos = center + n * (R - radius);
    }
}

// 다른 Mover 와의 충돌 처리 (Ball::collideWith 에서 가져온 로직)
bool Mover::collideWith(Mover& other, float correctionFactor) {
    ofVec2f d = other.pos - pos;
    float dist = d.length();
    float r1 = diameter * 0.5f;
    float r2 = other.diameter * 0.5f;
    float minDist = r1 + r2;
    if (dist == 0.0f) return false;

    if (dist < minDist) {
        ofVec2f n = d / dist;

        // 1) 겹침(overlap) 해소
        float overlap = minDist - dist;
        float correction = overlap * correctionFactor;

        ofVec2f correctionVec = n * (correction * 0.5f);
        pos       -= correctionVec;
        other.pos += correctionVec;
		if (USE_SOFT_BODY && !softPoints.empty()) {
			translateSoftPoints(-correctionVec);
			syncCenterFromSoftPoints();
		}
		if (USE_SOFT_BODY && !other.softPoints.empty()) {
			other.translateSoftPoints(correctionVec);
			other.syncCenterFromSoftPoints();
		}

        // 2) 속도 반사 (동일 질량, 탄성 충돌)
        ofVec2f dv = vel - other.vel;
        float vn = dv.dot(n);

        // 서로 멀어지는 중이면 추가 충돌 처리 안 함 (p5.js 코드와 동일한 조건)
        if (vn > 0.0f) {
            return true; // still count as collision because we resolved overlap
        }

        float impulse = vn; // 동일 질량, e = 1

        ofVec2f impulseVec = impulse * n;
        vel       -= impulseVec;
        other.vel += impulseVec;
		if (USE_SOFT_BODY && !softPoints.empty()) {
			applyVelocityToSoftPoints(-impulseVec);
			syncCenterFromSoftPoints();
		}
		if (USE_SOFT_BODY && !other.softPoints.empty()) {
			other.applyVelocityToSoftPoints(impulseVec);
			other.syncCenterFromSoftPoints();
		}
        return true;
    }

    return false;
}

bool Mover::isCollidingWith(const Blackhole& b) const {
    return (pos.distance(b.pos) < (diameter / 2 + b.radius));
}

Seed Mover::releaseSeed() const {
    return Seed(pos.x, pos.y);
}

void Mover::warp()
{
	setPosition(ofVec2f(ofRandom(width), ofRandom(height)));
}

void Mover::update() {
	if (USE_SOFT_BODY && !softPoints.empty()) {
		updateSoftBody();
		return;
	}

    vel += acc;
    vel.limit(Mover::VEL_LIMIT);
    pos += vel;
    acc.set(0, 0);
    // checkEdges(false);
}

void Mover::draw(bool dot) {
	ofFill();

	if (USE_SOFT_BODY && !softPoints.empty()) {
		drawSoftBody(dot);
		return;
	}

    if (!dot)
    {
        ofSetColor(90, 134, 124, 150);
        ofDrawCircle(pos, diameter * 0.5);

        ofSetColor(90, 84, 84, 250);
        ofDrawCircle(pos, diameter * 0.25);
    }
    else
    {
        ofSetColor(255, 200, 10);
        ofDrawCircle(pos, diameter * 0.5);
    }

}

void Mover::initSoftBody(int segments, float radius) {
	softPoints.clear();
	softPoints.reserve(segments);
	softRestRadius = radius;

	for (int i = 0; i < segments; ++i) {
		float angle = TWO_PI * (static_cast<float>(i) / static_cast<float>(segments));
		ofVec2f p = pos + ofVec2f(cos(angle), sin(angle)) * radius;
		SoftPoint pt;
		pt.pos = p;
		pt.vel.set(0, 0);
		pt.acc.set(0, 0);
		softPoints.push_back(pt);
	}
	syncCenterFromSoftPoints();
}

void Mover::updateSoftBody() {
	if (softPoints.size() < 3) {
		return;
	}

	const int count = static_cast<int>(softPoints.size());
	ofVec2f center(0, 0);
	for (const auto & p : softPoints) {
		center += p.pos;
	}
	center /= static_cast<float>(count);

	float restLen = 2.0f * softRestRadius * sin(PI / static_cast<float>(count));

	for (int i = 0; i < count; ++i) {
		SoftPoint & p = softPoints[i];
		SoftPoint & next = softPoints[(i + 1) % count];

		ofVec2f edge = next.pos - p.pos;
		float dist = edge.length();
		if (dist > 0.0001f) {
			ofVec2f n = edge / dist;
			float stretch = dist - restLen;
			ofVec2f force = n * (SOFT_EDGE_K * stretch);
			p.acc += force;
			next.acc -= force;
		}

		ofVec2f toCenter = center - p.pos;
		float distCenter = toCenter.length();
		if (distCenter > 0.0001f) {
			ofVec2f n = toCenter / distCenter;
			float stretch = distCenter - softRestRadius;
			p.acc += n * (SOFT_CENTER_K * stretch);
		}
	}

	for (auto & p : softPoints) {
		p.vel += p.acc;
		p.vel *= SOFT_DAMPING;
		p.vel.limit(Mover::VEL_LIMIT);
		p.pos += p.vel;
		p.acc.set(0, 0);
	}

	syncCenterFromSoftPoints();
}

void Mover::drawSoftBody(bool dot) {
	if (softPoints.size() < 3) {
		return;
	}

	int count = static_cast<int>(softPoints.size());
	if (dot) {
		ofSetColor(255, 200, 10);
	} else {
		ofSetColor(90, 134, 124, 150);
	}

	ofBeginShape();
	for (int i = 0; i < count + 3; ++i) {
		const auto & p = softPoints[i % count].pos;
		ofCurveVertex(p.x, p.y);
	}
	ofEndShape(true);

	if (!dot) {
		ofSetColor(90, 84, 84, 250);
		ofDrawCircle(pos, diameter * 0.25f);
	}
}

void Mover::translateSoftPoints(const ofVec2f& delta) {
	for (auto & p : softPoints) {
		p.pos += delta;
	}
}

void Mover::applyVelocityToSoftPoints(const ofVec2f& delta) {
	for (auto & p : softPoints) {
		p.vel += delta;
	}
}

void Mover::syncCenterFromSoftPoints() {
	if (softPoints.empty()) {
		return;
	}

	ofVec2f center(0, 0);
	ofVec2f avgVel(0, 0);
	for (const auto & p : softPoints) {
		center += p.pos;
		avgVel += p.vel;
	}
	center /= static_cast<float>(softPoints.size());
	avgVel /= static_cast<float>(softPoints.size());

	pos = center;
	vel = avgVel;
}
