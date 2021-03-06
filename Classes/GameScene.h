//
//  GameScene.h
//  TestGame
//
//  Created by Yuan Lin on 2/18/14.
//
//

#ifndef __TestGame__GameScene__
#define __TestGame__GameScene__

#include "cocos2d.h"
#include "GameMap.h"
#include "Common.h"
#include "Enemy.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    bool init();
    CREATE_FUNC(GameScene);
    
private:
    void initBG();
    cocos2d::Sprite* m_bgSprite;
    float scaleNow;
    bool onTouchBGBegan(cocos2d::Touch*, cocos2d::Event*);
    void onTouchBGMoved(cocos2d::Touch*, cocos2d::Event*);
    void onTouchBGEnded(cocos2d::Touch*, cocos2d::Event*);
    cocos2d::Point nowTouchPoint;
    void updateEdges();
    float maxWidth, minWidth, maxHeight, minHeight;
};


#endif /* defined(__TestGame__GameScene__) */
