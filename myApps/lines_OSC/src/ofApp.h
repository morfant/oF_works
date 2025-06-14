#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// listening port
#define RECV_PORT 12347

#define HOST "localhost"
#define SEND_PORT 12348

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
    
    
    signed char n = 1;
    string shapeName = " ", msg = " ", loading = ".", next = "";
    
    float bx, by, bz, ex, ey, ez;
    float tweakRange;
    float w, h, depthAbs;
    
    ofColor lineColor;
    
    ofxOscReceiver receiver;
    ofxOscSender sender;
    int modeSet = 0;
    
    int numOfLines = 0;

    
    
};
