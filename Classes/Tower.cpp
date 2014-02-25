//
//  Tower.cpp
//  TestGame
//
//  Created by Yuan Lin on 2/24/14.
//
//

#include "Tower.h"
#include "GameScene.h"
#include "Bullet.h"
#include "GameMap.h"
#include "Common.h"
#include "AnimationUtil.h"
#include "Enemy.h"

USING_NS_CC;

bool Tower::init(int curHP, int maxHP, int attack, float attSpeed, int attRange, float pX, int line, std::string v_name)
{
    t_curHP = curHP;
    t_maxHP = maxHP;
    t_attack = attack;
    t_attSpeed = attSpeed;
    t_position = Point(pX, GameMap::lineToY(line));
    t_line = line;
    t_attRange = attRange;
    name = v_name;
    auto frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile(
                                        StringUtils::format("Tower.plist"),
                                        StringUtils::format("Tower.png")
                                        );
    
    t_sprite = Sprite::createWithSpriteFrame(
                                             frameCache->getSpriteFrameByName(
                                                                              StringUtils::format("%s.png", name.c_str())
                                                                              )
                                             );
    t_sprite->setAnchorPoint(Point(0, 0));
    this->setPosition(t_position.x, t_position.y);
    this->addChild(t_sprite);
    this->schedule(schedule_selector(Tower::towerUpdate), 0.1f);
    t_status = STATUS_DONOTHING;
    return true;
}

void MagicTower::animateAttack()
{
    Animate* animate = Animate::create(AnimationUtil::createAnimWithFrame(
                                                                          StringUtils::format("Effect_PurpleCircle"),
                                                                          0.1f,
                                                                          -1)
                                       );
    auto att_sprite = Sprite::create();
    att_sprite->runAction(animate);
    att_sprite->setPosition(t_sprite->getContentSize().width/2, t_sprite->getContentSize().height);
    this->addChild(att_sprite, 2, 11);
}
void MagicTower::stopAttackAnimate()
{
    auto tmp = this->getChildByTag(11);
    tmp->stopAllActions();
    tmp->removeFromParentAndCleanup(true);
}

void Tower::towerUpdate(float dt)
{
    
    if (t_status == STATUS_COOLDOWN)
        return;
    float min = BG_WIDTH * 2 + 1;
    Enemy* attEnemy = NULL;
    for( Enemy* enemy : *GameScene::enemyList)
    {
        if (enemy==NULL || enemy->hasRemoved) continue;
        if (enemy->getLine() != t_line)
            continue;
        float enemy_x = enemy->getPositionX();
        if (abs(enemy_x - t_position.x)<=t_attRange && min>enemy_x)
        {
            min = enemy_x;
            attEnemy = enemy;
        }
    }
    if (attEnemy==NULL && t_status==STATUS_ATTACKING)
    {
        t_status = STATUS_DONOTHING;
        return;
    }
    if (attEnemy!=NULL)
    {
        if (t_status == STATUS_DONOTHING)
            this->animateAttack();
        this->attackEnemy(attEnemy);
        t_status = STATUS_COOLDOWN;
        this->runAction(Sequence::create(
                                         DelayTime::create(1.0f/t_attSpeed),
                                         CallFunc::create([&](){
                                             t_status = STATUS_ATTACKING;
                                         }),
                                         NULL
                                         ));
                        
    }
}

void MagicTower::attackEnemy(Enemy *enemy)
{
    //CCLOG("attack!");
    MagicBullet *bullet = MagicBullet::create();
    Point tmp = t_position;
    tmp.y += t_sprite->getContentSize().height;
    tmp.x += t_sprite->getContentSize().width / 2;
    bullet->setProperty(enemy, t_attack,  tmp);
    bullet->fire();
    this->getParent()->addChild(bullet);
}

MagicTower* MagicTower::create(int line, float pX)
{
    MagicTower* pRet = new MagicTower;
    if (pRet && pRet->init(MAGICTOWER_HP, MAGICTOWER_HP, MAGICTOWER_ATT, MAGICTOWER_ATTSPEED, MAGICTOWER_RANGE, pX, line, "Tower_Magic"))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
