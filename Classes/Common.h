//
//  Common.h
//  TestGame
//
//  Created by Yuan Lin on 2/18/14.
//
//

#ifndef TestGame_Common_h
#define TestGame_Common_h



const float WIN_WIDTH = 960;
const float WIN_HEIGHT = 640;
const float BG_WIDTH = 1100;
const float BG_HEIGHT = 552;
const float LEFT_EDGE_X = 0;
const float RIGHT_EDGE_X = BG_WIDTH * 2;
const float LINE1 = 201;
const float LINE2 = 670;
const float LINE3 = 900;

#define STATUS_RUNNING 1
#define STATUS_ATTACKING 2
#define STATUS_DONOTHING 3
#define STATUS_COOLDOWN 4

#define MAGICTOWER_HP 1000
#define MAGICTOWER_ATT 100
#define MAGICTOWER_ATTSPEED 2.5f
#define MAGICTOWER_RANGE 500

#endif
