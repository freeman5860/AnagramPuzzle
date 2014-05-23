#ifndef LEVEL_H_
#define LEVEL_H_

#include "cocos2d.h"

using namespace cocos2d;

class Level:public CCObject{
public:
	static Level * levelWithNum(int levelNum);

public:
	int mPointPerTile;
	int mTimeToSovle;
	CCArray * pAnagrams;
};

#endif