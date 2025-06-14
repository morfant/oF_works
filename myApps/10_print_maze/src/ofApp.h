#pragma once

#include "ofMain.h"
#define STEP 20
#define NUM_X 20
#define NUM_Y 20



class ofApp : public ofBaseApp{
	public:
        void walk();
        void drawWalker();
    void checkOffScreen();
    void bounceOffWall();
    void reset();
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
    
    float WIDTH, HEIGHT;
    ofColor bgColor = ofColor(0, 120, 179);
    ofColor lineColor = ofColor(255);
    float coins[NUM_X][NUM_Y];
    vector<ofVec2f> walkPaths;
    float cx, cy, xold, yold, xold2, yold2;
//    int count = 0, lockIdx = 0;
    int dir;
    ofPolyline line;
    bool isStarted = true;
    
};
