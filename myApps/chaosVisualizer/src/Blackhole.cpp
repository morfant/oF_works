// Blackhole.cpp
#include "Blackhole.h"

Blackhole::Blackhole(float x, float y, int id)
: pos(x, y), radius(30), id(id) {}

void Blackhole::display() {
    ofSetColor(255, 0, 0, 100);
    ofDrawCircle(pos.x, pos.y, radius);
    ofSetColor(255);
    ofDrawBitmapString("#" + ofToString(id), pos.x - 10, pos.y);
}

void Blackhole::moveTo(float mx, float my) {
    pos.set(mx, my);
}

bool Blackhole::isMouseOver(int mouseX, int mouseY) const {
    return ofDist(mouseX, mouseY, pos.x, pos.y) < radius;
}
