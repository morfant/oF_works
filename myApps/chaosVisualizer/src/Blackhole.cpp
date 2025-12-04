// Blackhole.cpp
#include "Blackhole.h"

Blackhole::Blackhole(float x, float y, int id)
	: pos(x, y)
	, radius(30)
	, id(id)
	, strength(1.0) { }

void Blackhole::display() {

	// strength 값으로 반지름 결정하고 그리는 부분 (예시)
	float sAbs       = fabs(strength);
	float sClamped = ofClamp(sAbs, 0.0f, 10.0f);
	float baseRadius = 4.0f;
	float maxRadius = 22.0f;
	float r = ofMap(sClamped, 0.0f, 10.0f, baseRadius, maxRadius, true);

	if (strength < 0) {
		ofSetColor(120, 100, 255, 200); // repulsive
	} else {
		ofSetColor(255, 120, 120, 200); // attractive
	}
	ofFill();
	ofDrawCircle(pos, r);

	// ofNoFill();
	// ofSetColor(255, 60, 60, 220);
	// ofSetLineWidth(1.8f);
	// ofDrawCircle(pos, r + 2.0f);

	ofSetColor(255);
	ofDrawBitmapString("#" + ofToString(id), pos.x - 10, pos.y);

	// strength 값 텍스트 (id 아래 줄에 표시)
	std::string strengthLabel = "s: " + ofToString(strength, 2); // 소수점 둘째자리
	ofDrawBitmapString(strengthLabel,
		pos.x - 20,
		pos.y + 14); // y를 약간 내려서 id 아래에
}

void Blackhole::moveTo(float mx, float my) {
	pos.set(mx, my);
}

bool Blackhole::isMouseOver(int mouseX, int mouseY) const {
	return ofDist(mouseX, mouseY, pos.x, pos.y) < radius;
}
