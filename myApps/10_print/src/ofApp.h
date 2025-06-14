#pragma once

#include "ofMain.h"
#define NUM_X 15
#define NUM_Y 15
#define PAD_Y 3



class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofColor bgColor = ofColor(0, 120, 179);
    ofPoint coordinate[NUM_X][NUM_Y];
    float coins[NUM_X][NUM_Y] = {0};
    float w, h;
    float GRID_X, GRID_Y;
    int count = 0, lockIdx = 0;
    ofPolyline line;
    
};
