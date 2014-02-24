//
//  Bullet.h
//  TestGame
//
//  Created by Yuan Lin on 2/24/14.
//
//

#ifndef __TestGame__Bullet__
#define __TestGame__Bullet__

#include "cocos2d.h"
#include "Common.h"
#include "Enemy.h"
#include "Tower.h"

class Bullet : public cocos2d::Node
{
public:
    CREATE_FUNC(Bullet);
    bool init();
    void removeSelf();
protected:
    bool hasRemoved;
    int damage, speed;

};

class MagicBullet : public Bullet
{
public:
    CREATE_FUNC(MagicBullet);
    bool init();
    void setProperty(Enemy* enemy, int _damage);
private:
    void update(float dt);
};

#endif /* defined(__TestGame__Bullet__) */
