// Seed.cpp
#include "Seed.h"


int Seed::nextID = 0;

Seed::Seed(float x, float y) {
	id = nextID++;
	pos.set(x, y);
	vel.set(0, 0);
	acc.set(0, 0);
	radius = 6;
	col.set(255, 255, 150, 180);
	mass = 0.1f;
	G = 20.0f;
}

void Seed::applyForce(const ofVec2f & force) {
	ofVec2f f = force / mass;
	acc += f;
}

void Seed::attract(const ofVec2f & target) {
	ofVec2f force = target - pos;
	float distance = ofClamp(force.length(), 5, 25);
	force.normalize();
	float strength = (G * mass) / (distance * distance);
	force *= strength;
	applyForce(force);
}

void Seed::checkEdges() {
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

bool Seed::isCollidingWith(const Blackhole & b) {
	float d = (pos - b.pos).length();
	return d < (radius + b.radius);
}

bool Seed::revealGridCell(Grid & grid, float threshold) {
	return grid.revealNearestCell(pos.x, pos.y, threshold);
}

void Seed::update() {
	vel += acc;
	vel.limit(VEL_LIMIT);
	pos += vel;
	acc.set(0, 0);
	checkEdges();
}

bool Seed::update(const std::vector<Blackhole> & blackholes, Grid & grid, float sitThreshold) {
	// 블랙홀에 인력 받기
	const Blackhole * nearest = nullptr;
	float minDist = FLT_MAX;

	for (const auto & b : blackholes) {
		float d = ofDist(pos.x, pos.y, b.pos.x, b.pos.y);
		if (d < minDist) {
			minDist = d;
			nearest = &b;
		}

		// 충돌 감지 → 제거
		if (isCollidingWith(b)) {
			return true; // erase 필요
		}
	}

	if (nearest) attract(nearest->pos);

	// 움직임 업데이트
	this->update(); // 내부 pos/vel 갱신용

	if (isOffscreen() || revealGridCell(grid, sitThreshold)) {
		done = true;
		return true;
	}

	// if (revealGridCell(grid, sitThreshold)) return true;

	// if (isOffscreen()) return true;

	return false;
}

void Seed::display() {
	// dot
	// ofSetColor(col);
	// ofDrawCircle(pos.x, pos.y, radius);

	// like a mover
	int diameter = 40;
	ofSetColor(90, 134, 124, 150);
	ofDrawCircle(pos, diameter * 0.5);

	ofSetColor(90, 84, 84, 250);
	ofDrawCircle(pos, diameter * 0.25);
}

bool Seed::isOffscreen() {
	return pos.x < -radius || pos.x > width + radius || pos.y < -radius || pos.y > height + radius;
}

bool Seed::isDone() const {
	return done;
}

void Seed::destroy() {
	ofLog() << "Seed destroyed at: " << pos;
}
