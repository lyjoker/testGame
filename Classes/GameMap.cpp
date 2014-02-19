//
//  GameMap.cpp
//  TestGame
//
//  Created by Yuan Lin on 2/18/14.
//
//

#include "GameMap.h"
#include "Common.h"

USING_NS_CC;
USING_NS_CC_EXT;

const float FLOOR_POS_Y = 110;
const float CELL_POS_Y = 220;
const float LEFT_EDGE_X = -BG_WIDTH / 2 + WIN_WIDTH / 2;
const float RIGHT_EDGE_X = BG_WIDTH / 2 + WIN_WIDTH / 2;

GameMap::GameMap()
    : mWalkableMapMaxX(RIGHT_EDGE_X), mWalkableMapMinX(LEFT_EDGE_X),
    mWalkableMapMaxY(CELL_POS_Y), mWalkableMapMinY(FLOOR_POS_Y)
{
    //sSprite::create("background.png");
    init();
}
bool GameMap::init()
{
    return true;
}
GameMap* GameMap::create(const char* tmp)
{
    Sprite::create(tmp);
    return this;
}
int GameMap::getWalkableRight()
{
	return mWalkableMapMaxX;
}

int GameMap::getWalkableTop()
{
	return mWalkableMapMaxY;
}

int GameMap::getWalkableLeft()
{
	return mWalkableMapMinX;
}

int GameMap::getWalkableBottom()
{
	return mWalkableMapMinY;
}