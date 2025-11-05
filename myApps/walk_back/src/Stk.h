/*
 *  Stk.h
 *  pp_sticks
 *
 *  Created by gangil Yi on 3/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#define DB_TIME 20
#define COLLISION_RANGE 0
//#define DEBUGMODE
#include "ofxVectorGraphics.h"

class Stk{
	
	
public:
	
	Stk();
	
	void init(int, int, int, int);
    void init(ofVec2f);
	void update();
	void display();
	ofVec2f hitCheck(ofVec2f);
	
	
	int rotateAngle;
	int color;
	float length;
	float strokeWidth;
	
	ofVec2f base1, base2, ellipse, velocity, direction;
    ofVec2f centerPos;

	float baseLength;
    vector<ofVec2f> coords;
//	vector<float> xCoords, yCoords;
	float ellipseRadius;
	float ellipseSpeed;
    float lampAngle;
	
    bool ballHitBar;
	bool bHitFlag;
    
private:
    int vecNum;
    int reflectDebounceTime;
	
	ofxVectorGraphics stkOutput;
	

	
	
};
