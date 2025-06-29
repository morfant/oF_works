#pragma once
#include "ofMain.h"

class AttractorPoint {
public:
    float initX, initY;
    ofVec2f pos;
    ofVec2f prevPos;

	ofVec2f targetPos;
	float convergeAmount = 0.0f;  // 0.0 = pure chaos, 1.0 = full convergence

    float a, b, c, d;
    bool hasPrev = false;
	bool goingToTarget = false;

    AttractorPoint(float initX_, float initY_, float _a, float _b, float _c, float _d) {
        initX = initX_;
        initY = initY_;
        pos.set(initX, initY);
        a = _a; b = _b; c = _c; d = _d;
    }

    void setParams(float a_, float b_, float c_, float d_) {
        a = a_;
        b = b_;
        c = c_;
        d = d_;
    }

    void resetPos() {
        if (abs(pos.x) > 2.0 || abs(pos.y) > 2.0) {
            pos.set(ofRandom(-0.001, 0.001), ofRandom(-0.001, 0.001));
            prevPos.set(0, 0);
            hasPrev = false;
        }
    }

    void update() {
		if (convergeAmount > 0)
		{
			goingToTarget = true;
		}
		else
		{
			goingToTarget = false;
		}

        prevPos = pos;

        float nextX = sin(b * pos.y) + c * sin(b * pos.x);
        float nextY = sin(a * pos.x) + d * sin(a * pos.y);
		ofVec2f chaoticPos(nextX, nextY);

		if (goingToTarget)
		{
			// 점차적으로 targetPos로 수렴
			pos = chaoticPos * (1.0 - convergeAmount) + targetPos * convergeAmount;
		}
		else {
			pos = chaoticPos;
		}

        hasPrev = true;
    }

    void draw(bool useLines) {
        float px = ofMap(pos.x, -2, 2, -ofGetWidth() / 2, ofGetWidth() / 2);
        float py = ofMap(pos.y, -2, 2, -ofGetHeight() / 2, ofGetHeight() / 2);

        if (useLines && hasPrev) {
            float prevX = ofMap(prevPos.x, -2, 2, -ofGetWidth() / 2, ofGetWidth() / 2);
            float prevY = ofMap(prevPos.y, -2, 2, -ofGetHeight() / 2, ofGetHeight() / 2);
            ofDrawLine(prevX, prevY, px, py);
        } else {
			// ofSetColor(100, 100, 200);
			ofSetColor(255);
            ofDrawCircle(px, py, 1.0);
        }
    }
};
