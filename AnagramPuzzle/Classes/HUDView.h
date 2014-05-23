#ifndef HUD_VIEW_H_
#define HUD_VIEW_H_

#include "cocos2d.h"
#include "StopWatchView.h"
#include "CounterPointView.h"
using namespace cocos2d;

class HUDView : public CCLayer{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	// implement the "static node()" method manually
    CREATE_FUNC(HUDView);

private:
	StopWatchView * pWatch;
	CounterPointView * pPointView;
	CCMenuItemImage * pButton;
	CCMenu * pMenu;
	CCLabelTTF * pLabel;
public:
	friend class MainScene;
};

#endif
