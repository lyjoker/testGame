//
//  AnimationUtil.h
//  TestGame
//
//  Created by Yuan Lin on 2/19/14.
//
//

#ifndef __TestGame__AnimationUtil__
#define __TestGame__AnimationUtil__

#include "cocos2d.h"

class AnimationUtil{
public:
    static cocos2d::Animation* createAnimWithFrame(const char* name, float delay, unsigned int iLoops);
    
};

#endif /* defined(__TestGame__AnimationUtil__) */
