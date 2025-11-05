/*
 *  BSmanage.cpp
 *  walk_back
 *
 *  Created by gangil Yi on 3/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "BSmanage.h"


BSmanage::BSmanage(){

	//OSC SETUP
	sender.setup( HOST, PORT );
	
}

BSmanage::BSmanage(int baNum, int stNum){
	
	//OSC SETUP
	sender.setup( HOST, PORT );

}

void BSmanage::init(int baNum, int stNum, int bhNum){

	for(int i = 0; i < baNum; i++){
		Ball* tBall = new Ball();
		balls.push_back(tBall);
	}
		
	for(int i = 0; i < stNum; i++){
		stks[i] = new Stk();
	}
	
	for(int i = 0; i < stNum; i++){
        stks[i]->init(100, 100 + 30*i, 200 + 30 * i, 100 + 30*i);
//		stks[i]->direction = balls[i]->direction;
	}
	
	for(int i = 0; i < bhNum; i++){
		BlackHole* tBhole = new BlackHole();
		bHoles.push_back(tBhole);
	}
	
}

void BSmanage::addBall(){
	
	Ball* tBall = new Ball();
	balls.push_back(tBall);
	
}

ofVec2f BSmanage::getBpos(Ball* _ball){
	
	return _ball->pos;
};


float BSmanage::getBradius(Ball* _ball){

	return _ball->radius;
};

void BSmanage::update(Stk* _stk, Ball* _ball){
	
	_stk->ellipse = getBpos(_ball);
	_stk->ellipseRadius = getBradius(_ball);
	_stk->direction = _ball->direction;
	_stk->update();

};

void BSmanage::bsHitCheck(Stk* _stk, Ball* _ball, int _sIdx){
	
	ofVec2f temp;
	temp = _stk->hitCheck(_ball->pos);
	_ball->direction = temp;
	
	if (_stk->bHitFlag == true) {
		oscSend4("BALL_HIT", _sIdx, _ball->radius, balls.size(), _stk->lampAngle);
	}
};

void BSmanage::checkEatBall(BlackHole* _bHole, Ball* _ball, int _bIdx){
	
	float tDist = ofDist(_bHole -> pos.x, _bHole -> pos.y, _ball -> pos.x, _ball -> pos.y);
	float subRadius = _bHole->radius - _ball->radius;

	if (tDist <= subRadius) {
		balls.erase(balls.begin() + _bIdx);
	}
	
};


void BSmanage::reset(){
	
	for (int i = 0; i < MANAGE_BAR_NUM; i++) {
		stks[i]->base1.x = 100;
		stks[i]->base1.y = 100 + 50 * i;
		stks[i]->base2.x = 200 + 50 * i;
		stks[i]->base2.y = 100 + 50 * i;
	}
	
	
}
	
//-------------------------OSC---------------------------

void BSmanage::oscSend1(const char* addr, int p1 ) //addr is address pattern
{
	ofxOscMessage m;
	m.setAddress( addr );
	m.addIntArg( p1 );
	sender.sendMessage( m );	
}

void BSmanage::oscSend2(const char* addr, int p1, int p2 ) //addr is address pattern
{
	ofxOscMessage m;
	m.setAddress( addr );
	m.addIntArg( p1 );
	m.addIntArg( p2 );	
	sender.sendMessage( m );	
}


void BSmanage::oscSend2(const char* addr, int p1, float p2 ) //addr is address pattern
{
	ofxOscMessage m;
	m.setAddress( addr );
	m.addFloatArg( p1 );
	m.addFloatArg( round(p2 * 100) );	
	sender.sendMessage( m );	
}

void BSmanage::oscSend4(const char* addr, int p1, float p2, int p3, float p4 ) //addr is address pattern
{
	ofxOscMessage m;
	m.setAddress( addr );
	m.addFloatArg( p1 );
	m.addFloatArg( round(p2) );
	m.addIntArg( p3 );
	m.addFloatArg( round(p4 * 100) );
	sender.sendMessage( m );	
}


void BSmanage::oscSend5(const char* addr, int p1, int p2, int p3, int p4, int p5 ) //addr is address pattern
{
	ofxOscMessage m;
	m.setAddress( addr );
	m.addIntArg( p1 );
	m.addIntArg( p2 );	
	m.addIntArg( p3 );	
	m.addIntArg( p4 );
	m.addIntArg( p5 );	        
	sender.sendMessage( m );	
}



