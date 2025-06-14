//
//  Agent.hpp
//  noiseMotion
//
//  Created by Gang il Lee on 12/24/24.
//

#ifndef Agent_hpp
#define Agent_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Ribbon3d.hpp"
#include "gdLib.h"

class Agent{
    
private:
    bool isOutside = false;
    glm::vec3 p;
    float offset, stepSize, angleY, angleZ;
    Ribbon3d* ribbon;
    ofVec3f col;
    
    
public:
    Agent();
    void update1();
    void update2();
    void draw();
    void setNoiseZRange(float f);
    void setRandomPosition();

    static int width, height;
    static int octave;
    static float falloff;
    static float noiseScale, noiseStrength;
    static float minStroke, maxStroke;
    static int spaceSizeX, spaceSizeY, spaceSizeZ;
    static bool mono;
    static float alpha;
    float strokeW;
    float offsetVelocity;

    
};

#endif /* Agent_hpp */
