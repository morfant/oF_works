//
//  Block.hpp
//  cam_mesh_b
//
//  Created by Gang il Lee on 2021/12/16.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "ofMain.h"

class Block {
    
    ofPoint pos; // pos.x, pos.y, pos.z
    ofColor col;
    float height;
    bool isAlive = true;
    int thr = 50;
    
public:
    static int count;
    Block(ofPoint p);
    void update(float h, ofColor c);
    void draw();
    
};


#endif /* Block_hpp */
