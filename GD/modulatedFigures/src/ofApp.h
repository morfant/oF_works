#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "../../UTILS/gdLib.h"

class ofApp : public ofBaseApp{

    public:
        void setup() override;
        void calculateLissajousPoints();
        void update() override;
        void drawAnimation();
        void draw() override;
        void exit() override;
        void onSliderChanged(int& value);

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
        
    
        int w, h;
        int pointCount = 800;
        int freqX = 1;
        int freqY = 4;
        int freqZ = 2;
        float phiX = 0;
        float phiY = 0;
        int modFreqX = 2;
        int modFreqY = 1;
    
        
        vector<glm::vec3> points;


        float angle;
        float x, y;
        int margin = 25;
    
        ofxPanel gui;
        ofxIntSlider iSlider[6];    // Int 타입 슬라이더
        ofxToggle toggle;
        ofEasyCam cam;
};
