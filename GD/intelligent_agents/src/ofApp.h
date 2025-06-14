#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
    
        enum class direction {
            NORTH,
            EAST,
            SOUTH,
            WEST
        };
 
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
    

        int getRandomAngle(direction dir);
        void drawRoundedLine(ofPoint start, ofPoint end, float thickness);
        void drawThickLine(ofPoint start, ofPoint end, float thickness);


        int w, h;
        direction dir;

        int posX, posY, posXCross, posYCross;
        int speed = 50;
        float angle = HALF_PI;
        int stepSize = 2;
        bool reachedBorder = false;
        ofPixels pixels;
        int angleCount = 5;
        float minLength = 0;
        ofFbo fbo;


};
