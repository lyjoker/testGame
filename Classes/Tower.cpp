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
    hasRemoved = false;
    t_curHP = curHP;
    t_maxHP = maxHP;
    t_attack = attack;
    t_attSpeed = attSpeed;
    t_position = Point(pX, GameMap::lineToY(line));
    t_line = line;
    t_attRange = attRange;
    name = v_name;
    auto frameCache = SpriteFrameCache::getInstance();
    
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
    
    t_healthbar = ProgressTimer::create(Sprite::create("health_bar_green.png"));
    t_healthbar->setType(ProgressTimer::Type::BAR);
    t_healthbar->setMidpoint(Point(0, 0));
    t_healthbar->setBarChangeRate(Point(1, 0));
    t_healthbar->setPercentage(100);
    t_healthbar->setScale(t_sprite->getContentSize().width / t_healthbar->getContentSize().width);
    t_healthbar->setAnchorPoint(Point(0,0));
    t_healthbar->setPosition(Point(0, -10));
    this->addChild(t_healthbar, 2);
    auto redbar = Sprite::create("health_bar_red.png");
    redbar->setPosition(t_healthbar->getPosition());
    redbar->setScale(t_sprite->getContentSize().width / redbar->getContentSize().width);
    redbar->setAnchorPoint(Point(0,0));
    this->addChild(redbar, 1);
    
    GameScene::towerList->pushBack(this);
    return true;
}

Rect Tower::getEffectRect()
{
    float _width = t_sprite->getContentSize().width;
    float _height = t_sprite->getContentSize().height;
    auto rect = Rect(
                     this->getPositionX() + _width * 0.15,
                     this->getPositionY() + _height * 0.15,
                     _width * 0.7,
                     _height * 0.7
                     );
    return rect;
}
Point Tower::getMidPoint()
{
    return (Point(
                  this->getPositionX() + t_sprite->getContentSize().width / 2,
                  this->getPositionY() + t_sprite->getContentSize().height / 2
                  )
            );
}
void Tower::setDamage(int damage)
{
    t_curHP -= damage;
    t_healthbar->setPercentage(float(t_curHP) / float(t_maxHP) * 100);
    if (t_curHP <= 0)
    {
        Tower::stopAllActionsFromAllChild(this);
        auto dead1 = FadeOut::create(0.5f);
        auto dead2 = Animate::create(AnimationUtil::createAnimWithFrame("Effect_TowerExplosion", 0.1f, 1));
        auto tmp_sprite = Sprite::create();
        tmp_sprite->setPosition(this->getMidPoint()-this->getPosition());
        this->addChild(tmp_sprite);
        tmp_sprite->runAction(dead2);
        t_sprite->runAction(Sequence::create(
                                         dead1,
                                         CallFunc::create(
                                                          [&](){removeSelf();}
                                                          ),
                                         NULL));
    }
}
void Tower::removeSelf()
{
    if(hasRemoved)
		return;
    
	hasRemoved = true;
	unscheduleAllSelectors();
    Tower::stopAllActionsFromAllChild(this);
	this->removeFromParentAndCleanup(true);
    GameScene::towerList->eraseObject(this);
}
void Tower::stopAllActionsFromAllChild(Node *p)
{
    Vector<Node*> children = p->getChildren();
    p->stopAllActions();
    if (p->getChildrenCount()==0)
        return;
    for (Node* it : children)
    {
        stopAllActionsFromAllChild(it);
    }
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
        if (enemy->getLine() != t_line || enemy->getHP()<=0)
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
        this->stopAttackAnimate();
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
    bullet->setProperty(enemy, t_attack,  tmp, "Bullet_PurpleBall", true);
    bullet->fire();
    this->getParent()->addChild(bullet, 3);
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
