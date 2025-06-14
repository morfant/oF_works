#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    ofSetVerticalSync(true);
    ofBackground(255);

    width = ofGetWidth();
    height = ofGetHeight();
    
    fbo.allocate(width, height);
    
    
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
     
    if (enableLoop == true)
    {
        fbo.begin();
        ofBackground(255);
        fbo.end();
        
        float rowCount = ofRandom(5, 30);
        float rowHeight = height / rowCount;
        
        for (int i = 0; i < rowCount; i++)
        {
            int partsCount = i + 1;
            vector<float> parts; // store width of each cells on a row
            
            for (int p = 0; p < partsCount; p++)
            {
                if (abs(ofRandomf()) < 0.05)
                {
                    int numFragments = ofRandom(2, 10);
                    partsCount += numFragments;
                    for (int n = 0; n < numFragments; n++)
                    {
                        parts.push_back(ofRandomf() + 1);
                    }
                }
                else
                {
                    parts.push_back(ofRandom(2, 20));
                }
                
            }
           
            // sum of all cell's width
            double sumWidthAllParts = 0;
            for (int s = 0; s < partsCount; s++)
            {
                if (parts.size() > 0)
                {
                    sumWidthAllParts += parts.at(s);
                }
            }
            
            double sumWidthCurrentParts = 0;
            for (int n = 0; n < parts.size(); n++)
            {
                sumWidthCurrentParts += parts.at(n);
                
                double x = ofMap(sumWidthCurrentParts - parts.at(n), 0, sumWidthAllParts, 0, width);
                double y = rowHeight * i;
                double w = ofMap(parts.at(n), 0, sumWidthAllParts, 0, width);
                double h = rowHeight;
                
                
                int index = counter % tileCountX;
                
                fbo.begin();
                ofFill();
                ofSetColor(
                           ofColor::fromHsb(
                                            hueValues[index],
                                            saturationValues[index],
                                            brightnessValues[index]));
                
                ofDrawRectangle(x, y, w, h);
                fbo.end();
                
                counter++;
            }
        }
        enableLoop = false;
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
    if (button == 0) enableLoop = true;

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
