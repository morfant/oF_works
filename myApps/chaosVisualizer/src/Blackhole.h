// Blackhole.h
#pragma once

#include "ofMain.h"
#include "Globals.h"

class Blackhole {
public:
    ofVec2f pos;
    float radius;
    int id;
    float strength;   // ★ 각 블랙홀의 인력 세기 (Perlin 노이즈로 제어)


	Blackhole() {};
    Blackhole(float x = 0, float y = 0, int id = 0);

    void display();
    void moveTo(float mx, float my);
    bool isMouseOver(int mouseX, int mouseY) const;
};
