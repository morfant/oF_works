//
//  Boid.cpp
//  flock
//
//  Created by giy on 2021/08/07.
//

#include "Boid.h"


Boid::Boid(float x, float y) {
    pos = glm::vec3(x, y, 0.f);
    float angle = ofRandom(TWO_PI);
    vel = glm::vec3(cos(angle), sin(angle), 0.f);
    acc = glm::vec3(0.f, 0.f, 0.f);
}

// https://openframeworks.cc/documentation/math/ofVec3f/#!show_limit
glm::vec3 Boid::limitMag(float f, glm::vec3 v) {
    float mag = glm::length(v);
    
    if (mag > f) {
        float ratio = f / mag;
        return v * ratio;
    } else {
        return v;
    }
    
}

void Boid::update() {
    vel = vel + acc;
    vel = limitMag(MAX_SPEED, vel);
    pos = pos + vel;
    acc = acc * 0.f;
    checkEdge();
}


void Boid::checkEdge() {
    if (pos.x > ofGetWidth()) {
        pos.x = 0.f;
    } else if (pos.x < 0) {
        pos.x = ofGetWidth();
    }
    
    if (pos.y > ofGetHeight()) {
        pos.y = 0.f;
    } else if (pos.y < 0) {
        pos.y = ofGetHeight();
    }
}

void Boid::draw() {

    ofPushMatrix();
    ofTranslate(pos.x, pos.y, pos.z);
    float angle = glm::atan(vel.y, vel.x);
    ofRotateRad(angle + PI/2);
    ofSetColor(255, 0, 100);
    ofFill();
    ofDrawTriangle(-5, 7, 5, 7, 0, -7);
    ofPopMatrix();
}


void Boid::run() {
    update();
    draw();
}

void Boid::run(std::vector<Boid> boids) {
    flock(boids);
    update();
    draw();
}

void Boid::flock(std::vector<Boid> boids) {
    glm::vec3 seq = seperate(boids);
    glm::vec3 ali = align(boids);
    glm::vec3 coh = cohesion(boids);
    
    seq = seq * 1.2f;
    ali = ali * 1.0f;
    coh = coh * 1.0f;
    
    applyForce(seq);
    applyForce(ali);
    applyForce(coh);
    
}

void Boid::applyForce(glm::vec3 f) {
    acc = acc + f;
}

glm::vec3 Boid::seperate(std::vector<Boid> boids) {
    float desiredSeperation = 20.f;
    glm::vec3 steer(0.f, 0.f, 0.f);
    int count = 0;
    
    for (std::vector<Boid>::iterator it = boids.begin(); it != boids.end(); it++) {
        float d = glm::distance(pos, (*it).pos);
        if (d > 0 && d < desiredSeperation) {
            glm::vec3 diff = pos - (*it).pos;
            diff = glm::normalize(diff);
            diff = diff / d;
            steer = steer + diff;
            count++;
        }
    }
    
    if (count > 0) {
        steer = steer / count;
    }
    
    if (glm::length(steer) > 0.f) {
        steer = glm::normalize(steer);
        steer = steer * MAX_SPEED;
        steer = steer - vel;
        steer = limitMag(MAX_FORCE, steer);
    }
    
    return steer;
    
}

glm::vec3 Boid::align(std::vector<Boid> boids) {
    float localCircleDistance = 25.f;
    glm::vec3 steer(0.f, 0.f, 0.f);
    int count = 0;
    
    for(std::vector<Boid>::iterator it = boids.begin(); it != boids.end(); it++) {
        float d = glm::distance(pos, (*it).pos);
        if (d > 0 && d < localCircleDistance ) {
            steer = steer + (*it).vel;
            count++;
        }
    }
    
    if (count > 0) {
        steer = steer / count;
        steer = glm::normalize(steer);
        steer = steer * MAX_SPEED;
        steer = steer - vel;
        steer = limitMag(MAX_FORCE, steer);
    }
    
    return steer;
    
}

glm::vec3 Boid::cohesion(std::vector<Boid> boids) {
    float localCircleDistance = 25.f;
    glm::vec3 steer(0.f, 0.f, 0.f);
    int count = 0;
    
    glm::vec3 avgPos(0.f, 0.f, 0.f);
    for(std::vector<Boid>::iterator it = boids.begin(); it != boids.end(); it++) {
        float d = glm::distance(pos, (*it).pos);
        if (d > 0 && d < localCircleDistance) {
            avgPos = avgPos + (*it).pos;
            count++;
        }
    }
    
    if (count > 0) {
        avgPos = avgPos / count;
        avgPos = glm::normalize(avgPos);
        avgPos = avgPos * MAX_SPEED;
        steer = avgPos - vel;
        steer = limitMag(MAX_FORCE, steer);
    }
    
    return steer;
    
}
