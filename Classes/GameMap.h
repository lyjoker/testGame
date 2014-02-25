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


class GameMap
{
public:
    static cocos2d::Point MapPoint(int line, float position, float nowScale);
    static float lineToY(int line);

};

#endif /* defined(__TestGame__GameMap__) */
