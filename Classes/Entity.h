//
//  Entity.h
//  TestGame
//
//  Created by Yuan Lin on 2/19/14.
//
//

#ifndef __TestGame__Entity__
#define __TestGame__Entity__

#include "cocos2d.h"

class Entity : public cocos2d::Node
{
public:
    void bindSprite(cocos2d::Sprite* sprite);
protected:
    cocos2d::Sprite* m_Sprite;
};
#endif /* defined(__TestGame__Entity__) */
