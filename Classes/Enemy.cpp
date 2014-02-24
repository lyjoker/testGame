//
//  Enemy.cpp
//  TestGame
//
//  Created by Yuan Lin on 2/19/14.
//
//

#include "Enemy.h"


USING_NS_CC;

bool Enemy::init()
{
    m_status = STATUS_RUNNING;

    return true;
}
void Enemy::initWithProperty(const char* pName, int pHP, int pSpeed, int pAttack, GameMap* point)
{
    name = pName;
    m_curHP = m_maxHP = pHP;
    m_speed = pSpeed;
    m_attack = pAttack;
    m_position = point;
    auto frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile(StringUtils::format("%s.plist", name.c_str()), StringUtils::format("%s.png", name.c_str()));
    Sprite* testSprite = Sprite::createWithSpriteFrame(frameCache->getSpriteFrameByName(StringUtils::format("%s_run1.png", name.c_str())));
    this->bindSprite(testSprite);
    m_Sprite->setPosition(point->getPosition().x, point->getPosition().y+90);
    m_status = STATUS_RUNNING;
    schedule(schedule_selector(Enemy::enemyUpdate), 0.1f);
    Point tmp = m_position->getPosition();
    tmp.y += 90;
    tmp.x = 0;
    m_Sprite->setFlippedX(true);
    auto moveto = MoveTo::create(2200.0f/m_speed, tmp);
    
    this->run();
    m_Sprite->runAction(moveto);
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
void Enemy::enemyUpdate(float dt)
{
    CCLOG("Now Position: %.0f , %.0f", m_Sprite->getPosition().x, m_Sprite->getPosition().y);
    
}

