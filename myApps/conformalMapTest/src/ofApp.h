#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;


    
    glm::vec2 mobiusTransform(const glm::vec2& z);

    
    float aReal, aImag;
    int gridSize, gridWidth, gridHeight;
		
};
