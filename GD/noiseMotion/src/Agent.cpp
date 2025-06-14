//
//  Agent.cpp
//  noiseMotion
//
//  Created by Gang il Lee on 12/24/24.
//

#include "Agent.hpp"


Agent::Agent()
{
    p = glm::vec2(ofRandom(width), ofRandom(height));
    pOld = glm::vec2(p.x, p.y);
    stepSize = ofRandom(1, 5);
    setNoiseZRange(0.4);
}

void Agent::update1()
{
    
//    angle = fractalNoise(p.x / noiseScale, p.y / noiseScale, octave, falloff) * noiseStrength; // 2D
    angle = fractalNoise(p.x / noiseScale, p.y / noiseScale, noiseZ, octave, falloff) * noiseStrength;
    p.x += cos(angle) * stepSize;
    p.y += sin(angle) * stepSize;
    
    if (p.x < -10) isOutside = true;
    else if (p.x > width + 10) isOutside = true;
    else if (p.y < -10) isOutside = true;
    else if (p.y > height + 10) isOutside = true;
    
    if (isOutside)
    {
        p.x = ofRandom(width);
        p.y = ofRandom(height);
        pOld = p;
    }
    
    ofSetLineWidth(strokeWidth * stepSize);
    ofDrawLine(pOld, p);
    pOld = p;
    isOutside = false;
    
    noiseZ += noiseZVelocity;
    
}

void Agent::update2()
{
    
//    angle = fractalNoise(p.x / noiseScale, p.y / noiseScale, octave, falloff) * 24;  // 2D
    angle = fractalNoise(p.x / noiseScale, p.y / noiseScale, noiseZ, octave, falloff) * 24; // 3D
    angle = (angle - int(angle)) * noiseStrength;

    
    p.x += cos(angle) * stepSize;
    p.y += sin(angle) * stepSize;
    
    if (p.x < -10) isOutside = true;
    else if (p.x > width + 10) isOutside = true;
    else if (p.y < -10) isOutside = true;
    else if (p.y > height + 10) isOutside = true;
    
    if (isOutside)
    {
        p.x = ofRandom(width);
        p.y = ofRandom(height);
        pOld = p;
    }
    
    ofSetLineWidth(strokeWidth * stepSize);
    ofDrawLine(pOld, p);
    pOld = p;
    isOutside = false;
    
    noiseZ += noiseZVelocity;

}


void Agent::setNoiseZRange(float f)
{
    noiseZ = ofRandom(f);
}
