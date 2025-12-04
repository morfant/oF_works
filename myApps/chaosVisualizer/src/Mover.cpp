// Mover.cpp
#include "Mover.h"
#include "Blackhole.h"
#include "Seed.h"
#include "ofMain.h"

Mover::Mover(float x, float y, float m)
    : pos(x, y), vel(ofRandom(-1, 1), ofRandom(-1, 1)), acc(0, 0), diameter(40), mass(m) {}

void Mover::applyForce(const ofVec2f& force) {
    acc += force / mass;
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

        pos       -= n * (correction * 0.5f);
        other.pos += n * (correction * 0.5f);

        // 2) 속도 반사 (동일 질량, 탄성 충돌)
        ofVec2f dv = vel - other.vel;
        float vn = dv.dot(n);

        // 서로 멀어지는 중이면 추가 충돌 처리 안 함 (p5.js 코드와 동일한 조건)
        if (vn > 0.0f) {
            return true; // still count as collision because we resolved overlap
        }

        float impulse = vn; // 동일 질량, e = 1

        vel       -= impulse * n;
        other.vel += impulse * n;
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
	pos.x = ofRandom(width);
	pos.y = ofRandom(height);
}

void Mover::update() {
    vel += acc;
    vel.limit(Mover::VEL_LIMIT);
    pos += vel;
    acc.set(0, 0);
    // checkEdges(false);
}

void Mover::draw(bool dot) {
	ofFill();

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
        ofDrawCircle(pos, diameter * 0.05);
    }

}
