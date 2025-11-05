/*
 *  ball.cpp
 *  pp
 *
 *  Created by gangil Yi on 3/24/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ball.h"

using namespace std;

Ball::Ball(){
	lineColor = 0xff00ff;
	radius = 2 + ofRandom(3);
	
	pos.x = ofGetWidth() * 3 / 4;
	pos.y = ofGetHeight() / 4;
	
	vel.x = 10.0;
	vel.y = 10.0;

	acc.x = 1.0;
	acc.y = 1.0;
	
	rotateAngle = 0;
	spd = ofRandom(6);
	
	// calculate initial random direction
	direction.x = 0.1 + ofRandom(0.89);
	direction.y = 0.1 + ofRandom(0.89);
}

void Ball::update()
{
    
    vel.x = direction.x * spd;
    vel.y = direction.y * spd;    
    
	pos.x += vel.x;
	pos.y += vel.y;
	
	rotateAngle = (rotateAngle + 1) % 360;
	
}

void Ball::update(int _rotateRate)
{
    vel.x = direction.x * spd;
    vel.y = direction.y * spd;    
    
	pos.x += vel.x;
	pos.y += vel.y;
    	
	rotateAngle = (rotateAngle + _rotateRate) % 360;
	
}



void Ball::display(int _color, int _numShape, float _step, float _angle, bool _isFill)
{
	
	ofPushMatrix();
	ofTranslate(pos.x, pos.y, 0.0);	
	ofRotateZ(rotateAngle);
	
	if(_isFill) ofFill();
	else ofNoFill();

    ofSetHexColor(_color);	
    
    //poly shape
    ofBeginShape();
	
	numSteps = _numShape;
	step		= _step;
	angle		= _angle;
	
	for(int i = 0; i < numSteps + 3; i++){
		float rx = cos(angle) * radius;
		float ry = sin(angle) * radius;
		
        ofCurveVertex(rx, ry);
		angle += step;
	}
	
    ofEndShape();    
         
	ofPopMatrix();	
	
}


void Ball::display(int _color, int _numShape, float _step, float _angle, float _radius, bool _isFill)
{
	
	ofPushMatrix();
	ofTranslate(pos.x, pos.y, 0.0);	
	ofRotateZ(rotateAngle);
	
	if(_isFill) ofFill();
	else ofNoFill();
	
    ofSetHexColor(_color);	
    
    //poly shape
    ofBeginShape();
	
	numSteps = _numShape;
	
	step		= _step;
	angle		= _angle;
	radius		= _radius;
	
	for(int i = 0; i < numSteps + 3; i++){
		float rx = cos(angle) * radius;
		float ry = sin(angle) * radius;
		
        ofCurveVertex(rx, ry);
		angle += step;
	}
	
    ofEndShape();    
	ofPopMatrix();	
	
}

void Ball::checkBorder(int x, int y, int width, int height){
	
	
    //LEFT
	if(pos.x <= radius){
		pos.x = radius;
		direction.x *= -1;
//        cout<<"x : " << direction.x << " y : " <<direction.y<<endl;
	}
    
    //RIGHT
	if (pos.x >= ofGetWidth() - radius) {
		pos.x = ofGetWidth() - radius;
		direction.x *= -1;		
//        cout<<"x : " << direction.x << " y : " <<direction.y<<endl;
	}
        
    //TOP
	if(pos.y <= radius){
		pos.y = radius;
		direction.y *= -1;
//        cout<<"x : " << direction.x << " y : " <<direction.y<<endl;
	}
    
    //BOTTOM
	if (pos.y >= ofGetHeight() - radius) {
		pos.y = ofGetHeight() - radius;
		direction.y *= -1;		
//        cout<<"x : " << direction.x << " y : " <<direction.y<<endl;
	}
}
