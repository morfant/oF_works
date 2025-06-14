//
//  Block.cpp
//  cam_mesh_b
//
//  Created by Gang il Lee on 2021/12/16.
//

#include "Block.hpp"


Block::Block(ofPoint p) {
    count++;
    pos = p;
}

void Block::update(float h, ofColor c) {
    height = h;
    col = c;
    
    if (height != 0 && height < thr) {
        isAlive = false;
    }
}

void Block::draw() {
    if (isAlive) {
        ofSetColor(col);
        ofDrawBox(pos.x, pos.y, pos.z, 10, 10, height);
    } else {
        ofSetColor(ofColor(0, 0, 0));
        ofDrawBox(pos.x, pos.y, pos.z, 10, 10, 0);
    }
}


