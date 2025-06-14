//
//  Rectangle.hpp
//  cam_mesh_class
//
//  Created by giy on 2021/11/30.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <stdio.h>
#include "ofMain.h"

class Rectangle {
    
    float x, y;
    float width, height;
    int num_x = 32, num_y = 28;
    float step_x, step_y;
    
public:
    Rectangle();
    Rectangle(float _x, float _y): x(_x), y(_y) {};

    void setup(float, float, float, float, int, int);
    void setup(int, int);
    void setMode(ofPrimitiveMode mode);
    void update();
    void draw(ofPixelsRef);
    void drawMesh();
    
    ofMesh mesh;
    
};


#endif /* Rectangle_hpp */
