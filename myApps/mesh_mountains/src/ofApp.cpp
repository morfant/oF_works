#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    stepX = width / num_x;
    stepY = height / num_y;
    
    for (int x = 0; x < num_x; ++x) {
        for (int y = 0; y < num_y; ++y) {
            mesh.addVertex(ofPoint(x * stepX, y * stepY, 0));
            mesh.addColor(ofColor(255, 255, 255));
        }
    }
   
    
}

//--------------------------------------------------------------
void ofApp::update(){
   
    // mode 선택
    if (prev_gl_mode != gl_mode) {
        mesh.setMode(connectingMode[gl_mode]);
        
        // num_x - 1이 미리 만든 vertex 수에 부합한다, 의도적인 에러를 만들어 보자
        for (int x = 0; x < num_x - 1; ++x) {
            // num_y - 1이 미리 만든 vertex 수에 부합한다, 의도적인 에러를 만들어 보자
            for (int y = 0; y < num_y - 1; ++y) {
                mesh.addIndex(x + (y * num_x));
                mesh.addIndex((x + 1) + (y * num_x));
                mesh.addIndex(x + (num_x * (y + 1)));
                
                mesh.addIndex((x + 1) + (y * num_x));
                mesh.addIndex((x + 1) + (num_x * (y + 1)));
                mesh.addIndex(x + (num_x * (y + 1)));
            }
        }
        prev_gl_mode = gl_mode;
    }
   
    
    // z 값에 변화 주기
    for (int x = 0; x < num_x; ++x) {
        for (int y = 0; y < num_y; ++y) {
            
            int idx = num_x * y + x;
            ofPoint v = mesh.getVertex(idx);
            
            float s = sin(ofGetFrameNum()/(20.f + idx/num_x)) * 20.f;
            v.z = ofNoise(idx/5.f + ofGetFrameNum()/60.f) * 200.f + s;
            mesh.setVertex(idx, v);
            ofColor c(v.z, 100, 120);
            mesh.setColor(idx, c);
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0, 0, 0);
    
    cam.begin();
    mesh.draw();
    cam.end();
    
    
    ofColor(255);
    ofDrawBitmapString("Select 1 ~ 7", 100, 100);
    
    string currentModeName = modeNames[gl_mode];
    ofDrawBitmapString(currentModeName, 100, 130);
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    int n = key - 48;
    
    if (0 < n && n < 8) {
        cout << n << endl;
        gl_mode = n - 1;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
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
