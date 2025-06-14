#pragma once

#include "ofMain.h"

#define NUM_X 20
#define NUM_Y 20
#define NUM_Z 20

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
    
        array<array<array<ofPoint, NUM_Z>, NUM_Y>, NUM_X> coordinate;
    
    float w, h;
    int gridX, gridY, gridZ;
    int side;
    float count;
    
    ofEasyCam cam;
};
