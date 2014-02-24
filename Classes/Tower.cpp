//
//  Tower.cpp
//  TestGame
//
//  Created by Yuan Lin on 2/24/14.
//
//

#include "Tower.h"

USING_NS_CC;

bool Tower::init(int curHP, int maxHP, int attack, int attSpeed, int attRange, GameMap* position, std::string v_name)
{
    t_curHP = curHP;
    t_maxHP = maxHP;
    t_attack = attack;
    t_attSpeed = attSpeed;
    t_position = position;
    t_attRange = attRange;
    name = v_name;
    auto frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile(
                                        StringUtils::format("%s.plist", name.c_str()),
                                        StringUtils::format("%s.png", name.c_str())
                                        );
    
    t_sprite = Sprite::createWithSpriteFrame(frameCache->getSpriteFrameByName(StringUtils::format("%s.png", name.c_str())));
    t_sprite->setPosition(t_position->getPosition());
    this->schedule(schedule_selector(Tower::towerUpdate), 0.1f);
    return true;
}

void Tower::attack()
{
    Animate* animate = Animate::create(AnimationUtil::createAnimWithFrame(
                                                                          StringUtils::format("%s_attack", name.c_str()),
                                                                          0.07f,
                                                                          1)
                                       );
    t_sprite->stopAllActions();
    t_sprite->runAction(animate);
}

void Tower::towerUpdate(float dt)
{
    if (t_status == STATUS_COOLDOWN)
        return;
    float min = BG_WIDTH + 1;
    Enemy* attEnemy = NULL;
    for( Enemy* enemy : *GameScene::enemyList)
    {
        if (enemy->getGamePos()->line != t_position->line)
            continue;
        float enemy_x = enemy->getGamePos()->x;
        if (abs(enemy_x - t_position->x)<=t_attRange && min>enemy_x)
        {
            min = enemy_x;
            attEnemy = enemy;
        }
    }
    if (attEnemy==NULL && t_status==STATUS_ATTACKING)
    {
        t_status = STATUS_DONOTHING;
        t_sprite->stopAllActions();
        return;
    }
    if (attEnemy!=NULL)
    {
        if (t_status == STATUS_DONOTHING)
            attack();
        attackEnemy(attEnemy);
        t_status = STATUS_COOLDOWN;
        this->runAction(Sequence::create(
                                         DelayTime::create(10.0f/t_attSpeed),
                                         [&](){
                                             t_status = STATUS_ATTACKING;
                                         },
                                         NULL
                                         ));
                        
    }
}

void Tower::attackEnemy(Enemy *enemy)
{
    
}
