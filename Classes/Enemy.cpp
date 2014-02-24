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
    m_Sprite->setPosition(point->getPosition());
    m_status = STATUS_RUNNING;
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

