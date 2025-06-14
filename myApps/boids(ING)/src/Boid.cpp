//
//  Boid.cpp
//  Boids
//
//  Created by Gang il Lee on 2021/07/30.
//

#include "Boid.hpp"

void Boid::applyForce(glm::vec3 f) {
    
    acc = acc + f;
}

void Boid::update() {
    
    vel = vel + acc;
    pos = pos + vel;
    
}

void Boid::draw() {
    ofPushMatrix();
    ofTranslate(pos);
    cone.draw();
    ofPopMatrix();
}
