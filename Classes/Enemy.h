//
//  Enemy.h
//  TestGame
//
//  Created by Yuan Lin on 2/19/14.
//
//

#ifndef __TestGame__Enemy__
#define __TestGame__Enemy__

#include "Common.h"
#include "Entity.h"
#include "cocos2d.h"
#include "AnimationUtil.h"

class Enemy : public Entity
{
public:
    CREATE_FUNC(Enemy);
    virtual bool init();
    void run();
};

#endif /* defined(__TestGame__Enemy__) */
