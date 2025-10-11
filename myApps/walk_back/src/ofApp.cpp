#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(60);
	
	realTime = false;
		
	//MIDI SETTING
    midiIn.listInPorts();
	midiIn.openPort(1); //check device number in console
	midiIn.addListener(this);
	
	//BSmanager
	man = new BSmanage();
	man->init(BALL_NUM, BAR_NUM, BH_NUM); //baNum, stNum
//	stk->init(0, ofGetHeight() - 200, ofGetWidth(), ofGetHeight() - 400);

    
    angleStep = 3.141592 / 360;
	BlackHoleDraw = false;

	midiConReverse = false;
	midiContAll = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    	
//	cout << ofGetFrameRate() << endl;
	
	ofBackground(255, 255, 255);
    	
	for (int i = 0; i < man->balls.size(); i++) {
		man->balls[i]->update(10);
	}
	
	if (BlackHoleDraw) {
		for (int i = 0; i < man->bHoles.size(); i++) {
			int tRand = (int)ofRandom(277);
			man->bHoles[i]->update(tRand, 600, 350); //rotate rate, posX, posY
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){

#ifdef DEBUG_MODE
    ofSetHexColor(0x005555);
    sprintf(tempStr, "FPS: %f", ofGetFrameRate());
    ofDrawBitmapString(tempStr, ofGetWidth() * 7/8, ofGetHeight() * 1/12 - 30 );
    sprintf(tempStr, "number of balls: %lu", man->balls.size());
    ofDrawBitmapString(tempStr, ofGetWidth() * 7/8 - 30, ofGetHeight() * 1/12 - 50 );
#endif
		
	//BAR
	for (int i = 0; i < BAR_NUM; i++) {
		for (int j = 0; j < man->balls.size(); j++) {
			man->update(man->stks[i], man->balls[j]); //stk*, ball*
			man->bsHitCheck(man->stks[i], man->balls[j], i);
		}
	}
		
	//BALL
	int tRan = (int)ofRandom(4);
	for(int i = 0; i < man->balls.size(); i++){
		man->balls[i]->display(0x002266 + i*100, 3 + tRan, TWO_PI/(3 + tRan), 0, true);		
		man->balls[i]->checkBorder(0, 0, ofGetWidth(), ofGetHeight());
	}
	
	
	if (BlackHoleDraw) {
		//BLACK HOLE
		for(int i = 0; i < man->bHoles.size(); i++){
			int tStep = 3 + (int)ofRandom(2);
			int tNshape = (int)ofRandom(70);
			//		int tCol = (int)ofRandom(255);
			man->bHoles[i]->display(0x000000, tNshape, tStep, 0, BLACKHOLE_SIZE, true);		
            man->bHoles[i]->checkBorder(0, 0, ofGetWidth(), ofGetHeight());            
			//Ball::display(int _color, float _lineWidth, int _numShape, float _step, float _angle, float _radius, bool _isFill)
		}
	
        for (int i = 0; i < man->bHoles.size(); i++) {
            for (int j = 0; j < man->balls.size(); j++) {
                man->checkEatBall(man->bHoles[i], man->balls[j], j);
            }
        }

        
        
	}
}

//----------MIDI MSG RECEIVE FUNCTION--------------

void ofApp::newMidiMessage(ofxMidiMessage& message) {
	id = message.channel;
	port = message.portNum;

	// only handle control change messages to avoid spurious updates
	if(message.status == MIDI_CONTROL_CHANGE) {
		if (message.control < BAR_NUM ) {
			currentCnum = message.control;
		}

		if(id == MIDI_CHANNEL) {
			value[currentCnum] = message.value;
		}

		if (midiContAll) {
			for (int i = 0; i < BAR_NUM; i++) {
				midiControlBar(i);
			}
		} else {
			midiControlBar(currentCnum);
		}
	}
}

void ofApp::midiControlBar(int ccNum)
{
	sLength[ccNum] = ceil(man->stks[ccNum]->baseLength);
	
	if (!midiConReverse) {
		man->stks[ccNum]->base1.x += 1;
		man->stks[ccNum]->base1.y -= (sin(angleStep) * (sLength[ccNum] / 2));
		man->stks[ccNum]->base2.x -= 1;
		man->stks[ccNum]->base2.y += (sin(angleStep) * (sLength[ccNum] / 2));
		
	} else {
		man->stks[ccNum]->base1.x += 1;
		man->stks[ccNum]->base1.y += (sin(angleStep) * (sLength[ccNum] / 2));
		man->stks[ccNum]->base2.x -= 1;
		man->stks[ccNum]->base2.y -= (sin(angleStep) * (sLength[ccNum] / 2));
		
	}
	
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	for (int i = 0; i < BAR_NUM; i++) {
		sLength[i] = ceil(man->stks[i]->baseLength);
	}

//    int yOffset = 200;
//    float ttPI = 0;
//    float rotStep = 3.141592 / 180;
	switch (key) {
		case OF_KEY_UP:
                        
			for (int i = 0; i < BAR_NUM; i++) {
				man->stks[i]->base1.x += 1;
				man->stks[i]->base1.y -= (sin(angleStep) * (sLength[i] / 2));
				man->stks[i]->base2.x -= 1;
				man->stks[i]->base2.y += (sin(angleStep) * (sLength[i] / 2));
				
			}
			
//			cout<<man->stks[0]->base1.x << " : " << man->stks[0]->base1.y << endl;
//			cout<<sin(3.14/2)<<endl;
//			cout<<"tPI "<<tPI<<endl;            
//			cout<<"dist between begin, end"<<ofDist(man->stks[0]->base1.x, man->stks[0]->base1.y, man->stks[0]->base2.x, man->stks[0]->base2.y) << endl;

			break;
            
		case OF_KEY_DOWN:
            
			for (int i = 0; i < BAR_NUM; i++) {
				man->stks[i]->base1.x += 1;
				man->stks[i]->base1.y += (sin(angleStep) * (sLength[i] / 2));
				man->stks[i]->base2.x -= 1;
				man->stks[i]->base2.y -= (sin(angleStep) * (sLength[i] / 2));
				
			}
			
//			cout<<man->stks[0]->base1.x << " : " << man->stks[0]->base1.y << endl;
//			cout<<sin(3.14/2)<<endl;
//			cout<<"tPI "<<tPI<<endl;                        
//            cout<<"dist between begin, end"<<ofDist(man->stks[0]->base1.x, man->stks[0]->base1.y, man->stks[0]->base2.x, man->stks[0]->base2.y) << endl;
			
			break;
			
        case 'h':
			if(!BlackHoleDraw){
				BlackHoleDraw = true;
				man->oscSend1("BLACKHOLE", 1);
				cout << "BH!" <<endl;
			}
			else{
				BlackHoleDraw = false;
				man->oscSend1("BLACKHOLE", 0);
			}
            break;

        case 'H':
			if(!BlackHoleDraw){
				BlackHoleDraw = true;
				man->oscSend1("BLACKHOLE", 1);				
				cout << "BH!" <<endl;
			}
			else{
				BlackHoleDraw = false;
				man->oscSend1("BLACKHOLE", 0);
			}
            break;
			
			
        case 't':
			if(!midiConReverse){
				midiConReverse = true;
				cout << "MIDI CON REVERSE!" <<endl;
			}
			else midiConReverse = false;
            break;

        case 'T':
			if(!midiConReverse){
				midiConReverse = true;
				cout << "MIDI CON REVERSE!" <<endl;
			}
			else midiConReverse = false;
            break;

			
		case 'r':			
			man->reset();
            break;
		case 'R':			
			man->reset();
            break;

        case 'u':
			if(!midiContAll){
				midiContAll = true;
				cout << "ALL MIDIS CONTROL" <<endl;
			}
            break;
        case 'U':
			if(!midiContAll){
				midiContAll = true;
				cout << "ALL MIDIS CONTROL" <<endl;
			}
            break;

        case 'y':
			if(midiContAll){
				midiContAll = false;
				cout << "SEPERATE MIDI CONTROL" <<endl;
			}
            break;

        case 'Y':
			if(midiContAll){
				midiContAll = false;
				cout << "SEPERATE MIDI CONTROL" <<endl;
			}
            break;
			
        case 'q':
			
			man->addBall();
			
            break;

        case 'Q':
			
			man->addBall();
			
            break;
			

			
//-----------SET FOR REALTIME---------------			
		case 'f':
			
			if(realTime == true){
				ofSetFullscreen(false);				
				realTime = false;
				ofSetWindowShape(640, 620);				
				ofSetWindowPosition(0, 0);				
				
			}else if(realTime == false) {
				ofSetFullscreen(true);				
				realTime = true;
				//				ofSetWindowShape(1024, 768);
				ofSetWindowPosition(ofGetScreenWidth(), 0);				
			}
			
			break;
			
		case 'F':
			
			if(realTime == true){
				ofSetFullscreen(false);				
				realTime = false;
				ofSetWindowShape(640, 620);				
				ofSetWindowPosition(0, 0);				
				
			}else if(realTime == false) {
				ofSetFullscreen(true);				
				realTime = true;
				//				ofSetWindowShape(1024, 768);
				ofSetWindowPosition(ofGetScreenWidth(), 0);				
			}
			
			break;
			
			
        default:
			break;
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
	
	cout << "mouseX: " << x << " mouseY: " << y << endl;
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
