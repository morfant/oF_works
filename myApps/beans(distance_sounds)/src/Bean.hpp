//
//  Bean.hpp
//  beans
//
//  Created by Gang il Lee on 11/27/24.
//

#ifndef Bean_hpp
#define Bean_hpp

#include <stdio.h>
#include "ofMain.h"

class Bean{
private:
    ofVec2f center;
    ofVec2f position = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    ofVec2f velocity;
    float radius = 20;
    float timef = 0.f;
    float step = 0.1f;
    int direction = 1;
    float width = 50.f;
    int vh = 1;
    int fbo = 1;

public:
    Bean(ofVec2f center, float len, float step, int vh, int fbo);
    
    void update();
    void draw();
    void setStep(float f);
    
    static ofFbo fbo1, fbo2;


    
};

#endif /* Bean_hpp */
