//
//  ball.cpp
//  whataball
//
//  Created by gangil Yi on 11/23/16.
//
//

// ----Headers----
#include "Ball.hpp"


// ----Birth & Death----
Ball::Ball(b2World* w, float x, float y,  bool isSuper)
{
   
    float textColor = 0xffffff;
    
    mWorld = w;
    radius = RAD;
//    radius[1] = (RAD - 60);
//    radius[2] = (RAD - 100);
//    radius[3] = (RAD - 130);
//    radius[4] = (RAD - 150);
    
    posX = x;
    posY = y;
   
    float curRad = radius/2;
    posX = x;
    posY = y - curRad;
    float oldPosX = posX;
    float oldPosY = posY;
   
//    rectArr[i] = ofRectangle(posX, (posY - radius), rectSide, rectSide);
    
//    posArr.push_back( ofPoint(posX, posY) );
//    stringArr.push_back("000");
    
    /* make box2d body */
    mBody = (b2Body*)new ofxBox2dCircle;
    // Density/Bounce/Friction,
//    mBody->setPhysics(0.0, 0.53, 0.1); // Density 0 means, static body
//    mBody->setPhysics(1.0, 0.83, 0.1); // Density 0 means, static body
//    mBody->setPhysics(1.0, PHYSICS_BOUNCE, PHYSICS_FRICTION); // Density 0 means, static body
//    mBody->setup(mWorld->getWorld(), cx, cy, curRad);
}

Ball::~Ball()
{
//    mBody->destroy();
//    cout << "destroy mbody" << endl;
//    delete this
    
}

// getter & setter
float
Ball::getX()
{
    return posX;
}

float
Ball::getY()
{
    return posY;
}


b2World*
Ball::getWorld()
{
//    return mWorld;
}

b2Body*
Ball::getBody()
{
//    return mBody;
    
}

void
Ball::setPos(ofPoint pos)
{
    posX = pos.x;
    posY = pos.y;
}


void
Ball::setRadius(float r)
{
}

void
Ball::addText(string text){
   
    /*
     <Get next position on circle>
     int newX = (int)(center.X + radius * Math.Cos(angle));
     int newY = (int)(center.Y + radius * Math.Sin(angle));
    */
    
//    cout << "addText()" << endl;
    
    if ((DEG_MUL*curIdx) >= 360) {
        curIdx = 0;
        
        if (radIdx < (RAD_NUM - 1)) {
//            oldPosY = oldPosY + (2*(radius[radIdx] - radius[radIdx+1]));
//            oldPosY = oldPosY + 20;
        }
        
        radIdx++;
        
        if (radIdx > RAD_NUM){
            radIdx = 0;
            curIdx = 0;
            cycleFin = true;
        }
        
//        cout << "radIdx: " << radIdx << endl;
        curRad = radius[radIdx]/2;

    }
    
    float the = ofDegToRad(DEG_MUL*curIdx);

    posX = cx + curRad*cos(the);
    posY = cy + curRad*sin(the);
    
//    cout << "new X/Y: " << posX << " / " << posY << endl;
    
    if (!cycleFin) {
        posArr.push_back(ofPoint(posX, posY));
        stringArr.push_back(text);
        stringArrOrigin.push_back(text);
    } else {
        int idx = (radIdx * 36) + curIdx;
        stringArr[idx] = text;
        stringArrOrigin[idx] = text;
    }
    

//    for (int i = 0; i < stringArr.size(); i++){
//        cout << stringArr.at(i) << endl;
//    }
    
    curIdx++;
    
    oldPosX = posX;
    oldPosY = posY;
    
}


void
Ball::addRect(){
  
}

void
Ball::renderAtBodyPosition()
{
//    b2Vec2 pos = mBody->GetPosition();
//    
//    ofPushStyle();
//    ofSetColor(250, 250, 0); // Set ball color
//    ofFill();
//    ofPushMatrix();
//    ofTranslate(_toPixelX(pos.x), _toPixelY(pos.y));
////    ofEllipse(0, 0, radius, radius);
//    ofPopMatrix();
//    ofPopStyle();
}


// Update & draw
void
Ball::update()
{
 
}


void
Ball::draw()
{
    
    ofSetHexColor(textColor);
    
    mBody->draw();

    ofPushMatrix();
    ofPoint box2dPos = mBody->getPosition();
//        ofPoint box2dPos = mBody->getB2DPosition();
    float box2dAngle = mBody->getRotation();
//        cout << "box2dpos X/Y: " << box2dPos.x << " / " << box2dPos.y << endl;
    
    ofTranslate(box2dPos.x, box2dPos.y);
    ofRotate(box2dAngle);

    for (int i = 0; i < stringArr.size(); i++){
        
    //text color
        
        ofDrawBitmapString(stringArr[i], posArr[i].x - cx, posArr[i].y - cy);
//            ofDrawCircle(posArr[i].x - cx, posArr[i].y - cy, 2);
    }

    ofPopMatrix();
 

   
    
    
}

void
Ball::switchText(string text)
{
    for (int i = 0; i < stringArr.size(); i++){
        stringArr[i] = text;
    }
    
}


void
Ball::revertText()
{
    stringArrCopy = stringArrOrigin;
    stringArr.swap(stringArrCopy);
}


void
Ball::applyPhysics(bool b)
{
    if (b) {
        mBody->setPhysics(1.0, PHYSICS_BOUNCE, PHYSICS_FRICTION);
//        cout << mBody->getPhysics() << endl;
    } else {
        mBody->setPhysics(0.0, PHYSICS_BOUNCE, PHYSICS_FRICTION);
    }
    
}

void
Ball::eraseText(float interval)
{
    float curTime = ofGetElapsedTimeMillis();
    while(stringArr.size()) {
        if ((ofGetElapsedTimeMillis() - curTime) > interval) {
            stringArr.pop_back();
            stringArrOrigin.pop_back();
//            stringArrCopy.pop_back();
//            posArr.pop_back();
            curTime = ofGetElapsedTimeMillis();
        }
    }
    
}


void
Ball::setGray(bool g){
    colorGray = g;
}


void
Ball::setColor(float c) {
    textColor = c;
}
