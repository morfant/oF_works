//
//  Agent.cpp
//  noiseMotion
//
//  Created by Gang il Lee on 12/24/24.
//

#include "Agent.hpp"


Agent::Agent()
{
    p = glm::vec3(0, 0, 0);
    setRandomPosition();
    offset = 10000;
    stepSize = ofRandom(1, 8);
    float r = ofRandom(1.0);
    
    if (r < 0.4) col = ofVec3f(ofRandom(190,200), ofRandom(80,100), ofRandom(50,70));
    else if (r < 0.5) col = ofVec3f(52, 100, ofRandom(50,80));
    else col = ofVec3f(273, ofRandom(50,80), ofRandom(40,60));
    
    strokeW = ofRandom(1.0);
    offsetVelocity = 0.05;
    ribbon = new Ribbon3d(p, (int)ofRandom(50, 150));
}

void Agent::update1()
{
    angleY = fractalNoise
    (p.x / noiseScale, p.y / noiseScale, p.z / noiseScale, octave, falloff) * noiseStrength;
    angleZ = fractalNoise
    ( p.x / noiseScale + offset, p.y / noiseScale, p.z / noiseScale, octave, falloff) * noiseStrength;
    
    p.x += cos(angleZ) * cos(angleY) * stepSize;
    p.y += sin(angleZ) * stepSize;
    p.z += cos(angleZ) * sin(angleY) * stepSize;
    
    if (p.x < -spaceSizeX || p.x > spaceSizeX ||
        p.y < -spaceSizeY || p.y > spaceSizeY ||
        p.z < -spaceSizeZ || p.z > spaceSizeZ)
    {
        setRandomPosition();
        isOutside = true;
    }
    
    ribbon->update(p, isOutside);
    isOutside = false;
    
}

void Agent::update2(){
    angleY = fractalNoise
    (p.x / noiseScale, p.y / noiseScale, p.z / noiseScale, octave, falloff) * noiseStrength;
    angleZ = fractalNoise
    ( p.x / noiseScale + offset, p.y / noiseScale, p.z / noiseScale, octave, falloff) * noiseStrength;
    
    p.x += cos(angleZ) * cos(angleY) * stepSize;
    p.y += sin(angleZ) * stepSize;
    p.z += cos(angleZ) * sin(angleY) * stepSize;
    

    // boundingbox wrap
    if(p.x<-spaceSizeX) {
        p.x=spaceSizeX;
        isOutside = true;
    }
    if(p.x>spaceSizeX) {
        p.x=-spaceSizeX;
        isOutside = true;
    }
    if(p.y<-spaceSizeY) {
        p.y=spaceSizeY;
        isOutside = true;
    }
    if(p.y>spaceSizeY) {
        p.y=-spaceSizeY;
        isOutside = true;
    }
    if(p.z<-spaceSizeZ) {
        p.z=spaceSizeZ;
        isOutside = true;
    }
    if(p.z>spaceSizeZ) {
        p.z=-spaceSizeZ;
        isOutside = true;
    }

    // create ribbons
    ribbon->update(p, isOutside);
    isOutside = false;
    offset += offsetVelocity;
}

void Agent::draw()
{
    ofColor colHsb;
    if (mono) colHsb = ofColor(0, 0, 0, alpha);
    else colHsb = hsbToRgb(col.x, col.y, col.z);
//    ribbon->drawLineRibbon(colHsb, ofMap(strokeW, 0, 1, minStroke, maxStroke));
//    ribbon->drawMeshRibbon(colHsb, ofMap(strokeW, 0, 1, minStroke, maxStroke));
    ribbon->drawMeshRibbonTriangle(colHsb, ofMap(strokeW, 0, 1, minStroke, maxStroke));
}

void Agent::setRandomPosition() {
    p.x = ofRandom(-spaceSizeX, spaceSizeX);
    p.y = ofRandom(-spaceSizeY, spaceSizeY);
    p.z = ofRandom(-spaceSizeZ, spaceSizeZ);
}
