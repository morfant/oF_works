#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    w = ofGetWidth();
    h = ofGetHeight();
    fbo.allocate(w, h, GL_RGBA);
    
    fbo.begin();
    ofBackground(255);
    ofEnableBlendMode(OF_BLENDMODE_ADD); // 더해질 수록 진해져서 원래 색을 찾는다
    fbo.end();
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (isClickedL == true)
    {
        int circleResolution = ofMap(ofGetMouseY(), 0, h, 2, 80);
        int radius = ofGetMouseX() - w * 0.5 + 0.5;
        float angle = TWO_PI / circleResolution;
    //    cout << circleResolution << " / " << radius << " / " << angle << endl;
        
        fbo.begin();
        ofTranslate(w * 0.5, h * 0.5);
        glEnable(GL_LINE_SMOOTH);     // 선 부드럽게
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // 최고품질로
        ofSetLineWidth(0.1);
        
        for (int i = 0; i < circleResolution; i++)
        {
            float x = cos(angle * i) * radius;
            float y = sin(angle * i) * radius;
            
            polyline.addVertex(x, y);
        }
        polyline.close();
        
        ofSetColor(strokeColor);
        polyline.draw();
        polyline.clear();
        fbo.end();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
   
    fbo.draw(0, 0);

}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's'){
        string fileName = PROJECTNAME + "_" + ofGetTimestampString("%Y-%m-%d-%H-%M-%S") + ".png";
        
        ofSaveScreen(fileName);
        cout << "Screenshot saved as: " << fileName << endl;
    }
    
    if (key == '1') strokeColor = ofColor::fromHsb(0, 0, 0, 10);
    if (key == '2') strokeColor = ofColor::fromHsb(
                        ofMap(192, 0, 360, 0, 255),
                        ofMap(100, 0, 100, 0, 255),
                        ofMap(64, 0, 100, 0, 255),
                        ofMap(10, 0, 100, 0, 255)
                                                   );
    if (key == '3') strokeColor = ofColor::fromHsb(
                        ofMap(52, 0, 360, 0, 255),
                        ofMap(100, 0, 100, 0, 255),
                        ofMap(71, 0, 100, 0, 255),
                        ofMap(10, 0, 100, 0, 255)
                                                   );
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
    if (button == 0) isClickedL = true;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (button == 0) isClickedL = false;

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
