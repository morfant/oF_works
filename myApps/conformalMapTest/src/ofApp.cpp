#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowShape(800, 800);
    ofBackground(0);

    // 초기 변환 중심 설정
    aReal = 0.0; // 실수 성분
    aImag = 0.0; // 허수 성분

    // 격자 생성
    gridSize = 80; // 격자 간격
    gridWidth = ofGetWidth() / gridSize;
    gridHeight = ofGetHeight() / gridSize;
}

//--------------------------------------------------------------
void ofApp::update() {
    // 실수 및 허수 성분 변경 (애니메이션 효과)
//    float time = ofGetElapsedTimef();
//    aReal = 0.5 * sin(time * 0.5);
//    aImag = 0.5 * cos(time * 0.5);
    
    aReal = ofMap(ofGetMouseX(), 0, ofGetWidth(), -0.2, 0.2);
    aImag = ofMap(ofGetMouseY(), 0, ofGetHeight(), -0.2, 0.2);
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); // 화면 중심 이동
    ofSetColor(255);

    // 격자 점 및 선 그리기
    for (int x = -gridWidth / 2; x < gridWidth / 2; x++) {
        for (int y = -gridHeight / 2; y < gridHeight / 2; y++) {
            // 현재 점
            glm::vec2 z = glm::vec2(x * gridSize, y * gridSize) / float(gridSize);
            glm::vec2 transformed = mobiusTransform(z);

            // 오른쪽 이웃 점
            glm::vec2 zRight = glm::vec2((x + 1) * gridSize, y * gridSize) / float(gridSize);
            glm::vec2 transformedRight = mobiusTransform(zRight);

            // 아래쪽 이웃 점
            glm::vec2 zDown = glm::vec2(x * gridSize, (y + 1) * gridSize) / float(gridSize);
            glm::vec2 transformedDown = mobiusTransform(zDown);

            // 현재 점 그리기
            ofDrawCircle(transformed.x * gridSize, transformed.y * gridSize, 2);

            // 오른쪽 이웃과 연결
            ofDrawLine(transformed.x * gridSize, transformed.y * gridSize,
                       transformedRight.x * gridSize, transformedRight.y * gridSize);

            // 아래쪽 이웃과 연결
            ofDrawLine(transformed.x * gridSize, transformed.y * gridSize,
                       transformedDown.x * gridSize, transformedDown.y * gridSize);
        }
    }

    // 변환 중심 시각화
    ofSetColor(255, 0, 0);
    ofDrawCircle(aReal * gridSize, aImag * gridSize, 5);

    // 정보 출력
    ofSetColor(255);
    ofDrawBitmapString("aReal: " + ofToString(aReal, 2) + ", aImag: " + ofToString(aImag, 2), 10, 20);
}

//--------------------------------------------------------------
// Möbius 변환 구현
glm::vec2 ofApp::mobiusTransform(const glm::vec2& z) {
    glm::vec2 a = glm::vec2(aReal, aImag); // 변환 중심
    float denom = 1 - (z.x * a.x + z.y * a.y); // (1 - z * conj(a))
    glm::vec2 numerator = z - a;              // (z - a)

    return numerator / denom; // (z - a) / (1 - z*conj(a))
}
