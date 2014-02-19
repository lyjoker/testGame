//
//  Entity.cpp
//  TestGame
//
//  Created by Yuan Lin on 2/19/14.
//
//

#include "Entity.h"

USING_NS_CC;

void Entity::bindSprite(Sprite* sprite)
{
    m_Sprite = sprite;
    this->addChild(m_Sprite);
}
