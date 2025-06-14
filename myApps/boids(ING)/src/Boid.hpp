//
//  Boid.hpp
//  Boids
//
//  Created by Gang il Lee on 2021/07/30.
//

#ifndef Boid_hpp
#define Boid_hpp

#include <stdio.h>
#include "ofMain.h"

class Boid {
    
    public:
        glm::vec3 pos, vel, acc;
        float rad = 10.f;
        float len = 20.f;
        ofConePrimitive cone;
        ofColor topCol = ofColor(155, 0, 100);
        ofColor capCol = ofColor(100, 100, 80);
    
    
    Boid() {
        cone.set( rad, len );
        cone.setTopColor(topCol);
        cone.setCapColor(capCol);
        pos = glm::vec3(0.f, 0.f, 0.f);
        acc = glm::vec3(0.f, 0.f, 0.f);
        vel = glm::vec3(0.f, 0.5f, 0.f);
    }
    
    
    void applyForce(glm::vec3 f);
    void update();
    void draw();
    
    
};

#endif /* Boid_hpp */
