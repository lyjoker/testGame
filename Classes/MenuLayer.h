//
//  MenuLayer.h
//  TestGame
//
//  Created by Yuan Lin on 2/24/14.
//
//

#ifndef __TestGame__MenuLayer__
#define __TestGame__MenuLayer__

#include "cocos2d.h"
#include "Common.h"



class MenuLayer : public cocos2d::Layer
{
public:
    bool init();
    CREATE_FUNC(MenuLayer);
    cocos2d::LabelTTF* timeDisplayer;
};

#endif /* defined(__TestGame__MenuLayer__) */
