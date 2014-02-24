//
//  GameMap.cpp
//  TestGame
//
//  Created by Yuan Lin on 2/18/14.
//
//

#include "GameMap.h"


USING_NS_CC;


const float FLOOR_POS_Y = 110;
const float CELL_POS_Y = 220;


GameMap::GameMap(int v_line, float v_x, float v_scale)
{
    line = v_line;
    x = v_x;
    scale = v_scale;
}
Point GameMap::MapPoint(int line, float position, float nowScale)
{
    if (line == 1)
        return Point(LINE1, position*nowScale);
    if (line == 2)
        return Point(LINE2, position*nowScale);
    return Point(LINE1, position*nowScale);
}
Point GameMap::getPosition()
{
    return GameMap::MapPoint(line, x, scale);
}
