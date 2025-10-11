/*
 *  BSmanage.h
 *  walk_back
 *
 *  Created by gangil Yi on 3/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


//#include "Ball.h"
#include "BlackHole.h"
#include "Stk.h"
#include "ofxOsc.h"


//#include "testApp.h"

#define MANAGE_BAR_NUM 15
#define HOST "localhost"
#define PORT 57120

class BSmanage{
	
public:
	
	BSmanage();
	BSmanage(int, int);
	
//	Ball* balls[MANAGE_BALL_NUM];
	vector<Ball*> balls;
	Stk* stks[MANAGE_BAR_NUM];
	vector<BlackHole*> bHoles;
	
	void init(int, int, int);	
	void bsHitCheck(Stk*, Ball*, int);
	void checkEatBall(BlackHole*, Ball*, int);

	
	ofVec2f getBpos(Ball*);
	float getBradius(Ball*);
	void update(Stk*, Ball*);
	void ballUpdate();
	
	
	//BALL
	void addBall();
	
	//BAR
	void reset();

	//OSC
	ofxOscSender sender;
	
	void oscSend1(const char* addr, int p1 );
	void oscSend2(const char* addr, int p1, int p2);
	void oscSend2(const char* addr, int p1, float p2);
	void oscSend4(const char* addr, int p1, float p2, int p3, float p4);
	void oscSend5(const char* addr, int p1, int p2, int p3, int p4, int p5);	
	
	



};