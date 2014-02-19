//
//  GameScene.cpp
//  TestGame
//
//  Created by Yuan Lin on 2/18/14.
//
//

#include "GameScene.h"

USING_NS_CC;

//Size visibleSize = Director::getInstance()->getVisibleSize();
float MAP_POS_X = WIN_WIDTH / 2;
float MAP_POS_Y = WIN_HEIGHT / 2;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
    
}
bool GameScene::init()
{
    bool bRet = false;
    do{
        initBG();
        auto testEnemy = Enemy::create();
        Sprite* testSprite = Sprite::create();
        testEnemy->bindSprite(testSprite);
        testEnemy->setPosition(200, 200);
        testEnemy->run();
        this->addChild(testEnemy);
        bRet = true;
    }while (0);
    return bRet;
}

void GameScene::initBG()
{

    m_bgSprite = Sprite::create("background.png");
    scaleNow = 2.0f;
    m_bgSprite->setScale(scaleNow);
    m_bgSprite->setPosition(Point(BG_WIDTH, BG_HEIGHT));
    this->addChild(m_bgSprite, 0);
    this->setPosition(-BG_WIDTH + WIN_WIDTH/2,-BG_HEIGHT + WIN_HEIGHT/2);
    auto bgListener = EventListenerTouchOneByOne::create();
    bgListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBGBegan, this);
    bgListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchBGMoved, this);
    bgListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchBGEnded, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(bgListener, m_bgSprite);
    //getEventDispatcher()->addEventListenerWithFixedPriority(bgListener, 100);
}
bool GameScene::onTouchBGBegan(Touch* touch, Event* event)
{
    nowTouchPoint = touch->getLocation();
    return true;
}
void GameScene::onTouchBGMoved(Touch* touch, Event* event)
{
    Point tmpPoint = touch->getLocation();
    //layerMove(nowTouchPoint.x - tmpPoint.x, -nowTouchPoint.y + tmpPoint.y);
    Point nowPoint = this->getPosition();
    nowPoint = nowPoint + (tmpPoint - nowTouchPoint);
    this->setPosition(nowPoint);
    nowTouchPoint = tmpPoint;
}
void GameScene::onTouchBGEnded(Touch* touch, Event* event)
{
    Point nowPoint = this->getPosition();
    Point oriPoint = nowPoint;
    updateEdges();
    nowPoint.x = fmin(maxWidth, nowPoint.x);
    nowPoint.x = fmax(minWidth, nowPoint.x);
    nowPoint.y = fmin(maxHeight, nowPoint.y);
    nowPoint.y = fmax(minHeight, nowPoint.y);
    if (!nowPoint.equals(oriPoint)){
        auto moveTo = MoveTo::create(0.5f, nowPoint);
        this->runAction(moveTo);
    }
}
void GameScene::updateEdges()
{
    maxWidth = 0;
    minWidth = WIN_WIDTH - scaleNow * BG_WIDTH;
    maxHeight = 0;
    minHeight = WIN_HEIGHT - scaleNow * BG_HEIGHT;
}
