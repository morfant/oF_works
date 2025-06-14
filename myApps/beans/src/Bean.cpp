//
//  Bean.cpp
//  beans
//
//  Created by Gang il Lee on 11/27/24.
//

#include "Bean.hpp"


Bean::Bean(ofVec2f cen, float len, float st, int VorH, int where)
{
    center = cen;
    position = center;
    
    width = len;
    direction = 1;
    step = st;
    
    vh = VorH;
    fbo = where;
}

void Bean::update()
{
    timef += (step * direction);
    if (abs(timef) >= 2) direction *= -1;
//    cout << timef << endl;
    
    if (vh == 1) position.x = center.x + tanh(timef) * width;
    if (vh == 0) position.y = center.y + tanh(timef) * width;
}

void Bean::draw()
{
   
    if (fbo == 1)
    {
        fbo1.begin();
    }
    else if (fbo == 2)
    {
        fbo2.begin();
    }
    
    
    ofPushMatrix();
    ofTranslate(position);
    //    ofTranslate(static_cast<glm::vec2>(position))

    ofSetColor(56, 73, 83);
    ofDrawEllipse(0, 0, radius, radius);
    
    ofPopMatrix();
    
    
    
    if (fbo == 1)
    {
        fbo1.end();
    }
    else if (fbo == 2)
    {
        fbo2.end();
    }

    
}

void Bean::setStep(float f)
{
    step = f;
}
