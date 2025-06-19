#include "ofMain.h"

class AttractorPoint {
public:
    float initX, initY;
    ofVec2f pos;
    ofVec2f prevPos;
    float a, b, c, d;
    bool hasPrev = false;

    AttractorPoint(float initX_, float initY_, float _a, float _b, float _c, float _d) {
        initX = initX_;
        initY = initY_;
        pos.set(initX, initY);
        a = _a; b = _b; c = _c; d = _d;
    }

    void setParams(float a_, float b_, float c_, float d_)
    {
        a = a_;
        b = b_;
        c = c_;
        d = d_;
    }


    void resetPos()
    {
        if (abs(pos.x) > 2 || abs(pos.y) > 2) {
            pos.set(ofRandom(-1, 1), ofRandom(-1, 1));
            prevPos.set(0, 0);
            hasPrev = false;
        }
    }

    void update() {
        prevPos = pos;
        float nextX = sin(b * pos.y) + c * sin(b * pos.x);
        float nextY = sin(a * pos.x) + d * sin(a * pos.y);
        // float px = ofMap(nextX, -2, 2, -ofGetWidth()/2, ofGetWidth()/2);
        // float py = ofMap(nextY, -2, 2, -ofGetHeight()/2, ofGetHeight()/2);

        // ofPushMatrix();
        // ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        // ofDrawCircle(px, py, 1.0);  // ATTR_RAD
        // ofPopMatrix();

        pos.set(nextX, nextY);
		// prevPos.x = px;
		// prevPos.y = py;
		// pos.x = nextX;
		// pos.y = nextY;

        hasPrev = true;

        // if (pos.x < -2 || pos.x > 2 || pos.y < -2 || pos.y > 2) {
        //     ofLog() << "Out of bounds: " << pos;
        // }
    }

    void draw(bool useLines) {
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        float px = ofMap(pos.x, -2, 2, -ofGetWidth()/2, ofGetWidth()/2);
        float py = ofMap(pos.y, -2, 2, -ofGetHeight()/2, ofGetHeight()/2);

        if (useLines && hasPrev) {
            float prevX = ofMap(prevPos.x, -2, 2, -ofGetWidth()/2, ofGetWidth()/2);
            float prevY = ofMap(prevPos.y, -2, 2, -ofGetHeight()/2, ofGetHeight()/2);
            ofDrawLine(prevX, prevY, px, py);
        } else {
            ofSetColor(0, 100, 100);
            ofDrawCircle(px, py, 1.0);  // ATTR_RAD
        }

        ofPopMatrix();
    }
};