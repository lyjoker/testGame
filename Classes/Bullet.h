//
//  Bullet.h
//  TestGame
//
//  Created by Yuan Lin on 2/24/14.
//
//

#ifndef __TestGame__Bullet__
#define __TestGame__Bullet__

#include "cocos2d.h"

class Enemy;

class Bullet : public cocos2d::Node
{
public:
    CREATE_FUNC(Bullet);
    bool init();
    void removeSelf();
    static float to360Angle(float angle)
	{
		if (angle > 360)
            angle = (int)angle % 360;
		if (angle < 0)
			angle += 360;
		return angle;
	}
protected:
    bool hasRemoved;
    int damage, speed;
    cocos2d::Point point;
    float angle;
    std::string name;
    

};

class MagicBullet : public Bullet
{
public:
    CREATE_FUNC(MagicBullet);
    bool init();
    void setProperty(Enemy* enemy, int _damage, cocos2d::Point point, const char* _name, bool _isExplosion);
    void fire();
    
    cocos2d::Sprite *sprite;
private:
    void update(float dt);
    void explosion();
    Enemy* target;
    bool active;
    bool isExplosion;
};

#endif /* defined(__TestGame__Bullet__) */
