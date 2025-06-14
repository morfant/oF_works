//
//  ball.hpp
//  whataball
//
//  Created by gangil Yi on 11/23/16.
//
//

//#ifndef Ball_hpp
//#define Ball_hpp


#define RAD 200

// ----Preprocessor command----
#pragma once


// ----Headers----
#include <stdio.h>
#include <iostream>
#include "ofMain.h"
#include "ofxBox2D.h"
#include "convertFunc.h"


// ----Class definition----
class Ball{
protected:
    
    // Position
    float   posX;
    float   posY;
    
    // Size
    float   radius;
    
    // Box2D
    b2Body*		mBody;
    b2World*    mWorld;
    
    bool        superBall;
    
    
public:
    // Birth and Death
    Ball(b2World* world, float x, float y, bool isSuper);
    ~Ball();
    
    // Getter
    float   getX();
    float   getY();
    bool    getIsSuper();
    
    // Userdata
    int     ballUserData;
    
    b2World*    getWorld();
    b2Body*     getBody();
    
    // Setter
    void    setX(float posX);
    void    setY(float posY);
    
    // Render
    void    renderAtBodyPosition();
    
    // Update & draw
    void    update();
    void    draw();
    
    
    
    
    
};

