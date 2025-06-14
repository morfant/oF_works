#pragma once

#include "ofMain.h"
#include "gdLib.h"

class ofApp : public ofBaseApp{

	public:
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
    
    
        bool isToggle = false;
        bool isDrawLine = false;
        float noiseXRange, noiseYRange;
        float noiseStep;
    
        ofMesh mesh, meshLine;
        ofEasyCam cam;
    
        int numX, numY;
        int width, height;
        int stepX, stepY;
        
        int glMode = 1;
        int prevGlMode = -1;
    
        float zScale = 200.f;
        
        ofPrimitiveMode connectingMode [3] = {
            OF_PRIMITIVE_POINTS,
            OF_PRIMITIVE_LINES,
            OF_PRIMITIVE_TRIANGLES,
        };
        
        string modeNames [3] = {
            "OF_PRIMITIVE_POINTS",
            "OF_PRIMITIVE_LINES",
            "OF_PRIMITIVE_TRIANGLES",
        };
    
    
        ofColor topColor, midColor, bottomColor;
    
        int octave = 4;
        float falloff = 0.5;
 
    

};
