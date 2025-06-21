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
    checkEdges(false);
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
