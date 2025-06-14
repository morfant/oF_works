#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth, camHeight);
    
    rect_1.setup(camWidth, camHeight);
    rect_2.setup(camWidth, camHeight);
    rect_3.setup(camWidth, camHeight);
    rect_4.setup(camWidth, camHeight);
    rect_5.setup(camWidth, camHeight);
    rect_6.setup(camWidth, camHeight);
    rect_7.setup(camWidth, camHeight);
    rect_8.setup(camWidth, camHeight);
    rect_9.setup(camWidth, camHeight);
    
    cout << "hello" << endl;
    
}


//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    
    // mode 선택
    if (prev_gl_mode != gl_mode) {
        rect_1.setMode(connectingMode[gl_mode]);
        rect_2.setMode(connectingMode[gl_mode]);
        rect_3.setMode(connectingMode[gl_mode]);
        rect_4.setMode(connectingMode[gl_mode]);
        rect_5.setMode(connectingMode[gl_mode]);
        rect_6.setMode(connectingMode[gl_mode]);
        rect_7.setMode(connectingMode[gl_mode]);
        rect_8.setMode(connectingMode[gl_mode]);
        rect_9.setMode(connectingMode[gl_mode]);
        
        rect_1.update();
        rect_2.update();
        rect_3.update();
        rect_4.update();
        rect_5.update();
        rect_6.update();
        rect_7.update();
        rect_8.update();
        rect_9.update();
        
        prev_gl_mode = gl_mode;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPixelsRef pixelsRef = vidGrabber.getPixels();
    
    rect_1.draw(pixelsRef);
    rect_2.draw(pixelsRef);
    rect_3.draw(pixelsRef);
    rect_4.draw(pixelsRef);
    rect_5.draw(pixelsRef);
    rect_6.draw(pixelsRef);
    rect_7.draw(pixelsRef);
    rect_8.draw(pixelsRef);
    rect_9.draw(pixelsRef);
    
    cam.begin();
    
    rect_1.drawMesh();
    rect_2.drawMesh();
    rect_3.drawMesh();
    rect_4.drawMesh();
    rect_5.drawMesh();
    rect_6.drawMesh();
    rect_7.drawMesh();
    rect_8.drawMesh();
    rect_9.drawMesh();
    
    cam.end();
    
    ofColor(255);
    ofDrawBitmapString("Select 1 ~ 7", 100, 100);
    
    string currentModeName = modeNames[gl_mode];
    ofDrawBitmapString(currentModeName, 100, 130);
    
    
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
    
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
