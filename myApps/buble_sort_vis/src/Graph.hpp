//
//  Graph.hpp
//  buble_sort_vis
//
//  Created by Gang il Lee on 11/11/24.
//

#pragma once
#include "ofMain.h"
#include <iostream>
#include <vector>

class Graph {
    
private:
    std::vector<int> vec;
    int width; // 전체 넓이
    int step; // bar 하나의 width
    int len;
    
public:
    Graph(std::vector<int>& v, int w)
    {
        vec = v;
        width = w;
        len = vec.size();
        step = width / len;
        cout << "step: " << step << endl;
    }
    
    void update(std::vector<int>& v)
    {
        vec = v;
    }
    
    void draw(int idx = 0)
    {
        for (int i = 0; i < len; i++) {
            int height = vec[i];
//            cout << height << endl;
            
            if (i == idx) { ofSetColor(255, 0, 0); }
            else if (i == (idx + 1)) { ofSetColor(0, 0, 255); }
            else { ofSetColor(255); }
            
            ofDrawRectangle(
                i * step,
                ofGetHeight() - height,
                step,
                height
            );
            
//            ofDrawEllipse(i*step + (step/2), ofGetHeight() - height, step, step);
            
            
        }
    }

};

