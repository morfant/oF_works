#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Agent.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;
        void drawScene();

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
		
        const string PROJECTNAME = "NoiseMotion";
        const int pdfAccumulationFrame = 60;
        bool bSavePdf = false;
        int count = 0;

        ofxPanel gui;
        ofxIntSlider iSlider[4];    // Int 타입 슬라이더
        ofxFloatSlider fSlider[6];     // Float 타입 슬라이더
        ofxToggle toggle;          // 토글 버튼
        ofxButton button;          // 일반 버튼
        
        int w, h;
        int drawMode;
        
        const int AGENT_MAX_NUM = 20000;
        int agentsCount;
        
        float overlayAlpha;
        float agentAlpha;
        
        vector<shared_ptr<Agent>> agents;
};
