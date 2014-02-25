//
//  Entity.cpp
//  TestGame
//
//  Created by Yuan Lin on 2/19/14.
//
//

#include "Creature.h"
#include "Common.h"
#include "AnimationUtil.h"

USING_NS_CC;


void Creature::animateRun()
{
    
    Animate* animate = Animate::create(AnimationUtil::createAnimWithFrame(StringUtils::format("%s_run", name.c_str()), 20.0f/m_speed, -1));
    m_sprite->stopAllActions();
    m_sprite->runAction(animate);
    m_status = STATUS_RUNNING;
}
void Creature::animateAttack()
{

    Animate* animate = Animate::create(AnimationUtil::createAnimWithFrame(StringUtils::format("%s_attack", name.c_str()), 0.07f, 1));
    m_sprite->stopAllActions();
    m_sprite->runAction(RepeatForever::create(Sequence::create(animate,DelayTime::create(1.0f/m_attSpeed), NULL)));
    m_status = STATUS_ATTACKING;

}
int Creature::getLine()
{
    return m_line;
}
