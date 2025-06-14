#pragma once

#include <random>  // C++의 랜덤 라이브러리
#include <sstream>  // for std::ostringstream
#include <iomanip>  // for std::setw and std::setfill
#include "ofMain.h"
#include "ofxGui.h"
#include "Dot.hpp"
#define NUM 12



class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
    
        void fillArr();
        void clearArr();
        void setRandomSeed();
        void savePdf();  // PDF 저장 함수

		
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
    
        float WIDTH, HEIGHT;
    
    // PDF
    bool saveToPdf = false;   // PDF 저장 여부 플래그

    // App
    vector<Dot *> arr;
    
    // Random
    // Mersenne Twister 엔진을 시드로 초기화
    std::mt19937 generator;
    
    // 실수 범위의 분포 선언
    std::uniform_real_distribution<float> distribution;
    
    // 시드를 고정하여 재현 가능한 난수 생성
    unsigned int seed = 0;
    unsigned int previousSeed = -1;  // 초기값을 -1로 설정하여 첫 번째 업데이트에서 무조건 실행되도록 함

    // GUI
    ofxPanel gui;             // GUI 패널
    ofxIntSlider randomSeed;  // 숫자 입력을 위한 슬라이더

   
};
