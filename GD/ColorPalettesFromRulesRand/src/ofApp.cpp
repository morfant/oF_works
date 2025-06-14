#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    ofSetVerticalSync(true);

    w = ofGetWidth();
    h = ofGetHeight();
    
    
    for (int i = 0; i < tileCountX; i++)
    {
        hueValues[i] = (int)ofRandom(255);
        saturationValues[i] = (int)ofRandom(255);
        brightnessValues[i] = (int)ofRandom(255);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    counter = 0;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    
    // map mouse to grid resolution
    int currentTileCountX = (int)(ofMap(mX, 0, w, 1, tileCountX));
    int currentTileCountY = (int)(ofMap(mY, 0, h, 1, tileCountY));
    tileWidth = w / currentTileCountX;
    tileHeight = h / currentTileCountY;
    
    for (int y = 0; y < tileCountY; y++)
    {
        for (int x = 0; x < tileCountX; x++)
        {
            int index = counter % currentTileCountX;
            posX = tileWidth * x;
            posY = tileHeight * y;

            ofFill();
            ofSetColor(
                ofColor::fromHsb(
                    hueValues[index],
                    saturationValues[index],
                    brightnessValues[index]));
            
            ofDrawRectangle(posX, posY, tileWidth, tileHeight);
            counter++;
        }
    }
    
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
    
    if (key == '1')
    {
        for (int i = 0; i < tileCountX; i++)
        {
            hueValues[i] = (int)ofRandom(255);
            saturationValues[i] = (int)ofRandom(255);
            brightnessValues[i] = (int)ofRandom(255);
        }
    }
    
    if (key == '2')
    {
        for (int i = 0; i < tileCountX; i++)
        {
            hueValues[i] = (int)ofRandom(255);
            saturationValues[i] = (int)ofRandom(255);
            brightnessValues[i] = 255;
        }
    }

    if (key == '3')
    {
        for (int i = 0; i < tileCountX; i++)
        {
            hueValues[i] = (int)ofRandom(255);
            saturationValues[i] = 255;
            brightnessValues[i] = (int)ofRandom(255);
        }
    }

    if (key == '4')
    {
        for (int i = 0; i < tileCountX; i++)
        {
            hueValues[i] = (int)ofRandom(255 * 0.5);
            saturationValues[i] = (int)ofRandom(80/100.0 * 255, 255);
            brightnessValues[i] = (int)ofRandom(50/100.0 * 255, 90/100.0 * 255);
        }
    }

    if (key == '5')
    {
        for (int i = 0; i < tileCountX; i++)
        {
            if (i % 2 == 0)
            {
                hueValues[i] = (int)ofRandom(255);
                saturationValues[i] = 255;
                brightnessValues[i] = (int)ofRandom(255);
            }
            else
            {
                hueValues[i] = 195/360.0 * 255;
                saturationValues[i] = (int)ofRandom(255);
                brightnessValues[i] = 255;
            }
        }
    }


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mX = ofClamp(x, 0, w);
    mY = ofClamp(y, 0, h);
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
