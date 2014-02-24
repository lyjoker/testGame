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
#include "GameScene.h"
#include "GameMap.h"
#include "Bullet.h"


class Tower : public cocos2d::Node
{
protected:
    cocos2d::Sprite *t_sprite;
    std::string name;
    int t_curHP, t_maxHP, t_attack, t_attSpeed, t_attRange, t_status;
    //cocos2d::Point t_position;
    GameMap *t_position;
    void towerUpdate(float dt);
public:
    static Tower* create(int curHP, int maxHP, int attack, int attSpeed, int attRange, GameMap* position, std::string name)
    {
        Tower *pRet = new Tower();
        if (pRet && pRet->init(curHP, maxHP, attack, attSpeed, attRange, position, name))
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
    bool init(int, int,int, int,int, GameMap*, std::string);
    void attack();
    void attackEnemy(Enemy* enemy);
};

#endif /* defined(__TestGame__Tower__) */
