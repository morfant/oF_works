//
//  Rectangle.cpp
//  cam_mesh_class
//
//  Created by giy on 2021/11/30.
//

#include "Rectangle.hpp"

Rectangle::Rectangle() {
}



void Rectangle::setup(int camWidth, int camHeight) {
    
    step_x = camWidth / num_x;
    step_y = camHeight / num_y;
    
    for (int y = 0; y < num_y; ++y) {
        for (int x = 0; x < num_x; ++x) {
            mesh.addVertex(ofPoint(x * step_x, y * step_y, 0));
            mesh.addColor(ofColor(255, 255, 255));
        }
    }
}



void Rectangle::setMode(ofPrimitiveMode mode) {
    mesh.setMode(mode);
}



void Rectangle::update() {
    
    for (int y = 0; y < num_y - 1; ++y) {
        for (int x = 0; x < num_x - 1; ++x) {
            mesh.addIndex(x + (y * num_x));
            mesh.addIndex((x + 1) + (y * num_x));
            mesh.addIndex(x + (num_x * (y + 1)));
            
            mesh.addIndex((x + 1) + (y * num_x));
            mesh.addIndex((x + 1) + (num_x * (y + 1)));
            mesh.addIndex(x + (num_x * (y + 1)));
        }
    }
    
}



void Rectangle::draw(ofPixelsRef pixelsRef) {
    
     for (int y = 0; y < num_y; ++y) {
         for (int x = 0; x < num_x; ++x) {
             
             int xPos = x * step_x;
             int yPos = y * step_y;
             
             // get the pixel and its lightness (lightness is the average of its RGB values)
             float lightness = pixelsRef.getColor(xPos,yPos).getLightness();
             
             int idx = x + (num_x * (num_y - 1 - y));
             //            int idx = x + (num_x * y);
             ofPoint v = mesh.getVertex(idx);
             
             v.z = lightness;
             mesh.setVertex(idx, v);
             ofColor c(v.z, 100 + v.z/2, 120);
             mesh.setColor(idx, c);
             
         }
     }
    
}



void Rectangle::drawMesh() {
    
    ofPushMatrix();
    ofTranslate(x, y);
    mesh.draw();
    ofPopMatrix();
}
