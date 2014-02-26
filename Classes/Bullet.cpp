//
//  Bullet.cpp
//  TestGame
//
//  Created by Yuan Lin on 2/24/14.
//
//

#include "Bullet.h"
#include "Common.h"
#include "Enemy.h"
#include "Tower.h"

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
	this->unscheduleAllSelectors();
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
void MagicBullet::setProperty(Enemy* enemy, int _damage, Point _point, const char* _name, bool _isExplosion)
{
    target = enemy;
    damage = _damage;
    point = _point;
    name = _name;
    isExplosion = _isExplosion;
}
void MagicBullet::fire()
{
    auto frameCache = SpriteFrameCache::getInstance();
    SpriteFrame* tmp = frameCache->getSpriteFrameByName(StringUtils::format("%s.png", name.c_str()));
    sprite = Sprite::createWithSpriteFrame(tmp);
    sprite->setScale(0.6f);
    sprite->setPosition(point.x, point.y);
    float dx = target->getMidPoint().x - point.x;
    float dy = target->getMidPoint().y - point.y;
    float tanangle = dy / dx;
    angle = atanf(tanangle);
    angle = to360Angle(CC_RADIANS_TO_DEGREES(angle));
    if (dx<0 && dy>0)
        angle -= 180;
    else if (dx<0 && dy<0)
        angle += 180;
    sprite->setRotation(360-angle);
    if (target!=NULL) active = true;
    this->addChild(sprite);
}
void MagicBullet::explosion()
{
    auto frameCache = SpriteFrameCache::getInstance();
    SpriteFrame* tmp = frameCache->getSpriteFrameByName(StringUtils::format("%s_Exp.png", name.c_str()));
    sprite->removeFromParentAndCleanup(true);
    sprite = Sprite::createWithSpriteFrame(tmp);
    sprite->setPosition(point + Point(
                                      sprite->getContentSize().width * cosf(CC_DEGREES_TO_RADIANS(angle)) / 2,
                                      sprite->getContentSize().height * sinf(CC_DEGREES_TO_RADIANS(angle)) / 2));
    this->addChild(sprite);
    sprite->runAction(Sequence::create(FadeOut::create(0.3f),
                                       CallFunc::create(CC_CALLBACK_0(Bullet::removeSelf, this)),
                                       NULL));
    CCLOG("point: %f, %f", point.x, point.y);
    active = false;
    
}
void MagicBullet::update(float dt)
{
    if (active)
    {
        if (target==NULL || target->hasRemoved)
        {
            removeSelf();
            return;
        }
        if (sprite->getBoundingBox().intersectsRect(target->getEffectRect()))
        {
            target->setDamage(damage);
            if (isExplosion)
                explosion();
            else
                removeSelf();
            return;
        }
        float dx = target->getMidPoint().x - point.x;
        float dy = target->getMidPoint().y - point.y;
        float tanangle = dy / dx;
        angle = atanf(tanangle);
        angle = to360Angle(CC_RADIANS_TO_DEGREES(angle));
        if (dx<0 && dy>0)
            angle -= 180;
        else if (dx<0 && dy<0)
            angle += 180;
        float radian = CC_DEGREES_TO_RADIANS(angle);
        point.x += cosf(radian) * speed * dt;
        point.y += sinf(radian) * speed * dt;
        sprite->setPosition(point);
        sprite->setRotation(360 - angle);
    }
}
