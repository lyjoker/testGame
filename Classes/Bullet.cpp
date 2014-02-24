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
    active = false;
    target = NULL;
    scheduleUpdate();
    return true;
}
void MagicBullet::setProperty(Enemy* enemy, int _damage, Point _point)
{
    target = enemy;
    damage = _damage;
    point = _point;
}
void MagicBullet::fire()
{
    sprite = Sprite::create("MagicBullet.png");
    sprite->setPosition(point.x, point.y);
    if (target!=NULL) active = true;
    this->addChild(sprite);
}
void MagicBullet::update(float dt)
{
    if (active)
    {
        if (sprite->getBoundingBox().intersectsRect(target->m_Sprite->getBoundingBox()))
        {
            removeSelf();
        }
        float dx = target->m_Sprite->getPosition().x - point.x;
        float dy = point.y - target->m_Sprite->getPosition().y;
        float tanangle = dy / dx;
        float angle = atanf(tanangle);
        if (angle<0) angle+=3.14159f;
        point.x += cosf(angle) * speed * dt;
        point.y -= sinf(angle) * speed * dt;
        sprite->setPosition(point);
        sprite->setRotation(angle * 180 / 3.14159f);
    }
}