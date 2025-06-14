#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
   
    if (video.load("video2.mp4"))
    {
        w = video.getWidth();
        h = video.getHeight();
//        video.setLoopState(OF_LOOP_NORMAL);
        video.play();
        texture.allocate(w, h, GL_RGB);
    }
    else
    {
        ofLogError() << "Video failed to load!";
    }
    
  
    for (int i = 0; i < numSpheres; i++)
    {
         glm::vec3 _pos(
            ofRandom(-800, 800),
            ofRandom(-800, 800),
            ofRandom(-800, 800)
        );
           
        shared_ptr<TexSphere> sp = make_shared<TexSphere>(
            _pos, ofRandom(40, 80), ofRandomf() * 2.0, ofVec2f(w, h)
        );
        spheres.push_back(sp);
        shared_ptr<glm::vec3> pos = make_shared<glm::vec3>(_pos);
        positions.push_back(pos);
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    
    video.update();
    if (video.isFrameNew())
    {
        texture.loadData(video.getPixels());
    }
    
    for (int i = 0; i < spheres.size(); i++)
    {
        spheres.at(i)->update();
        spheres.at(i)->getTexture(texture);
    }
   
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    ofEnableDepthTest();
    
    for (int i = 0; i < spheres.size(); i++)
    {
        spheres.at(i)->draw();
    }
    
    
    // Draw lines
    for (int i = 0; i < positions.size() - 1; i++)
    {
        for (int j = 0; j < positions.size(); j++)
        {
            if (i != j)
            {
                glm::vec3 begin = *(positions.at(i));
                glm::vec3 end = *(positions.at(j));
                
                ofSetColor(33, 158, 188, 100);
                ofSetLineWidth(0.1);
                ofDrawLine(begin, end);
            }
        }
    }
    
    
    
    cam.end();

}

//--------------------------------------------------------------
void ofApp::exit(){
    
    spheres.clear();
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
