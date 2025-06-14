#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    WIDTH = ofGetWidth();
    HEIGHT = ofGetHeight();
    
    // Random
    // [0, 1) 범위의 실수를 생성하는 분포 설정
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    generator.seed(seed);
    
    // GUI
    gui.setup();  // 패널 초기화
    gui.add(randomSeed.setup("Random Seed", 0, 0, 100));  // 랜덤 시드를 위한 슬라이더 (0 ~ 1000)
    
    // 패널 크기 조절
    gui.setSize(WIDTH - 50, 100);  // 패널의 폭을 300으로 설정
    

    // 초기에 시드 설정
    setRandomSeed();
    
}

//--------------------------------------------------------------
void ofApp::update(){

    // 랜덤 시드가 변경된 경우에만 setRandomSeed() 호출
    if (randomSeed != previousSeed) {
        setRandomSeed();
        previousSeed = randomSeed;  // 이전 시드 값을 현재 시드 값으로 업데이트
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(saveToPdf)
    {
        // 숫자를 4자리 형식으로 변환
        int seedValue = randomSeed;  // ofxIntSlider의 값을 가져옴
        std::ostringstream oss;
        oss << std::setw(4) << std::setfill('0') << seedValue;
        std::string formattedSeed = oss.str();
        
        std::string fileName = "cover-"+formattedSeed+"-"+ofGetTimestampString()+".pdf";
        cout << "Save as pdf begin...(" << fileName << ")" << endl;
        ofBeginSaveScreenAsPDF(fileName, false);
    }

    // Drawing
    ofSetBackgroundColor(255);
    for (Dot* d : arr)
    {
        d->draw();
    }
    
    if(saveToPdf)
    {
        cout << "Save as pdf Done" << endl;
        ofEndSaveScreenAsPDF();
        saveToPdf = false;
    }
    
    // GUI 표시
    gui.draw();
}


void ofApp::clearArr() {
    // 벡터의 각 포인터가 가리키는 객체를 삭제
    for (Dot* d : arr) {
        delete d;  // 객체 삭제
    }

    arr.clear();  // 벡터의 모든 요소를 제거 (선택 사항)
}

void ofApp::fillArr() {
    for (int i = 0; i < NUM; i++)
    {
        float randomValue = distribution(generator);
        float x = randomValue * ofGetWidth();
        float y = distribution(generator) * ofGetHeight();
        
        ofVec2f pos = ofVec2f(x, y);
        
        Dot* d = new Dot(generator, distribution, pos, 10.f);
        arr.push_back(d);
    }
 
}

// 랜덤 시드를 설정하는 함수
void ofApp::setRandomSeed() {
    clearArr();
    
    cout << "RandomSeed: " << randomSeed << endl;
    generator.seed(randomSeed);
    
    fillArr();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // 방향키로 슬라이더 값 조정
    if (key == OF_KEY_LEFT) {
        randomSeed = std::max(randomSeed - 1, randomSeed.getMin());  // 왼쪽 방향키: 값 감소
    } else if (key == OF_KEY_RIGHT) {
        randomSeed = std::min(randomSeed + 1, randomSeed.getMax());  // 오른쪽 방향키: 값 증가
    } else if (key == OF_KEY_RETURN) {
        saveToPdf = true;
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
