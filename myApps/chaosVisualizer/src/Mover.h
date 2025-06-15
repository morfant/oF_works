// Mover.h
#pragma once
#include "ofMain.h"
#include "Blackhole.h"
#include "Seed.h"

class Mover {
public:
	static constexpr float VEL_LIMIT = 10.0f;
    ofVec2f pos, vel, acc;
    float diameter;
    float mass;
    float G;

	Mover() {};
    Mover(float x, float y, float m);

    void applyForce(const ofVec2f& force);
    void attract(const ofVec2f& target);
    void checkEdges(bool blocked);
    bool isCollidingWith(const Blackhole& b) const;
    Seed releaseSeed() const;
    void update();
    void draw();
};
