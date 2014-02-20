//
//  Enemy.cpp
//  TestGame
//
//  Created by Yuan Lin on 2/19/14.
//
//

#include "Enemy.h"


USING_NS_CC;

bool Enemy::init()
{
    return true;
}
void Enemy::initWithProperty(const char* pName, int pHP, int pSpeed, int pAttack)
{
    name = strcpy(name, pName);
    m_curHP = m_maxHP = pHP;
    m_speed = pSpeed;
    m_attack = pAttack;
}
void Enemy::run()
{
    auto frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("hero_magi.plist", "hero_magi.png");
    
    Animate* animate = Animate::create(AnimationUtil::createAnimWithFrame("run", 0.5f, -1));
    m_Sprite->runAction(animate);
}