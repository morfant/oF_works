#pragma once

#include <cmath>
#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        double beta(double x, double y, bool isLgamma=false);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    float w;
    float h;
    float step = 0.03;
    float scaleFactor = 50.f;
    float r_min = -3.f;
    float r_max = 3.f;

    ofEasyCam cam; // add mouse controls for camera movement
//    ofCamera cam;
    ofFbo fbo;
};
