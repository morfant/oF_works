/*
 *  BlackHole.cpp
 *  walk_back
 *
 *  Created by gangil Yi on 3/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "BlackHole.h"

void BlackHole::init(int _posX, int _posY, float ra, int lc){

	//	output.noFill();
    ofSetHexColor(lc);
    ofCircle(_posX, _posY, ra);
    	
};

void BlackHole::update(int _rotateRate, int _posX, int _posY)
{
	
//    vel.x = direction.x * spd;
//    vel.y = direction.y * spd;    
//    
//	pos.x += vel.x;
//	pos.y += vel.y;
//    
//	rotateAngle = (rotateAngle + _rotateRate) % 360;

    
    
	pos.x = _posX;
	pos.y = _posY;
	rotateAngle = (rotateAngle + _rotateRate) % 360;
	
}
