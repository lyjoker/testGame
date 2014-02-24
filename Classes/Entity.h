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
#include "Common.h"
#include "AnimationUtil.h"
#include "GameMap.h"

class Entity : public cocos2d::Node
{
public:
    void bindSprite(cocos2d::Sprite* sprite);
    void run();
    void attack();
    GameMap *getGamePos();
protected:
    cocos2d::Sprite* m_Sprite;
    int m_curHP, m_maxHP, m_attack, m_speed, m_status;
    std::string name;
    GameMap *m_position;
};
#endif /* defined(__TestGame__Entity__) */
