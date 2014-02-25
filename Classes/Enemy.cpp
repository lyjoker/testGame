//
//  Enemy.cpp
//  TestGame
//
//  Created by Yuan Lin on 2/19/14.
//
//

#include "Enemy.h"
#include "Common.h"
#include "Creature.h"
#include "GameMap.h"
#include "GameScene.h"

USING_NS_CC;

bool Enemy::init()
{
    m_status = STATUS_RUNNING;
    hasRemoved = false;
    return true;
}
void Enemy::initWithProperty(const char* pName, int pHP, int pSpeed, int pAttack, int pLine, float pX, float attSpeed)
{
    name = pName;
    m_curHP = m_maxHP = pHP;
    m_speed = pSpeed;
    m_attack = pAttack;
    m_position = Point(pX, GameMap::lineToY(pLine));
    m_line = pLine;
    m_attSpeed = attSpeed;
    auto frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile(
                                        StringUtils::format("%s.plist", name.c_str()),
                                        StringUtils::format("%s.png", name.c_str())
                                        );
    m_sprite = Sprite::createWithSpriteFrame(
                                             frameCache->getSpriteFrameByName(
                                                                             StringUtils::format("%s_run1.png", name.c_str())
                                                                             )
                                            );
    m_sprite->setAnchorPoint(Point(0, 0));
    m_sprite->setFlippedX(true);
    this->setPosition(m_position);
    this->addChild(m_sprite);
    m_status = STATUS_RUNNING;
    
    m_healthbar = ProgressTimer::create(Sprite::create("health_bar_green.png"));
    m_healthbar->setType(ProgressTimer::Type::BAR);
    m_healthbar->setMidpoint(Point(0, 0));
    m_healthbar->setBarChangeRate(Point(1, 0));
    m_healthbar->setPercentage(100);
    m_healthbar->setScale(m_sprite->getContentSize().width / m_healthbar->getContentSize().width);
    m_healthbar->setAnchorPoint(Point(0,0));
    m_healthbar->setPosition(Point(0, m_sprite->getContentSize().height));
    this->addChild(m_healthbar, 2);
    auto redbar = Sprite::create("health_bar_red.png");
    redbar->setPosition(m_healthbar->getPosition());
    redbar->setScale(m_sprite->getContentSize().width / redbar->getContentSize().width);
    redbar->setAnchorPoint(Point(0,0));
    this->addChild(redbar, 1);
    
    schedule(schedule_selector(Enemy::enemyUpdate), 0.1f);
    Point tmp = m_position;
    tmp.x = 0;
    
    auto moveto = MoveTo::create(2200.0f/m_speed, tmp);
    
    this->animateRun();
    this->runAction(moveto);
    /*
    auto enemyListener = EventListenerTouchOneByOne::create();
    enemyListener->onTouchBegan = [=](Touch* touch, Event* event)->bool{
        
        Point tmp = this->convertToNodeSpace(touch->getLocation());


        if (m_Sprite->boundingBox().containsPoint(tmp))
        {
            if (this->m_status == STATUS_RUNNING)
            {
                this->attack();
            }else if (this->m_status == STATUS_ATTACKING)
            {
                this->run();
            }
        }
        return true;
    };
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(enemyListener, m_Sprite);
    */
}

Rect Enemy::getEffectRect()
{
    float _width = m_sprite->getContentSize().width;
    float _height = m_sprite->getContentSize().height;
    auto rect = Rect(
                     this->getPositionX() + _width * 0.15,
                     this->getPositionY() + _height * 0.15,
                     _width * 0.7,
                     _height * 0.7
                     );
    return rect;
}
Point Enemy::getMidPoint()
{
    return (Point(
                  this->getPositionX() + m_sprite->getContentSize().width / 2,
                  this->getPositionY() + m_sprite->getContentSize().height / 2
                  )
            );
}
void Enemy::setDamage(int damage)
{
    m_curHP -= damage;
    m_healthbar->setPercentage(float(m_curHP) / float(m_maxHP) * 100);
    if (m_curHP <= 0)
    {
        this->stopAllActions();
        m_sprite->stopAllActions();
        auto dead1 = Blink::create(0.3f, 3);
        this->runAction(Sequence::create(
                                         dead1,
                                         CallFunc::create(
                                                           [&](){removeSelf();}
                                                          ),
                                         NULL));
    }
}
void Enemy::removeSelf()
{
    if(hasRemoved)
		return;
    
	hasRemoved = true;
	unscheduleAllSelectors();
	this->stopAllActions();
    m_sprite->stopAllActions();
	this->removeFromParentAndCleanup(true);
    GameScene::enemyList->eraseObject(this);
}
void Enemy::enemyUpdate(float dt)
{
    if (m_status == STATUS_COOLDOWN)
        return;
    if (m_status == STATUS_RUNNING)
    {
    
    }
    
}

