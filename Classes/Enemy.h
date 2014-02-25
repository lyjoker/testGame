//
//  Enemy.h
//  TestGame
//
//  Created by Yuan Lin on 2/19/14.
//
//

#ifndef __TestGame__Enemy__
#define __TestGame__Enemy__

#include "cocos2d.h"
#include "Creature.h"


class Enemy : public Creature
{
public:
    bool init();
    CREATE_FUNC(Enemy);
    //Enemy* create(const char* pName, int pHP, int pSpeed, int pAttack);
    void initWithProperty(const char* pName, int pHP, int pSpeed, int pAttack, int pLine, float pX, float attSpeed);
    void enemyUpdate(float dt);
    cocos2d::Rect getEffectRect();
    cocos2d::Point getMidPoint();
    void removeSelf();
    void setDamage(int damage);
    cocos2d::Animate* animateDead();

};

#endif /* defined(__TestGame__Enemy__) */
