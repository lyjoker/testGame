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
                                        StringUtils::format("Tower.plist"),
                                        StringUtils::format("Tower.png")
                                        );
    
    t_sprite = Sprite::createWithSpriteFrame(frameCache->getSpriteFrameByName(StringUtils::format("%s.png", name.c_str())));
    t_sprite->setPosition(t_position->getPosition().x, t_position->getPosition().y+125);
    this->addChild(t_sprite);
    this->schedule(schedule_selector(Tower::towerUpdate), 0.1f);
    t_status = STATUS_DONOTHING;
    return true;
}

void Tower::attack()
{
    Animate* animate = Animate::create(AnimationUtil::createAnimWithFrame(
                                                                          StringUtils::format("%s_attack", name.c_str()),
                                                                          0.1f,
                                                                          -1)
                                       );
    t_sprite->stopAllActions();
    t_sprite->runAction(animate);
}

void Tower::towerUpdate(float dt)
{
    
    if (t_status == STATUS_ATTACKING)
        CCLOG("yes");
    if (t_status == STATUS_COOLDOWN)
        return;
    float min = BG_WIDTH * 2 + 1;
    Enemy* attEnemy = NULL;
    for( Enemy* enemy : *GameScene::enemyList)
    {
        if (enemy->getGamePos()->line != t_position->line)
            continue;
        float enemy_x = enemy->getPositionX();
        if (abs(enemy_x - t_position->x*t_position->scale)<=t_attRange && min>enemy_x)
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
                                         CallFunc::create([&](){
                                             t_status = STATUS_ATTACKING;
                                         }),
                                         NULL
                                         ));
                        
    }
}

void Tower::attackEnemy(Enemy *enemy)
{
    CCLOG("attack!");
    MagicBullet *bullet = MagicBullet::create();
    Point tmp = t_position->getPosition();
    tmp.y += t_sprite->getBoundingBox().getMaxY() - t_sprite->getBoundingBox().getMinY();
    bullet->setProperty(enemy, t_attack,  tmp);
    bullet->fire();
    this->addChild(bullet);
}
