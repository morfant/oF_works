#include "ofApp.h"

void ofApp::walk(){
    xold2 = xold;
    yold2 = yold;
    xold = cx;
    yold = cy;
    
    if (dir == 0) cx = cx - 1; // LEFT
    if (dir == 1) cx = cx + 1; // RIGHT
    if (dir == 2) cy = cy - 1; // UP
    if (dir == 3) cy = cy + 1; // DOWN
    
    float avgx = (cx + xold + xold2) / 3;
    float avgy = (cy + yold + yold2) / 3;
    
    ofVec2f pos(avgx, avgy);
    
    walkPaths.push_back(pos);
    
}

void ofApp::drawWalker()
{
//    let idx = wx + (height / step) * wy;

//      wold = walls[idx];

    ofSetColor(190, 120, 200);
    ofSetLineWidth(3.0);
    
    ofNoFill();
    ofBeginShape();
    for (ofVec2f p : walkPaths) {
        ofVertex((p.x + 0.5) * STEP, (p.y + 0.5) * STEP);
        // ellipse((p.x + 0.5) * step, (p.y + 0.5) * step, 10);
        // ellipse((cx + 0.5) * step, (cy + 0.5) * step, 10);
    }
    ofEndShape();
    
}

void ofApp::checkOffScreen()
{
    // print("checkOffScreen()");
    if (cx >= 0 && cx <= WIDTH / STEP && cy >= 0 && cy <= HEIGHT / STEP) {
      bounceOffWall();
    } else {
      // noLoop();
      // saveWall();
      // makeMaze();
      // init();
    }
}

void ofApp::bounceOffWall()
{
    float coin = coins[(int)cx][(int)cy];

    if (coin < 0.5) {
        
        // \
        
        
        if (dir == 0) dir = 2;
        else if (dir == 1) dir = 3;
        else if (dir == 2) dir = 0;
        else if (dir == 3) dir = 1;
    } else {
        // /
        
        
        if (dir == 0) dir = 3;
        else if (dir == 1) dir = 2;
        else if (dir == 2) dir = 1;
        else if (dir == 3) dir = 0;
    }
}

void ofApp::reset()
{
    cx = cy = xold = yold = xold2 = yold2 = -1;
    dir = round(ofRandom(3));
    walkPaths.clear();
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);
    xold = yold = xold2 = yold2 = -1;
    WIDTH = ofGetWidth();
    HEIGHT = ofGetHeight();
    
    // makeMaze
    for (int i = 0; i < NUM_X; i++) {
        for (int j = 0; j < NUM_Y; j++) {
            coins[i][j] = ofRandom(1.0);
        }
    }
    
    dir = round(ofRandom(3.0));
    cx = round(ofRandom(WIDTH));
    cy = round(ofRandom(HEIGHT));
//    cx = 10;
//    cy = 12;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(bgColor);

    // drawMaze
    for (int i = 0; i < NUM_X; i++) {
        for (int j = 0; j < NUM_Y; j++) {
            
            ofPushMatrix();
            ofTranslate(STEP * i, STEP * j);
            
            ofSetColor(lineColor);
            ofSetLineWidth(1.f);
            if (coins[i][j] < 0.5)
            {
                ofDrawLine(0, 0, STEP, STEP);
            }
            else
            {
                ofDrawLine(STEP, 0, 0, STEP);
            }
            
            ofPopMatrix();

        }
    }
    
    if (isStarted == true)
    {
        walk();
        checkOffScreen();
        drawWalker();
    }

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 32) {
      reset();
      isStarted = false;
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
    if (isStarted == false) {
        isStarted = true;
        cx = (x / STEP);
        cy = (y / STEP);
        xold2 = xold = cx;
        yold2 = yold = cy;
        
        
        cout << "x: " << cx << " / y: " << cy << endl;
//      print(mouseX + " / " + mouseY);
//      print(wx + " / " + wy);
    }
    
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
