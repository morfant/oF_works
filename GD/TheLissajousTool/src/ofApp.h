#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "gdLib.h"

class ofApp : public ofBaseApp{

    public:
        void setup() override;
        void update() override;
        void drawAnimation();
        void draw() override;
        void exit() override;
    
        void calculateLissajousPoints();
        void drawLine(const glm::vec2& p1, const glm::vec2& p2);
//    void drawLine(shared_ptr<glm::vec2> p1, shared_ptr<glm::vec2> p2);
        void onSliderChangedInt(int& value);
        void onSliderChangedFloat(float& value);
        void onSliderChangedIntStep(int& value);

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
        
    
        int width, height;
        int pointCount = 1500;
        int freqX = 13;
        int freqY = 11;
        int freqZ = 11;
        float phiX = 97;
        float phiY = 0;
        int modFreqX = 0;
        int modFreqY = 0;
        int modFreq2X = 11, modFreq2Y = 17;
        float modFreq2Strength = 0.0;
        int randomOffset = 2;
        bool invertBackground = false;
        bool connectAllPoints = true;
        float connectionRadius = 110;

        float lineWeight = 1, lineAlpha = 20;
        bool invertHue = false;
        float minHueValue = 0;
        float maxHueValue = 100;
        float saturationValue = 80;
        float brightnessValue = 0;


        vector<shared_ptr<glm::vec2>> lissajousPoints;


        float angle;
        float x, y;
    
        ofxPanel gui;
        ofxIntSlider iSlider[15];
        ofxFloatSlider fSlider[10];
        ofxToggle toggle[10];
        ofEasyCam cam;
    
        bool reDraw = false;
};
