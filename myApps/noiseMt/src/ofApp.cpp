#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofBackground(255);
    
    cout << ofGetWidth() << ofGetHeight() << endl;
    float stepWidth = ofGetWidth()/(float)width;
    float stepHeight = ofGetHeight()/(float)height;
    cout << stepWidth << endl;
    
//    mesh.setMode(OF_PRIMITIVE_LINES);
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            mesh.addVertex(ofPoint(x * stepWidth, y * stepHeight, 0)); // make a new vertex
            mesh.addColor(ofFloatColor(0,0,0));  // add a color at that vertex
        }
    }

    // now it's important to make sure that each vertex is correctly connected with the
    // other vertices around it. This is done using indices, which you can set up like so:
    for (int y = 0; y < height - 1; y++){
        for (int x = 0; x < width - 1; x++){
            mesh.addIndex(x + y * width);               // 0, 0
            mesh.addIndex((x + 1) + y * width);           // 1, 0
            mesh.addIndex(x + (y + 1) * width);           // 0, width

            mesh.addIndex((x + 1) + y * width);           // 1, 0
            mesh.addIndex((x + 1) + (y + 1) * width);       // 1, width
            mesh.addIndex(x + (y + 1) * width);           // 0, width
            
            // make connection order : 0 - 1 - 10 - 1 - 11 - 10
        }
    }

    
//    cam.setScale(1,-1,1);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            
            int idx = width * y + x;
            
            glm::vec3 tmpVec = mesh.getVertex(idx);
            tmpVec.z = 200.0f * ofNoise(idx/10.f + ofGetFrameNum()/100.0f);
            mesh.setVertex(idx, tmpVec);
//            cout << "tmpVec.z: " << tmpVec.z << endl;

            ofFloatColor sampleColor(tmpVec.z/100.f, 0.5f, 0.5f);
            mesh.setColor(idx, sampleColor);
        }
    }


    
    //let's move the camera when you move the mouse
    float rotateAmount = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, TWO_PI);
    cout << rotateAmount << endl;

    //move the camera around the mesh
    glm::vec3 camDirection(0,0,1);
    glm::vec3 centre(ofGetWidth()/2.f,ofGetHeight()/2.f, 255/2.f);
    glm::vec3 camDirectionRotated = glm::rotate(camDirection, rotateAmount, glm::vec3(1,0,0));
    float camDist = ofMap(ofGetMouseX(), 0, ofGetWidth(), 100.f, 1000.f);
    glm::vec3 camPosition = centre + camDirectionRotated * camDist;
    
    cam.setPosition(camPosition);
    cam.lookAt(centre);

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    mesh.draw();
//    mesh.drawFaces();
//    mesh.drawWireframe();
    
    cam.end();


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
