//
//  Ribbon3d.hpp
//  agentsInSpace
//
//  Created by Gang il Lee on 12/28/24.
//

#ifndef Ribbon3d_hpp
#define Ribbon3d_hpp

#include <stdio.h>
#include "ofMain.h"

class Ribbon3d {
    
private:
    int count;
    vector<glm::vec3> p;
    vector<bool> isGap;
    
    
public:
    Ribbon3d(glm::vec3 theP, int theCount);
    void update(glm::vec3 theP, bool theIsGap);
    void drawLineRibbon(ofColor theStrokeCol, float theWidth);
    void drawMeshRibbon(ofColor theStrokeCol, float theWidth);
    void drawMeshRibbonTriangle(ofColor theStrokeCol, float theWidth);
};

#endif /* Ribbon3d_hpp */
