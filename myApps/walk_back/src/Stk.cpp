/*
 *  STK.cpp
 *  pp_sticks
 *
 *  Created by gangil Yi on 3/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Stk.h"

Stk::Stk()
{

	rotateAngle = 0;
	color = 0x224499;
	length = 30;
	strokeWidth = 3;
	bHitFlag = false;
};

void Stk::init(int _x1, int _y1, int _x2, int _y2)
{
	reflectDebounceTime = 0;

	base1.x = _x1;
	base1.y = _y1;
	base2.x = _x2;
	base2.y = _y2;

	// calculate initial random direction
	direction.x = 0.1 + ofRandom(0.89);
	direction.y = 0.1 + ofRandom(0.89);

	//	cout << direction.x << endl;

	// normalize direction vector
	float directionVectLength = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction.x /= directionVectLength;
	direction.y /= directionVectLength;

	ellipseSpeed = 3.5;

	rotateAngle = 0;
}

void Stk::update()
{

	if (reflectDebounceTime < DB_TIME && reflectDebounceTime > 0)
	{
		reflectDebounceTime--;
		//        cout<<"rTime: "<<reflectDebounceTime<<endl;
	}

	bHitFlag = false;
}

// USING THIS
ofVec2f Stk::hitCheck(ofVec2f _pos)
{
	// calculate length of base top
	if (base1.x < 0)
	{
		base1.x = 0;
		baseLength = ofDist(base1.x, base1.y, base2.x, base2.y);
		//		cout << "o1" << endl;
		//		cout << "1X: "<< base1.x << " 1Y: " << base1.y << " 2X: " << base2.x << " 2Y: " << base2.y << endl;
	}

	else if (base1.x > ofGetWidth())
	{
		base1.x = ofGetWidth();
		baseLength = ofDist(base1.x, base1.y, base2.x, base2.y);
		//		cout << "o2" << endl;
		//		cout << "1X: "<< base1.x << " 1Y: " << base1.y << " 2X: " << base2.x << " 2Y: " << base2.y << endl;
	}

	if (base2.x < 0)
	{
		base2.x = 0;
		baseLength = ofDist(base1.x, base1.y, base2.x, base2.y);
		//		cout << "o3" << endl;
		//		cout << "1X: "<< base1.x << " 1Y: " << base1.y << " 2X: " << base2.x << " 2Y: " << base2.y << endl;
	}

	else if (base2.x > ofGetWidth())
	{
		base2.x = ofGetWidth();
		baseLength = ofDist(base1.x, base1.y, base2.x, base2.y);
		//		cout << "o4" << endl;
		//		cout << "1X: "<< base1.x << " 1Y: " << base1.y << " 2X: " << base2.x << " 2Y: " << base2.y << endl;
	}

	if (base1.y < 0)
	{
		base1.y = 0;
		baseLength = ofDist(base1.x, base1.y, base2.x, base2.y);
		//		cout << "o5" << endl;
		//		cout << "1X: "<< base1.x << " 1Y: " << base1.y << " 2X: " << base2.x << " 2Y: " << base2.y << endl;
	}

	else if (base1.y > ofGetHeight())
	{
		base1.y = ofGetHeight();
		baseLength = ofDist(base1.x, base1.y, base2.x, base2.y);
		//		cout << "o6" << endl;
		//		cout << "1X: "<< base1.x << " 1Y: " << base1.y << " 2X: " << base2.x << " 2Y: " << base2.y << endl;
	}

	if (base2.y < 0)
	{
		base2.y = 0;
		baseLength = ofDist(base1.x, base1.y, base2.x, base2.y);
		//		cout << "o7" << endl;
		//		cout << "1X: "<< base1.x << " 1Y: " << base1.y << " 2X: " << base2.x << " 2Y: " << base2.y << endl;
	}

	else if (base2.y > ofGetHeight())
	{
		base2.y = ofGetHeight();
		baseLength = ofDist(base1.x, base1.y, base2.x, base2.y);
		//		cout << "o8" << endl;
		//		cout << "1X: "<< base1.x << " 1Y: " << base1.y << " 2X: " << base2.x << " 2Y: " << base2.y << endl;
	}

	else if (base1.x > 0 && base1.x < ofGetWidth() && base1.y > 0 && base1.y < ofGetHeight() &&
			 base2.x > 0 && base2.x < ofGetWidth() && base2.y > 0 && base2.y < ofGetHeight())
	{

		baseLength = ofDist(base1.x, base1.y, base2.x, base2.y);

		//		cout << "normal" << endl;
		//		cout << "1X: "<< base1.x << " 1Y: " << base1.y << " 2X: " << base2.x << " 2Y: " << base2.y << endl;
	}

	lampAngle = abs(base2.y - base1.y) / abs(base2.x - base1.x);

	// clear previous xCoords / yCoords vector elements
	coords.clear();
	//    yCoords.clear();

	vecNum = ceil(baseLength);

	// get coordinate
	coords.clear();
	coords.reserve(vecNum + 1);
	for (int i = 0; i <= vecNum; ++i)
	{
		float t = (baseLength == 0) ? 0.0f : (float)i / vecNum;
		coords.emplace_back(
			base1.x + (base2.x - base1.x) * (float)i / vecNum,
			base1.y + (base2.y - base1.y) * (float)i / vecNum);
	}

	// draw stk
	display();

	// calculate base top normal
	float baseDeltaX = (base2.x - base1.x) / baseLength;
	float baseDeltaY = (base2.y - base1.y) / baseLength;

	float normalX = -1 * baseDeltaY;
	float normalY = baseDeltaX;

	// normalized incidence vector
	float incidenceVectorX = -1 * direction.x;
	float incidenceVectorY = -1 * direction.y;

	// detect and handle collision

	//    vector<float>::const_iterator it;
	//    for(it = xCoords.begin(); it != xCoords.end(); ++it)
	//    {
	//
	//    }

	for (vector<ofVec2f>::const_iterator it = coords.begin(); it != coords.end(); ++it)
	{

		//    for (int i=0; i < vecNum; i++){
		// check distance between ellipse and base top coordinates
		//		cout<<"COMPARE RUN"<<endl;
		if (reflectDebounceTime == 0)
		{
			//		cout<<"COMPARE 2 RUN"<<endl;
			if (ofDist(_pos.x, _pos.y, it->x, it->y) <= ellipseRadius + COLLISION_RANGE)
			{
				//				cout<<"ON HIT!"<<endl;

				bHitFlag = true;

				reflectDebounceTime = DB_TIME;

				/*
				if (i == 0 || i == vecNum - 1) {

//					cout << "edge hit!" <<endl;
					direction.x *= -1;
					direction.y *= -1;
					reflectDebounceTime-=1;
					return direction;
				}

				 */

				// calculate dot product of incident vector and base top normal(N*L)
				float dot = incidenceVectorX * normalX + incidenceVectorY * normalY;

				// calculate reflection vector
				float reflectionVectorX = 2 * normalX * dot - incidenceVectorX;
				float reflectionVectorY = 2 * normalY * dot - incidenceVectorY;

				// assign reflection vector to direction vector
				direction.x = reflectionVectorX;
				direction.y = reflectionVectorY;

				/*
				// draw base top normal at collision point
				ofSetColor(255, 128, 0);
				ofSetLineWidth(5);
				ofLine(ellipse.x, ellipse.y, ellipse.x - normalX * 100, ellipse.y - normalY * 100);

				float cPointX = ellipse.x - normalX;
				float cPointY = ellipse.y - normalY;
				*/

				reflectDebounceTime -= 1;
				return direction;

#ifdef DEBUGMODE
				cout << "in stk make - dirX : " << direction.x << " dirY : " << direction.y << endl;
				//                cout<<"rtime: " << reflectDebounceTime <<endl;
				//                cout<<"COLLISION POINT: " << cPointX << "  inVecY: " << cPointY<< endl;

				cout << "inVecX: " << incidenceVectorX << "  inVecY: " << incidenceVectorY << endl;
				cout << "refVecX: " << reflectionVectorX << "  refVecY: " << reflectionVectorY << endl;
#endif
				// i = vecNum;
				it = coords.end();
			}
		}
	}

	return direction;
}

void Stk::display()
{
	//	ofSetHexColor(0x1100ee);

	/*
	//draw begin / end point
	ofSetColor(255, 0, 0);
	ofFill();
	ofCircle(base1.x, base1.y, 10);
	ofSetColor(0, 0, 255);
	ofCircle(base2.x, base2.y, 10);
	*/
	//
	//	stkOutput.setColor(0x5c5c5c);
	//	stkOutput.setLineWidth(1);
	//	stkOutput.line(base1.x, base1.y, base2.x, base2.y);

	ofSetHexColor(0x5c5c5c);
	ofSetLineWidth(1);
	ofEnableSmoothing();
	ofLine(base1.x, base1.y, base2.x, base2.y);
	ofDisableSmoothing();
}
