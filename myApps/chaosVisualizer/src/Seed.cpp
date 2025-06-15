// Seed.cpp
#include "Seed.h"

Seed::Seed(float x, float y) {
    pos.set(x, y);
    vel.set(0, 0);
    acc.set(0, 0);
    radius = 6;
    col.set(255, 255, 150, 180);
    mass = 0.1f;
    G = 20.0f;
}

void Seed::applyForce(const ofVec2f& force) {
    ofVec2f f = force / mass;
    acc += f;
}

void Seed::attract(const ofVec2f& target) {
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

bool Seed::isCollidingWith(const Blackhole& b) {
    float d = (pos - b.pos).length();
    return d < (radius + b.radius);
}

bool Seed::revealGridCell(Grid& grid, float threshold) {
    return grid.revealNearestCell(pos.x, pos.y, threshold);
}

void Seed::update() {
    vel += acc;
    vel.limit(VEL_LIMIT);
    pos += vel;
    acc.set(0, 0);
    checkEdges();
}

void Seed::display() {
    ofSetColor(col);
    ofDrawCircle(pos.x, pos.y, radius);
}

bool Seed::isOffscreen() {
    return pos.x < -radius || pos.x > width + radius || pos.y < -radius || pos.y > height + radius;
}

void Seed::destroy() {
    ofLog() << "Seed destroyed at: " << pos;
}
