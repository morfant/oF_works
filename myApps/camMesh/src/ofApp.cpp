#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
    ofBackground(0,0,0);
    ofEnableAlphaBlending();

	camWidth = 640;
	camHeight = 480;
	
	vidGrabber.setVerbose(true);
	vidGrabber.setup(camWidth, camHeight);
    
    stepX = camWidth / num_x;
    stepY = camHeight / num_y;
    
    for (int y = 0; y < num_y; ++y) {
        for (int x = 0; x < num_x; ++x) {
            mesh.addVertex(ofPoint(x * stepX, y * stepY, 0));
            mesh.addColor(ofColor(255, 255, 255));
        }
    }
   
}


//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
    
    // mode 선택
    if (prev_gl_mode != gl_mode) {
        mesh.setMode(connectingMode[gl_mode]);
        
        for (int y = 0; y < num_y - 1; ++y) {
            for (int x = 0; x < num_x - 1; ++x) {
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
   

}

//--------------------------------------------------------------
void ofApp::draw(){
	
//    vidGrabber.draw(0,0); // cam으로 들어오는 frame을 캔버스 0, 0 좌표에 그린다

	ofPixelsRef pixelsRef = vidGrabber.getPixels();
    
    for (int y = 0; y < num_y; ++y) {
        for (int x = 0; x < num_x; ++x) {
            
            int xPos = x * stepX;
            int yPos = y * stepY;
            
            // get the pixel and its lightness (lightness is the average of its RGB values)
            float lightness = pixelsRef.getColor(xPos,yPos).getLightness();
            
            int idx = x + (num_x * (num_y - 1 - y));
//            int idx = x + (num_x * y);
            ofPoint v = mesh.getVertex(idx);
            
            v.z = lightness;
            mesh.setVertex(idx, v);
            ofColor c(v.z, 100 + v.z/2, 120);
            mesh.setColor(idx, c);
            
        }
    }
  
    cam.begin();
    mesh.draw();
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
