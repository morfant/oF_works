//
//  Circle.hpp
//  MovementInAGrid
//
//  Created by Gang il Lee on 1/2/25.
//

#ifndef Circle_hpp
#define Circle_hpp

#include <stdio.h>
#include "ofMain.h"

class Circle{
    
private:
    int posX, posY;
    float shiftX, shiftY;
    float radius;
    float lineWidth;
    
    
public:
    Circle(int x, int y, float r);
    void draw();
    void setRadius(float r);
    void setShift(float x, float y);
    void setLineWidth(float w);

};


#endif /* Circle_hpp */
