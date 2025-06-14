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
#include "gdLib.h"

class Agent{
    
private:
    glm::vec2 p, pOld;
    float noiseZ, noiseZVelocity = 0.01;
    float stepSize, angle;
    bool isOutside = false;
    
    
public:
    Agent();
    void update1();
    void update2();
    void setNoiseZRange(float f);

    static int width, height;
    static int octave;
    static float falloff;
    static float noiseScale, noiseStrength;
    static float strokeWidth;

    
};

#endif /* Agent_hpp */
