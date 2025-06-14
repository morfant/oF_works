#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    // 윈도우 크기 설정
    ofSetWindowShape(800, 600);
    ofSetFrameRate(5);

    n = ARRAY_SIZE;
    resetArray();
    stepI = 0;
    stepJ = 0;
    
    graph = new Graph(values, ofGetWidth());
    
    font.load("verdana.ttf", 24); // 폰트를 불러오고 크기를 24로 설정
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Bubble sort 시각화
//    for (int i = 0; i < n - 1; i++)
    if (stepI < n - 1)
    {
//        for (int j = 0; j < n - 1 - i; j++)
        if (stepJ < n - 1 - stepI)
        {
            if (values[stepJ] > values[stepJ + 1]) // 오름차순
//            if (values[stepJ] < values[stepJ + 1]) // 내림차순
            {
                std::swap(values[stepJ], values[stepJ + 1]);
            }
            stepJ++;
        }
        else
        {
            stepJ = 0;
            stepI++;
        }
    }
    else
    {
        resetArray();
        stepI = 0;
        stepJ = 0;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    graph->update(values);
    graph->draw(stepJ);
    
    font.drawString(
                    ofToString(ofGetFrameRate(), 2),
                    ofGetWidth() / 2 - 50, ofGetHeight() / 2
    ); // 원하는 위치에 텍스트 출력
    
}


//--------------------------------------------------------------
void ofApp::resetArray(){
    values.clear();
    for (int i = 0; i < n; i++) {
        values.push_back(ofRandom(10, ofGetHeight()));  // 랜덤한 값으로 배열 초기화
    }
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
