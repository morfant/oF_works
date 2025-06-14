//
//  Boid.hpp
//  flock
//
//  Created by giy on 2021/08/07.
//

#ifndef Boid_h
#define Boid_h

#include <stdio.h>
#include "ofMain.h"

class Boid {
private:
    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec3 acc;
    float r = 20;
    float MAX_SPEED = 3.0f;
    float MAX_FORCE = 0.05f;
    
    
public:
    Boid(float x, float y);
    
    glm::vec3 limitMag(float f, glm::vec3 v);
    
    void update();
    void draw();
    void checkEdge();
    void run();
    void run(std::vector<Boid> boids);
    
    void applyForce(glm::vec3 f);
    glm::vec3 seperate(std::vector<Boid> boids);
    glm::vec3 align(std::vector<Boid> boids);
    glm::vec3 cohesion(std::vector<Boid> boids);
    void flock(std::vector<Boid> boids);
        
};

#endif /* Boid_hpp */

