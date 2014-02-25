//
//  Entity.h
//  TestGame
//
//  Created by Yuan Lin on 2/19/14.
//
//

#ifndef __TestGame__Creature__
#define __TestGame__Creature__

#include "cocos2d.h"



class Creature : public cocos2d::Node
{
public:
    void animateRun();
    void animateAttack();
    int getLine();
    bool hasRemoved;
protected:
    int m_curHP, m_maxHP, m_attack, m_speed, m_status, m_line;
    float m_attSpeed;
    std::string name;
    cocos2d::Point m_position;
    cocos2d::Sprite* m_sprite;
    cocos2d::ProgressTimer* m_healthbar;
};
#endif /* defined(__TestGame__Creature__) */
