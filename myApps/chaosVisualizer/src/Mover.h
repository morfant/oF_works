// Mover.h
#pragma once
#include "ofMain.h"
#include "Blackhole.h"
#include "Seed.h"

struct SoftPoint {
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f acc;
};

class Mover {
public:
	static constexpr float VEL_LIMIT = 5.0f;
	static constexpr bool USE_SOFT_BODY = true;
	static constexpr int SOFT_POINT_COUNT = 24;
	static constexpr float SOFT_EDGE_K = 0.25f;
	static constexpr float SOFT_CENTER_K = 0.15f;
	static constexpr float SOFT_DAMPING = 0.96f;
	ofVec2f pos, vel, acc;
    float diameter;
    float mass;
    float G;

	Mover() {};
    Mover(float x, float y, float m);

	void setPosition(const ofVec2f& newPos);
    void applyForce(const ofVec2f& force);
	void applyBlackholeForce(const std::vector<Blackhole>& blackholes, float forceBaseScale);
    void attract(const ofVec2f& target);
    void checkEdges(bool blocked);
    void bounceOnCircleBoundary(const ofVec2f& center, float R);
    bool collideWith(Mover& other, float correctionFactor);
    bool isCollidingWith(const Blackhole& b) const;
    Seed releaseSeed() const;
	void warp();
    void update();
    void draw(bool dot);

private:
	std::vector<SoftPoint> softPoints;
	float softRestRadius = 0.0f;

	void initSoftBody(int segments, float radius);
	void updateSoftBody();
	void drawSoftBody(bool dot);
	void translateSoftPoints(const ofVec2f& delta);
	void applyVelocityToSoftPoints(const ofVec2f& delta);
	void syncCenterFromSoftPoints();
};
