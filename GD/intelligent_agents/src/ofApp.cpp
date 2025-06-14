#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(10);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    w = ofGetWidth();
    h = ofGetHeight();
    
    posX = posXCross = w * 0.5;
    posY = posYCross = h * 0.5;
    
    float stepAngle = 360 / (angleCount * 4);
    angle = ofRandom(angleCount * 4) * stepAngle;
    
    fbo.allocate(w, h, GL_RGBA);
    fbo.begin();
    ofClear(255, 255, 255, 255);
    fbo.end();

    pixels.allocate(w, h, OF_PIXELS_RGB);

}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < speed; i++)
    {
//        fbo.begin();
//        ofFill();
//        ofSetColor(0);
//        ofDrawCircle(posX, posY, 2);
//        fbo.end();
        
        posX += stepSize * cos(angle);
        posY += stepSize * sin(angle);
        
        reachedBorder = false;
        if (posY <= 5)
        {
            dir = direction::SOUTH;
            reachedBorder = true;
        }
        else if (posY >= h - 5)
        {
            dir = direction::NORTH;
            reachedBorder = true;
        }
        else if (posX <= 5)
        {
            dir = direction::EAST;
            reachedBorder = true;
        }
        else if (posX >= w - 5)
        {
            dir = direction::WEST;
            reachedBorder = true;
        }
        
        
        fbo.readToPixels(pixels);
        ofColor c = pixels.getColor(posX, posY);
        
        if ((c.r != 255 && c.g != 255 && c.b != 255) || reachedBorder == true)
        {
            angle = ofDegToRad(getRandomAngle(dir));
//            cout << "New angle! : " << angle << " -> " << reachedBorder << endl;

            float d = ofDist(posX, posY, posXCross, posYCross);
//            cout << d << endl;
            
            if (d >= minLength)
            {
                fbo.begin();
                ofSetColor(0, 0, 0, 90 + d/3);
//                ofColor c = ofColor::fromHsb(0, 255, 10 + d/3);
//                ofSetColor(c);
                drawRoundedLine(ofVec2f(posX, posY), ofVec2f(posXCross, posYCross), d/48);
                fbo.end();
            }
            
            posXCross = posX;
            posYCross = posY;
            
        }
        
    }


}

void ofApp::drawRoundedLine(ofPoint start, ofPoint end, float thickness) {
    // 두 점을 기준으로 벡터 계산
    ofVec2f direction = (end - start).normalize();
    ofVec2f perpendicular(-direction.y, direction.x); // 수직 벡터

    // 선 그리기
    ofBeginShape();
    ofVertex(start - perpendicular * thickness / 2);
    ofVertex(start + perpendicular * thickness / 2);
    ofVertex(end + perpendicular * thickness / 2);
    ofVertex(end - perpendicular * thickness / 2);
    ofEndShape(true);

    // 둥근 끝 부분 추가
    ofSetCircleResolution(50); // 해상도 설정
    ofDrawCircle(start, thickness / 2);
    ofDrawCircle(end, thickness / 2);
}

void ofApp::drawThickLine(ofPoint start, ofPoint end, float thickness) {
    ofVec2f direction = (end - start).normalize();
    ofVec2f perpendicular(-direction.y, direction.x);

    ofBeginShape();
    ofVertex(start - perpendicular * thickness / 2);
    ofVertex(start + perpendicular * thickness / 2);
    ofVertex(end + perpendicular * thickness / 2);
    ofVertex(end - perpendicular * thickness / 2);
    ofEndShape(true);
}


int ofApp::getRandomAngle(direction dir)
{
    int a = (floor(ofRandom(-angleCount, angleCount)) + 0.5) * 90 / angleCount;
    
    if (dir == direction::NORTH) return a - 90;
    else if (dir == direction::EAST) return a;
    else if (dir == direction::SOUTH) return a + 90;
    else if (dir == direction::WEST) return a + 180;
    else return 0;
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    fbo.draw(0,  0);
        


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
