// Mover.h
#pragma once
#include "ofMain.h"
#include "Blackhole.h"
#include "Seed.h"

class Mover {
public:
	static constexpr float VEL_LIMIT = 5.0f;
    ofVec2f pos, vel, acc;
    float diameter;
    float mass;
    float G;

	Mover() {};
    Mover(float x, float y, float m);

    void applyForce(const ofVec2f& force);
    void attract(const ofVec2f& target);
    void checkEdges(bool blocked);
    void bounceOnCircleBoundary(const ofVec2f& center, float R);
    bool collideWith(Mover& other, float correctionFactor);
    bool isCollidingWith(const Blackhole& b) const;
    Seed releaseSeed() const;
	void warp();
    void update();
    void draw(bool dot);
};
