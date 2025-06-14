#pragma once

#include "Graph.hpp"
#include "ofMain.h"

// 배열의 크기 설정
#define ARRAY_SIZE 80

class ofApp : public ofBaseApp{
    
public:
    void setup() override;
    void update() override;
    void draw() override;
    void exit() override;
    
    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y ) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
    
    
    void resetArray();      // 배열 초기화

    // algorithm
    vector<int> quickSort(vector<int>& vec);
    int makePart(vector<int>& vec, int left, int right, int pvIdx);
    void quickSort(vector<int>& vec, int left, int right);
    
    
    // for visualize
    bool quickSortStep();
    void setupQuickSort(vector<int>& vec);

    int n;
    int pivotIndex, leftIndex, rightIndex;
    
    stack<pair<int, int>> quickSortStack;
    vector<int> currentVec;
    vector<int> values;  // 정렬할 값들

    Graph* graph;
    ofTrueTypeFont font;
        
};
