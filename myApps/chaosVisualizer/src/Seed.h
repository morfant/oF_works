// Seed.h
#pragma once
#include "ofMain.h"
#include "Blackhole.h"
#include "Grid.h"

class Seed {
public:
	static int nextID; // 전역 ID 증가용
    int id;
	bool done = false;

	static constexpr float VEL_LIMIT = 15.0f;
    ofVec2f pos, vel, acc;
    float radius;
    ofColor col;
    float mass;
    float G;

	Seed() {};
    Seed(float x, float y);

    void applyForce(const ofVec2f& force);
    void attract(const ofVec2f& target);
    void checkEdges();
    bool isCollidingWith(const Blackhole& b);
    bool revealGridCell(Grid& grid, float threshold);
	void update();
	bool update(const std::vector<Blackhole> &blackholes, Grid &grid, float sitThreshold);

    void display();
    bool isOffscreen();
	bool isDone() const;
    void destroy();
};
