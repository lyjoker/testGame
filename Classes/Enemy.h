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
#include "Common.h"
#include "Entity.h"


class Enemy : public Entity
{
public:
    bool init();
    CREATE_FUNC(Enemy);
    //Enemy* create(const char* pName, int pHP, int pSpeed, int pAttack);
    void initWithProperty(const char* pName, int pHP, int pSpeed, int pAttack, GameMap* point);
    void enemyUpdate(float dt);
};

#endif /* defined(__TestGame__Enemy__) */
