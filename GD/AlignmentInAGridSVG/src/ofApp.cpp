#include "ofApp.h"

float tileCount = 20;
float step;
int width, height;
int mX, mY;
int theSeed = 0;


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    width = ofGetWidth();
    height = ofGetHeight();
    step = width / tileCount;
    
    svg.load("module_1.svg");

}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    tileCount = 20;
    step = width / tileCount;

    ofBackground(255);
    ofSetColor(0);
    
    for (int y = 0; y < tileCount; y++)
    {
        for (int x = 0; x < tileCount; x++)
        {
            
            float posX = x * step;
            float posY = y * step;
            float dist = ofDist(posX, posY, mX, mY);
            dist = ofClamp(dist, 0, 510);

            float angle = atan2(mY - posY, mX - posX) + ofDegToRad(90);
            ofPushMatrix();
            float svgWidth = svg.getWidth();
            float svgHeight = svg.getHeight();
            ofTranslate(posX + (svgWidth * 0.5), posY + (svgHeight * 0.5));
            ofRotateZRad(angle);
            ofTranslate(-svgWidth * 0.5, -svgHeight * 0.5);
            
            float scl = ofMap(dist, 100, 510, 0.1, 2.0);
            ofScale(scl, scl);
            
            float alpha = ofMap(dist, 100, 510, 0, 255);
            // SVG의 모든 경로에 대해 투명도 설정
            
            setSVGColor(svg, 0, 0, 0, alpha);
           
            svg.draw();
            ofPopMatrix();
            
        }
    }
    
    
    ofSetColor(255, 0, 0);
    ofDrawBitmapString("Press 1 ~ 7\nto switch a svg on each grid.", width * 0.7, height * 0.1);
        

}

void ofApp::setSVGColor(ofxSvg& src, int r, int g, int b, float a){
    
    // set color of all pathes that consist of the svg
    for (int i = 0; i < src.getNumPath(); i++) {
        ofPath &path = src.getPathAt(i);
        
        // 경로의 기존 색상을 가져와 알파 값을 수정
        ofColor fillColor = path.getFillColor();
//        fillColor.r = r;
//        fillColor.g = g;
        fillColor.b = b;
        fillColor.a = a;
        path.setFillColor(fillColor);

        ofColor strokeColor = path.getStrokeColor();
//        strokeColor.r = r;
//        strokeColor.g = g;
        strokeColor.b = b;
        strokeColor.a = a;
        path.setStrokeColor(strokeColor);
    }
    
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == '1') svg.load("module_1.svg");
    if (key == '2') svg.load("module_2.svg");
    if (key == '3') svg.load("module_3.svg");
    if (key == '4') svg.load("module_4.svg");
    if (key == '5') svg.load("module_5.svg");
    if (key == '6') svg.load("module_6.svg");
    if (key == '7') svg.load("module_7.svg");
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mX = ofClamp(x, 0, width);
    mY = ofClamp(y, 0, height);

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (button == 0)
    {
        theSeed = ofRandom(2000);
    }

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
