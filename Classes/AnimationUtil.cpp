//
//  AnimationUtil.cpp
//  TestGame
//
//  Created by Yuan Lin on 2/19/14.
//
//

#include "AnimationUtil.h"
USING_NS_CC;

Animation* AnimationUtil::createAnimWithFrame(const char* name, float delay, int iLoops)
{
    auto cache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> framesArray = Vector<SpriteFrame*>();
    SpriteFrame* frame = NULL;
    int index = 1;
    do {
        const char* tmp = String::createWithFormat("%s%d.png", name, index++)->getCString();
        frame = cache->getSpriteFrameByName(tmp);
        if (frame == NULL)
            break;
        framesArray.pushBack(frame);
    } while (true);
    Animation* animation = Animation::createWithSpriteFrames(framesArray);
    animation->setLoops(iLoops);
    animation->setRestoreOriginalFrame(true);
    animation->setDelayPerUnit(delay);
    return animation;
    
}