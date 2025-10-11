/*
 *  BlackHole.h
 *  walk_back
 *
 *  Created by gangil Yi on 3/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Ball.h"


class BlackHole : public Ball{
	
public:
	
	void init(int, int, float, int);
	void update(int, int, int); //rotate rate, xpos, ypos
	
	float pullingForce;

};