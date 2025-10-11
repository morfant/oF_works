/*
 *  ball.h
 *  pp
 *
 *  Created by gangil Yi on 3/24/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxVectorGraphics.h"

class Ball{

	
public:

	Ball();
	
	void update();
	virtual void update(int);	
	void display(int _color, int _numShape, float _step, float _angle, bool _isFill);	
	void display(int _color, int _numShape, float _step, float _angle, float _radius, bool _isFill);
	void checkBorder(int x, int y, int width, int height);
	
	int lineColor;
	int numSteps;
	float step;
	float angle;
	float radius;
	
	int rotateAngle;
	
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f direction;
	ofVec2f acc;
	float spd;
		
//private:
	ofxVectorGraphics output;

};