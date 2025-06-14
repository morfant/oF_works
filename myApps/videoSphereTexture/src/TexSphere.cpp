//
//  TexSphere.cpp
//  videoSphere
//
//  Created by Gang il Lee on 2/11/25.
//

#include "TexSphere.hpp"

TexSphere::TexSphere(
    const glm::vec3& _pos, float r, float ang, const ofVec2f& wh
    )
{
    
    pos = _pos;
    radius = r;
    rotAngle = ang;
    
    sp.setRadius(radius);
    sp.mapTexCoords(0, 0, wh.x, wh.y); // 전체를 텍스쳐로 사용
//        sphere.mapTexCoords(startX, startY, startX + texWidth, startY + texHeight); // 일정 부분만 텍스쳐로 사용
    

}


void TexSphere::update()
{
    if (ofGetFrameNum() % selInterval == 0)
    {
        selAxis = rand() % 3;
        selInterval = ofRandom(100, 400);
    }
    if (selAxis == 0) sp.rotateDeg(rotAngle, 1, 0, 0);
    else if (selAxis == 1) sp.rotateDeg(rotAngle, 0, 1, 0);
    else if (selAxis == 2) sp.rotateDeg(rotAngle, 0, 0, 1);
    
}

void TexSphere::getTexture(const ofTexture& t)
{
    texture = t;
}

void TexSphere::draw()
{
    
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(pos);
    texture.bind();
    sp.draw();
    texture.unbind();
    ofPopMatrix();
}
