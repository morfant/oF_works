#pragma once

#include "ofMain.h"
#include "Block.hpp"

// This example is  based on the Processing "ASCII Video" example by Ben Fry
// and it is designed to demonstrate how to re-interpret live video as text
// to make it look like some good old ASCII art!
//
// For more information regarding this example take a look at the README.md.

class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
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
    
    ofVideoGrabber vidGrabber;
    int camWidth;
    int camHeight;
    
    int num_x = 32;
    int num_y = 28;
    float width, height;
    float stepX, stepY;
    
    ofEasyCam cam;
    ofMesh mesh;
    int gl_mode = 0;
    int prev_gl_mode = -1;
    
    ofPrimitiveMode connectingMode [7] = {
        OF_PRIMITIVE_POINTS,
        OF_PRIMITIVE_LINES,
        OF_PRIMITIVE_LINE_STRIP,
        OF_PRIMITIVE_LINE_LOOP,
        OF_PRIMITIVE_TRIANGLES,
        OF_PRIMITIVE_TRIANGLE_STRIP,
        OF_PRIMITIVE_TRIANGLE_FAN
    };
    
    string modeNames [7] = {
        "OF_PRIMITIVE_POINTS",
        "OF_PRIMITIVE_LINES",
        "OF_PRIMITIVE_LINE_STRIP",
        "OF_PRIMITIVE_LINE_LOOP",
        "OF_PRIMITIVE_TRIANGLES",
        "OF_PRIMITIVE_TRIANGLE_STRIP",
        "OF_PRIMITIVE_TRIANGLE_FAN"
    };
    
    
    Block* blocks[896];
    
    
};
