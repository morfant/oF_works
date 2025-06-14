#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    // 윈도우 크기 설정
    ofSetWindowShape(800, 600);
    ofSetFrameRate(5);

    n = ARRAY_SIZE;
    resetArray();
    
    graph = new Graph(values, ofGetWidth());
    
    font.load("verdana.ttf", 24); // 폰트를 불러오고 크기를 24로 설정
    
    // 스택 초기화
    setupQuickSort(values);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    // quickSort 함수 검증
//    vector<int> v = quickSort(values);
//    quickSort(values, 0, values.size() - 1);
//
//    for (auto& i : values)
//    {
//        cout << i << ", ";
//    }
//
//    cout << endl;
    
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    graph->update(currentVec);
    graph->draw(pivotIndex, leftIndex, rightIndex);
     
    bool isSorted = quickSortStep();
    if (isSorted) {
        // 정렬 완료 처리
        ofLog() << "Sorting complete!";
    }
    
    
    font.drawString(
                    ofToString(ofGetFrameRate(), 2),
                    ofGetWidth() / 2 - 50, ofGetHeight() / 2
    ); // 원하는 위치에 텍스트 출력
    
}


//--------------------------------------------------------------
void ofApp::resetArray(){
    values.clear();
    for (int i = 0; i < n; i++) {
        values.push_back(ofRandom(10, ofGetHeight()));  // 랜덤한 값으로 배열 초기화
    }
}

//--------------------------------------------------------------

bool ofApp::quickSortStep() {
    if (quickSortStack.empty()) return true; // 정렬이 완료되면 true 반환
    
    auto [left, right] = quickSortStack.top();
    quickSortStack.pop();

    if (left >= right) return false; // 현재 부분 배열이 유효하지 않으면 다음 단계로

    int pivot = right;
    int pivotValue = currentVec[pivot];
    int stored_idx = left;
    
    // partition 단계 수행
    for (int i = left; i < right; i++) {
        if (currentVec[i] < pivotValue) {
            std::swap(currentVec[i], currentVec[stored_idx]);
            stored_idx++;
        }
    }
    std::swap(currentVec[stored_idx], currentVec[right]);
    
    // 새 부분 배열을 스택에 추가
    quickSortStack.push({left, stored_idx - 1});
    quickSortStack.push({stored_idx + 1, right});
    
    // 전역으로 값 전달
    pivotIndex = stored_idx;
    leftIndex = left;
    rightIndex = right;

    // 정렬 중간 결과를 그리기
//    graph->update(currentVec);
//    graph->draw(stored_idx);

    return false; // 아직 완료되지 않음
}

//--------------------------------------------------------------
void ofApp::setupQuickSort(vector<int>& vec) {
    currentVec = vec; // 초기 배열 설정
    while (!quickSortStack.empty()) quickSortStack.pop(); // 스택 초기화
    quickSortStack.push({0, vec.size() - 1});
}

// Algorithm itself
//--------------------------------------------------------------
vector<int> ofApp::quickSort(vector<int>& vec){
    
    if (vec.size() <= 1) return vec;
    
    int pivot = vec.size() - 1;
    int pivotValue = vec[pivot];
    
    vector<int> less, greater, pivots;
    
    
    for (auto & x : vec)
    {
        if (x < pivotValue) {
            less.push_back(x);
        } else if (x > pivotValue) {
            greater.push_back(x);
        } else {
            pivots.push_back(x);
        }
    }
    
    vector<int> result;
    vector<int> sortedLess = quickSort(less);
    vector<int> sortedGreater = quickSort(greater);
    
    result.insert(result.end(), sortedLess.begin(), sortedLess.end());
    result.insert(result.end(), pivots.begin(), pivots.end());
    result.insert(result.end(), sortedGreater.begin(), sortedGreater.end());
    
    return result;
}

//--------------------------------------------------------------
int ofApp::makePart(vector<int>& vec, int left, int right, int pvIdx){
    
    int pivot = pvIdx;
    int pivotValue = vec[pivot];
    
    swap(vec[pivot], vec[right]);
    
    int currentIdx = left;
    
    for (int i = left; i < right; i++)
    {
        if (vec[i] <= pivotValue)
        {
            swap(vec[currentIdx], vec[i]);
            currentIdx++;
        }
    }
    
    swap(vec[currentIdx], vec[right]);
    
    return currentIdx;
}

//--------------------------------------------------------------
void ofApp::quickSort(vector<int>& vec, int left, int right){
    
    if (right > left)
    {
        int pivot = right;
        int newPIdx = makePart(vec, left, right, pivot);
        quickSort(vec, left, newPIdx - 1);
        quickSort(vec, newPIdx + 1, right);
    }
}




//--------------------------------------------------------------
void ofApp::exit(){

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
