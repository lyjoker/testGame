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

class Tower;

class Enemy : public Creature
{
public:
    //Enemy* create(const char* pName, int pHP, int pSpeed, int pAttack);
    bool initWithProperty(const char* pName, int pHP, int pSpeed, int pAttack, int pLine, float pX, float attSpeed, int attRange);
    virtual void enemyUpdate(float dt);
    cocos2d::Rect getEffectRect();
    cocos2d::Point getMidPoint();
    void removeSelf();
    void setDamage(int damage);
    cocos2d::Animate* animateDead();
    virtual bool setDefaultProperty();
protected:
    void stopActionAndRun();
    virtual void attackTower(Tower* tower);
    float pxWidthRate, pxHeightRate, widthRate, heightRate;
    float runInternalTime;

};

class EnemyKnight : public Enemy
{
public:
    static EnemyKnight* create(int pLine, float pX);
};

class EnemyBlueDragon : public Enemy
{
public:
    static EnemyBlueDragon* create(int pLine, float pX);
    bool setDefaultProperty();
    void attackTower(Tower* tower);
    void enemyUpdate(float dt);
};
#endif /* defined(__TestGame__Enemy__) */
