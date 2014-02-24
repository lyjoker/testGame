//
//  Bullet.cpp
//  TestGame
//
//  Created by Yuan Lin on 2/24/14.
//
//

#include "Bullet.h"

USING_NS_CC;

bool Bullet::init()
{
    hasRemoved = false;
    return true;
}

void Bullet::removeSelf()
{
    if(hasRemoved)
		return;
    
	hasRemoved = true;
	unscheduleAllSelectors();
	this->stopAllActions();
	this->removeFromParentAndCleanup(true);
}

bool MagicBullet::init()
{
    speed = 500;
    return true;
}
