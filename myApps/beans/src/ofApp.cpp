#include "ofApp.h"


// Static member variable
ofFbo Bean::fbo1;
ofFbo Bean::fbo2;


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255);
    ofSetCircleResolution(40);
    
    w = ofGetWidth();
    h = ofGetHeight();
    
    Bean::fbo1.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    Bean::fbo2.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    
    int stepW = 120;
    int stepH = 120;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            auto b = make_shared<Bean>(ofVec2f(i * stepW, j * stepH), 50, ofRandom(0.01f, 0.08f), 0, 1);
//            auto b = make_shared<Bean>(ofVec2f(i * stepW, j * stepH), 50, 0.05f, 0, 1);
            beans_1.push_back(b);
        }
    }
    
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            auto b = make_shared<Bean>(ofVec2f(i * stepW, j * stepH), 50, ofRandom(0.01f, 0.08f), 1, 2);
//            auto b = make_shared<Bean>(ofVec2f(i * stepW, j * stepH), 50, 0.05f, 1, 2);
            beans_2.push_back(b);
        }
    }
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (auto it = beans_1.begin(); it != beans_1.end(); it++)
    {
        auto& b = *it;
        b->update();
    }
    
    for (auto it = beans_2.begin(); it != beans_2.end(); it++)
    {
        auto& b = *it;
        b->update();
    }


}

//--------------------------------------------------------------
void ofApp::draw(){

    Bean::fbo1.begin();
    ofBackground(255, 255, 255, 255);
    Bean::fbo1.end();
    for (auto it = beans_1.begin(); it != beans_1.end(); it++)
    {
        auto& b = *it;
        b->draw();
    }
    
    ofEnableDepthTest();  // 깊이 테스트 활성화 (3D 공간에서 오브젝트가 올바르게 보이게 하기 위해)
    ofPushMatrix();

    // FBO를 회전시키기
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, -50); // FBO가 화면의 중앙에 위치하도록
    ofRotateXDeg(30);  // X축으로 30도 회전
    //       ofRotateYDeg(ofGetElapsedTimef() * 50);  // Y축으로 시간에 따라 회전 (회전 속도: 50도/초)
    ofRotateZDeg(15);  // Z축으로 15도 회전

    // 회전된 FBO 그리기
    Bean::fbo1.draw(-Bean::fbo1.getWidth() / 2, -Bean::fbo1.getHeight() / 2);
    ofPopMatrix();  // 변환 상태 복원
    ofDisableDepthTest();  // 깊이 테스트 비활성화 (2D 그리


    
    
    Bean::fbo2.begin();
    ofBackground(255, 200, 200, 200);
    Bean::fbo2.end();
    for (auto it = beans_2.begin(); it != beans_2.end(); it++)
    {
        auto& b = *it;
        b->draw();
    }
//    Bean::fbo2.draw(0, 0);

     
    ofEnableDepthTest();  // 깊이 테스트 활성화 (3D 공간에서 오브젝트가 올바르게 보이게 하기 위해)
    ofPushMatrix();

    // FBO를 회전시키기
    cout << ofGetMouseX() << endl;
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, ofGetMouseY()); // FBO가 화면의 중앙에 위치하도록
    ofRotateXDeg(30);  // X축으로 30도 회전
//    ofRotateYDeg(ofGetElapsedTimef() * 50);  // Y축으로 시간에 따라 회전 (회전 속도: 50도/초)
    ofRotateZDeg(15);  // Z축으로 15도 회전

    // 회전된 FBO 그리기
    Bean::fbo2.draw(-Bean::fbo2.getWidth() * 0.3, -Bean::fbo2.getHeight() * 0.3);
    ofPopMatrix();  // 변환 상태 복원
    ofDisableDepthTest();  // 깊이 테스트 비활성화 (2D 그리


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
