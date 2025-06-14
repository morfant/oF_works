#pragma once

#include "ofMain.h"
#include "Rectangle.hpp"

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
    int camWidth = 640;
    int camHeight = 480;
  
    
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
    
    
    Rectangle rect_1 = {0, 0};
    Rectangle rect_2 = {(float)camWidth, 0};
    Rectangle rect_3 = {(float)camWidth*2, 0};
    Rectangle rect_4 = {0, (float)camHeight};
    Rectangle rect_5 = {(float)camWidth, (float)camHeight};
    Rectangle rect_6 = {(float)camWidth * 2, (float)camHeight};
    Rectangle rect_7 = {0, (float)camHeight * 2};
    Rectangle rect_8 = {(float)camWidth, (float)camHeight * 2};
    Rectangle rect_9 = {(float)camWidth * 2, (float)camHeight * 2};
    

};
