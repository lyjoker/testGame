//
//  Entity.cpp
//  TestGame
//
//  Created by Yuan Lin on 2/19/14.
//
//

#include "Entity.h"

USING_NS_CC;

void Entity::bindSprite(Sprite* sprite)
{
    m_Sprite = sprite;
    this->addChild(m_Sprite);
}
void Entity::run()
{
    
    Animate* animate = Animate::create(AnimationUtil::createAnimWithFrame(StringUtils::format("%s_run", name.c_str()), 20.0f/m_speed, -1));
    m_Sprite->stopAllActions();
    m_Sprite->runAction(animate);
    m_status = STATUS_RUNNING;
}
void Entity::attack()
{

    Animate* animate = Animate::create(AnimationUtil::createAnimWithFrame(StringUtils::format("%s_attack", name.c_str()), 0.07f, 1));
    m_Sprite->stopAllActions();
    m_Sprite->runAction(RepeatForever::create(Sequence::create(animate,DelayTime::create(0.5f), NULL)));
    m_status = STATUS_ATTACKING;

}
GameMap* Entity::getGamePos()
{
    return m_position;
}
float Entity::getPositionX()
{
    return m_Sprite->getPosition().x;
}