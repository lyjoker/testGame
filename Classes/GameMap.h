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
#include "Common.h"

class GameMap
{
public:
    static cocos2d::Point MapPoint(int line, float position, float nowScale);
    GameMap(int v_line, float v_x, float v_scale);
    int line;
    float x, scale;
    cocos2d::Point getPosition();

};

#endif /* defined(__TestGame__GameMap__) */
