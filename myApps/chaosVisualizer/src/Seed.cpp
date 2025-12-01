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
	// 질량에 따라 가속도가 달라지도록 mass를 strength에서 제거
	float strength = G / (distance * distance);
	force *= strength;
	applyForce(force);
}

void Seed::checkEdges() {
	bool heavy = (mass > 1.0f);

	if (pos.x + radius >= width) {
		pos.x = width - radius;
		vel.x *= -1;
	} else if (pos.x - radius <= 0) {
		pos.x = radius;
		vel.x *= -1;
	}

	if (pos.y + radius >= height) {
		pos.y = height - radius;
		if (heavy) {
			// 무거운 시드는 바닥에서 멈춤
			vel.y = 0;
		} else {
			vel.y *= -1;
		}
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
	// 질량이 크면 아래로 향하는 "중력"을 추가
	if (mass > 1.0f) {
		float t = ofClamp(mass, 1.0f, 2.0f);
		float g = ofMap(t, 1.0f, 2.0f, 0.1f, 1.5f, true);
		acc.y += g;
	}

	vel += acc;
	// 질량에 따라 최대 속도도 달라지도록 조정 (0.01 ~ 2.0)
	float maxVel = ofMap(mass, 0.01f, 2.0f, 30.0f, 3.0f, true);
	vel.limit(maxVel);
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
	// 질량에 따라 색 농도(알파)와 크기를 더 극적으로 변화
	float t = ofClamp(mass, 0.01f, 2.0f);
	float tn = ofMap(t, 0.01f, 2.0f, 0.0f, 1.0f, true);

	int alphaOuter = ofMap(tn, 0.0f, 1.0f, 40, 255, true);
	int alphaInner = ofMap(tn, 0.0f, 1.0f, 80, 255, true);
	float diameter = ofMap(tn, 0.0f, 1.0f, 20.0f, 90.0f, true);

	ofSetColor(90, 134, 124, alphaOuter);
	ofDrawCircle(pos, diameter * 0.5f);

	ofSetColor(90, 84, 84, alphaInner);
	ofDrawCircle(pos, diameter * 0.25f);
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
