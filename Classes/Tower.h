//
//  Tower.h
//  TestGame
//
//  Created by Yuan Lin on 2/24/14.
//
//

#ifndef __TestGame__Tower__
#define __TestGame__Tower__

#include "cocos2d.h"

class Enemy;

class Tower : public cocos2d::Node
{
protected:
    cocos2d::Sprite *t_sprite;
    std::string name;
    int t_curHP, t_maxHP, t_attack,  t_attRange, t_status, t_line;
    float t_attSpeed;
    cocos2d::Point t_position;
    virtual void towerUpdate(float dt);
    virtual void animateAttack(){};
    virtual void attackEnemy(Enemy* enemy){};
    virtual void stopAttackAnimate(){};
public:
    static Tower* create(int curHP, int maxHP, int attack, float attSpeed, int attRange, float pX, int line, std::string name)
    {
        Tower *pRet = new Tower();
        if (pRet && pRet->init(curHP, maxHP, attack, attSpeed, attRange, pX,line, name))
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
    bool init(int, int,int, float,int, float,int, std::string);

};

class MagicTower : public Tower
{
public:
    static MagicTower* create(int line, float pX);

private:
    void attackEnemy(Enemy* enemy);
    void animateAttack();
    void stopAttackAnimate();
    //void towerUpdate(float dt);
};

#endif /* defined(__TestGame__Tower__) */
