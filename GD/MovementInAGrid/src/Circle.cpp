//
//  Circle.cpp
//  MovementInAGrid
//
//  Created by Gang il Lee on 1/2/25.
//

#include "Circle.hpp"
Circle::Circle(int x, int y, float r)
{
    posX = x;
    posY = y;
    radius = r;
    lineWidth = 2;
}

void Circle::draw()
{
    ofEnableSmoothing();
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofSetLineWidth(lineWidth);
    ofDrawCircle(posX + shiftX, posY + shiftY, radius);
}

void Circle::setRadius(float r)
{
    radius = r;
}

void Circle::setLineWidth(float w)
{
    lineWidth = w;
}

void Circle::setShift(float x, float y)
{
    shiftX = x;
    shiftY = y;
}


