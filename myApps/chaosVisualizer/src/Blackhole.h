// Blackhole.h
#pragma once

#include "ofMain.h"
#include "Globals.h"

class Blackhole {
public:
    ofVec2f pos;
    float radius;
    int id;

	Blackhole() {};
    Blackhole(float x = 0, float y = 0, int id = 0);

    void display();
    void moveTo(float mx, float my);
    bool isMouseOver(int mouseX, int mouseY) const;
};
