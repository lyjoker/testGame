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
#include "Tower.h"
#include "Bullet.h"

USING_NS_CC;


bool Enemy::initWithProperty(const char* pName, int pHP, int pSpeed, int pAttack, int pLine, float pX, float attSpeed, int attRange)
{
    hasRemoved = false;
    name = pName;
    m_curHP = m_maxHP = pHP;
    m_speed = pSpeed;
    m_attack = pAttack;
    m_position = Point(pX, GameMap::lineToY(pLine));
    m_line = pLine;
    m_attSpeed = attSpeed;
    m_attRange = attRange;
    auto frameCache = SpriteFrameCache::getInstance();
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
    /*Point tmp = m_position;
    float dist = tmp.x;
    tmp.x = 0;
    auto moveto = MoveTo::create(dist/m_speed, tmp);
    
    
    this->animateRun();
    this->runAction(moveto);
    */
    GameScene::enemyList->pushBack(this);
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
    return true;
}
bool Enemy::setDefaultProperty()
{
    pxWidthRate = 0.15f;
    pxHeightRate = 0.15f;
    widthRate = 0.7f;
    heightRate = 0.7f;
    runInternalTime = 20.0f/m_speed;
    this->stopActionAndRun();
    return true;
}
Rect Enemy::getEffectRect()
{
    float _width = m_sprite->getContentSize().width;
    float _height = m_sprite->getContentSize().height;
    auto rect = Rect(
                     this->getPositionX() + _width * pxWidthRate,
                     this->getPositionY() + _height * pxHeightRate,
                     _width * widthRate,
                     _height * heightRate
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
    Tower* attTower = NULL;
    for( Tower* tower : *GameScene::towerList)
    {
        if (tower==NULL || tower->hasRemoved) continue;
        if (tower->getLine() != m_line || tower->getHP()<=0)
            continue;
        if ((m_attRange==0 && this->getEffectRect().intersectsRect(tower->getEffectRect()))
            || (m_attRange>0 && this->getPosition().getDistance(tower->getMidPoint())<=m_attRange))
        {
            attTower = tower;
            break;
        }
    }
    if (attTower==NULL && m_status==STATUS_ATTACKING)
    {
        m_status = STATUS_RUNNING;
        this->stopActionAndRun();
        return;
    }
    if (attTower!=NULL)
    {
        this->stopAllActions();
        this->animateAttack();
        this->attackTower(attTower);
        m_status = STATUS_COOLDOWN;
        this->runAction(Sequence::create(
                                         DelayTime::create(0.5f/m_attSpeed),
                                         CallFunc::create([&](){
                                                                m_status = STATUS_ATTACKING;
                                                                }),
                                         NULL
                                         ));
        
    }

    
}
void Enemy::stopActionAndRun()
{
    Point tmp = this->getPosition();
    float dist = tmp.x;
    tmp.x = 0;
    auto moveto = MoveTo::create(dist/m_speed, tmp);
    
    this->animateRun(runInternalTime);
    this->runAction(moveto);
}
void Enemy::attackTower(Tower *tower)
{
    tower->setDamage(m_attack);
}

EnemyKnight* EnemyKnight::create(int pLine, float pX)
{
    EnemyKnight *pRet = new EnemyKnight();
    if (pRet && pRet->initWithProperty("Enemy_Knight", 1000, 60, 40, pLine, pX, 1.0f, 0) && pRet->setDefaultProperty())
    {
        pRet->autorelease();
        return pRet;
    }else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
EnemyBlueDragon* EnemyBlueDragon::create(int pLine, float pX)
{
    EnemyBlueDragon *pRet = new EnemyBlueDragon();
    if (pRet && pRet->initWithProperty("Enemy_BlueDragon", 500, 100, 60, pLine, pX, 0.7f, 350) && pRet->setDefaultProperty())
    {
        pRet->autorelease();
        return pRet;
    }else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool EnemyBlueDragon::setDefaultProperty()
{
    pxWidthRate = 0.3f;
    pxHeightRate = 0.35f;
    widthRate = 0.4f;
    heightRate = 0.35f;
    this->setPosition(this->getPosition()+Point(0, 300+rand()%100-50));
    runInternalTime = 6.0f/m_speed;
    this->stopActionAndRun();
    //schedule(schedule_selector(EnemyBlueDragon::enemyUpdate), 0.1f);
    return true;
}
void EnemyBlueDragon::attackTower(Tower* tower)
{
    /*MagicBullet *bullet = MagicBullet::create();
    Point tmp = this->getPosition();
    tmp.y += m_sprite->getContentSize().height;
    bullet->setProperty(tower, m_attack,  tmp, "Bullet_PurpleBall", true);
    bullet->fire();
    this->getParent()->addChild(bullet, 3);*/
    this->animateRun(runInternalTime);
}
void EnemyBlueDragon::enemyUpdate(float dt)
{
    CCLOG("BlueDragon Update!");
}