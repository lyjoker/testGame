//
//  GameMap.h
//  TestGame
//
//  Created by Yuan Lin on 2/18/14.
//
//

#ifndef __TestGame__GameMap__
#define __TestGame__GameMap__

#include "cocos2d.h"
#include "cocos-ext.h"

class GameMap : public cocos2d::Sprite
{
public:
    GameMap();
    bool init();
    int getWalkableRight();
    int getWalkableLeft();
    int getWalkableTop();
    int getWalkableBottom();
    GameMap* create(const char*);
private:
    const int mWalkableMapMinX;
    const int mWalkableMapMaxX;
    const int mWalkableMapMinY;
    const int mWalkableMapMaxY;
};

#endif /* defined(__TestGame__GameMap__) */
