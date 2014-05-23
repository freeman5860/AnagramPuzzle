#ifndef HINT_BUTTON_H_
#define HINT_BUTTON_H_

#include "cocos2d.h"

using namespace cocos2d;

class HintButton: public CCNode{
public:

	void initView();

	CREATE_FUNC(HintButton)
private:
	CCSprite * pButton;
	CCLabelTTF * pLabel;
};

#endif