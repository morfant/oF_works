#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    /* basic steup */
    
//    //Set projection width / height
//    int pjW = 1600;
//    int pjH = 900;
//    
//    float winPosX = (pjW - ofGetWidth())/2.f;
//    float winPosY = (pjH - ofGetHeight())/2.f;
//    
    if (REALTIME){
        cout << "REALTIME!" << endl;
        windowPosition = ofPoint(1440, 0);
        ofSetWindowPosition(windowPosition.x, windowPosition.y);
        ofToggleFullscreen();
        infoDisplay = false;
    }else{
        cout << "NOT REALTIME!" << endl;
        windowPosition = ofPoint(0, 0);
        ofSetWindowPosition(windowPosition.x, windowPosition.y);
        infoDisplay = true;
    }
    
    /* BALL */
    for (int i = 0; i < BALL_NUM; i++){
        curBalls[i] = NULL;
    }
    
    /* OFXOSC */
    oscRecvThr[0] = 0.02;
    oscRecvThr[1] = 0.04;
    oscRecvThr[2] = 0.01;
    
    for (int i = 0; i < CH_NUM; i++){
        oscRecvVal[i] = 0;
        oscAddrs[i] = "/ch" + std::to_string(i);
//        cout << oscAddrs[i] << endl;
    }
    
	// listen on the given OSC_RECV_PORT
	cout << "listening for osc messages on OSC_RECV_PORT " << OSC_RECV_PORT << "\n";
	receiver.setup(OSC_RECV_PORT);
	current_msg_string = 0;

    
    /* OFXBOX2D */
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createBounds();
	box2d.setFPS(60.0);
	box2d.registerGrabbing();
    
	ofBackground(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){

   
    /* OFXBOX2D */
	box2d.update();
    
    
    /* OFXOSC */
	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}
    
//    for (int i = 0; i < 8; i++){
//        oscRecvVal[i] = 0;
//    }
//
    
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);
        
        if (!REALTIME) {
            cout << "osc recv: " << m.getArgAsFloat(0) << endl;
        }
        
        /*
            ch0: teum 
            ch1: bae
            ch2: linear 
        */
        
        
        for (int i = 0; i < CH_NUM; i++){
            if (m.getAddress() == oscAddrs[i]) {
//                oscRecvVal[i] = m.getArgAsFloat(0);
                oscRecvVal[i%3] = m.getArgAsFloat(0);
//                cout << oscRecvVal[i%3] << endl;
                
                if (curBalls[i%3] != NULL) {
//                if (curBalls[i] != NULL) {
//                if (curBalls.at(i) != NULL) {
//                    cout << "addText(): " << (i%CH_NUM) << endl;
//                    balls.at(i%CH_NUM)->addText(std::to_string(oscRecvVal[i]));
//                    curBalls[i]->addText(std::to_string(oscRecvVal[i]));
                    if (oscRecvVal[i%3] > oscRecvThr[i%3]){
                        curBalls[i%3]->addText(std::to_string(oscRecvVal[i%3]));
                        
//                        if (oscRecvVal[i%3] > LOUD_LEVEL) {
//                            // switch text
//                            for (vector<Ball*>::iterator it = balls.begin(); it != balls.end(); it++) {
//                                (*it)->switchText("future of");
//                            }
//                        }
//                        
                        // revert text normally.
//                        for (vector<Ball*>::iterator it = balls.begin(); it != balls.end(); it++) {
//                            (*it)->revertText();
//                        }
//                        
                    };
                     
                   
                }
                
//                cout << oscAddrs[i] << "-" << i << "-" << oscRecvVal[i] << endl;
            } else {
                // unrecognized message: display on the bottom of the screen
                string msg_string;
                msg_string = m.getAddress();
                msg_string += ": ";
                for(int i = 0; i < m.getNumArgs(); i++){
                    // get the argument type
                    msg_string += m.getArgTypeName(i);
                    msg_string += ":";
                    // display the argument - make sure we get the right type
                    if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                        msg_string += ofToString(m.getArgAsInt32(i));
                    }
                    else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                        msg_string += ofToString(m.getArgAsFloat(i));
                    }
                    else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                        msg_string += m.getArgAsString(i);
                    }
                    else{
                        msg_string += "unknown";
                    }
                }
                // add to the list of strings to display
                msg_strings[current_msg_string] = msg_string;
                timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
                current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
                // clear the next line
                msg_strings[current_msg_string] = "";
                           
                }
            }
//
//        if(m.getAddress() == "/ch1"){
//            
//		} else if(m.getAddress() == "/ch2"){
//			// both the arguments are int32's
//            oscRecvVal[1] = m.getArgAsFloat(1);
//            cout << "ch2 received" << endl;
//		} else if(m.getAddress() == "/ch3"){
//			mouseButtonState = m.getArgAsString(0);
//		} else if(m.getAddress() == "/ch4"){
//			// the single argument is a string
//			mouseButtonState = m.getArgAsString(0);
//		} else if(m.getAddress() == "/ch5"){
//			// the single argument is a string
//			mouseButtonState = m.getArgAsString(0);
//		} else if(m.getAddress() == "/ch6"){
//			// the single argument is a string
//			mouseButtonState = m.getArgAsString(0);
//		} else if(m.getAddress() == "/ch7"){
//			// the single argument is a string
//			mouseButtonState = m.getArgAsString(0);
//		} else if(m.getAddress() == "/ch8"){
//			// the single argument is a string
//			mouseButtonState = m.getArgAsString(0);
//		} else{
//			// unrecognized message: display on the bottom of the screen
//			string msg_string;
//			msg_string = m.getAddress();
//			msg_string += ": ";
//			for(int i = 0; i < m.getNumArgs(); i++){
//				// get the argument type
//				msg_string += m.getArgTypeName(i);
//				msg_string += ":";
//				// display the argument - make sure we get the right type
//				if(m.getArgType(i) == OFXOSC_TYPE_INT32){
//					msg_string += ofToString(m.getArgAsInt32(i));
//				}
//				else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
//					msg_string += ofToString(m.getArgAsFloat(i));
//				}
//				else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
//					msg_string += m.getArgAsString(i);
//				}
//				else{
//					msg_string += "unknown";
//				}
//			}
//			// add to the list of strings to display
//			msg_strings[current_msg_string] = msg_string;
//			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
//			current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
//			// clear the next line
//			msg_strings[current_msg_string] = "";
//		}

	}
    
    /* BALL */
//    for (int i = 0; i < BALL_NUM; i++){
//        if (balls[i] != NULL) {
//            balls[i]->update();
//        }
//    }
//
    for (int i = 0; i < balls.size(); i++){
//        if (balls[i] != NULL) {
            balls[i]->update();
//        }
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    

    /* OFXBOX2D */
	// draw the ground
	box2d.drawGround();
	
    
    /* info display */
    if (infoDisplay) {
        string info = "";
        info += "Press [c] for circles\n";
        info += "Press [b] for blocks\n";
        info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
        info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
        info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
        ofSetHexColor(0xff1111);
        ofDrawBitmapString(info, 30, 30);
    }
    
    /* BALL */
    
    //circle color
//    if (colorGray) {
//        ofSetHexColor(0x444342);
//        
//    } else {
//        ofSetHexColor(0xffffff);
//    }
    
    for (int i = 0; i < balls.size(); i++){
        balls[i]->draw();
    }
    
    /* OSC */
//	string buf;
//	buf = "listening for osc messages on OSC_RECV_PORT" + ofToString(OSC_RECV_PORT);
//	ofDrawBitmapString(buf, 10, 20);
//    
//    if(receivedImage.getWidth() > 0){
//        ofDrawBitmapString("Image:", 10, 160);
//        receivedImage.draw(10, 180);
//    }
//
//	// draw mouse state
//	buf = "mouse: " + ofToString(mouseX, 4) +  " " + ofToString(mouseY, 4);
//	ofDrawBitmapString(buf, 430, 20);
//	ofDrawBitmapString(mouseButtonState, 580, 20);
//
//	for(int i = 0; i < NUM_MSG_STRINGS; i++){
//		ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
//	}



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    float mx = ofGetMouseX();
    float my = ofGetMouseY();
    
    /* set color */
	if(key == 'c') {
        for (vector<Ball*>::iterator it = balls.begin();
             it != balls.end(); it++) {
             (*it)->setColor(0xffffff);
        }
        cout << "setColor ffffff" << endl;
	}
    
    if(key == 'v') {
        for (vector<Ball*>::iterator it = balls.begin();
             it != balls.end(); it++) {
             (*it)->setColor(0x444342);
        }
        
        cout << "setColor 444342" << endl;
	}
	
	if(key == 'b') {
		float w = ofRandom(4, 20);
		float h = ofRandom(4, 20);
		boxes.push_back(shared_ptr<ofxBox2dRect>(new ofxBox2dRect));
		boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
		boxes.back().get()->setup(box2d.getWorld(), mx, my, w, h);
	}
	
	if(key == 't') ofToggleFullscreen();
    
    
    if(key == '1'){
//        if (curBalls[0] == NULL) {
            Ball* aBall = new Ball(&box2d, 300, 100, RAD, false);
//            Ball* aBall = new Ball(&box2d, 900, 100, RAD, false);
            curBalls[0] = aBall;
            balls.push_back(aBall);
//        }
        
    } else if (key == '2') {
        Ball* aBall = new Ball(&box2d, 600, 100, RAD, false);
//        Ball* aBall = new Ball(&box2d, 300, 100, RAD, false);
        curBalls[1] = aBall;
        balls.push_back(aBall);
    } else if (key == '3') {
        Ball* aBall = new Ball(&box2d, 900, 100, RAD, false);
//        Ball* aBall = new Ball(&box2d, 600, 100, RAD, false);
        curBalls[2] = aBall;
        balls.push_back(aBall);
    }
    
    if (key == 'f'){
        // change all strings to 'future of ' temporary
        for (vector<Ball*>::iterator it = balls.begin();
             it != balls.end(); it++) {
            (*it)->switchText("future of");
        }
    }
    
    if (key == 'g'){
        for (vector<Ball*>::iterator it = balls.begin();
             it != balls.end(); it++) {
            (*it)->revertText();
        }
    }
    
    if (key == 'q') {
        cout << "applyPhysics(TRUE)" << endl;
        curBalls[0]->applyPhysics(TRUE);
//        curBalls[1]->applyPhysics(TRUE);
//        curBalls[2]->applyPhysics(TRUE);
    }
    
    if (key == 'a') {
        cout << "applyPhysics(FALSE)" << endl;
        curBalls[0]->applyPhysics(FALSE);
//        curBalls[1]->applyPhysics(FALSE);
//        curBalls[2]->applyPhysics(FALSE);
    }
    
    /* set oscRecvThr */
    if (key == 'p') {
        if (oscRecvThr[2] <= 0.98){
            oscRecvThr[2]+=0.01;
            cout << "oscRecvThr[2]: " << oscRecvThr[2] << endl;
        }
    }
    
    if (key == 'l') {
        if (oscRecvThr[2] >= 0.01){
            oscRecvThr[2]-=0.01;
            cout << "oscRecvThr[2]: " << oscRecvThr[2] << endl;
        }
    }
    
    if (key == 'o') {
        if (oscRecvThr[1] <= 0.98){
            oscRecvThr[1]+=0.01;
            cout << "oscRecvThr[1]: " << oscRecvThr[1] << endl;
        }
    }
    
    if (key == 'k') {
        if (oscRecvThr[1] >= 0.01){
            oscRecvThr[1]-=0.01;
            cout << "oscRecvThr[1]: " << oscRecvThr[1] << endl;
        }
    }
    
    if (key == 'i') {
        if (oscRecvThr[0] <= 0.98){
            oscRecvThr[0]+=0.01;
            cout << "oscRecvThr[0]: " << oscRecvThr[0] << endl;
        }
    }
    
    if (key == 'j') {
        if (oscRecvThr[0] >= 0.01){
            oscRecvThr[0]-=0.01;
            cout << "oscRecvThr[0]: " << oscRecvThr[0] << endl;
        }
    }
    
    /* erase */
    if (key == 'r') {
         for (vector<Ball*>::iterator it = balls.begin(); it != balls.end(); it++) {
//             oscRecvThr[0] = 1;
//             oscRecvThr[1] = 1;
//             oscRecvThr[2] = 1;
             
//            (*it)->eraseText(100);
             
        }
        
        int lastIdx = balls.size() - 1;
        if (lastIdx >= 0) {
            delete balls[lastIdx];
            balls.pop_back();
        }
        
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
