//
//  TexSphere.hpp
//  videoSphere
//
//  Created by Gang il Lee on 2/11/25.
//

#ifndef TexSphere_hpp
#define TexSphere_hpp

#include <stdio.h>
#include "ofMain.h"
#include "glm/vec3.hpp"


class TexSphere {
private:
    ofSpherePrimitive sp;
    ofTexture texture;
    
    glm::vec3 pos;
    float radius;
    float rotAngle;
    
    int selAxis = 0;
    int selInterval = 200;
    
    
public:
    TexSphere(){};
    TexSphere(const glm::vec3& _pos, float r, float ang, const ofVec2f& wh);
    
    void update();
    void getTexture(const ofTexture& t);
    void draw();
    
};

#endif /* TexSphere_hpp */
