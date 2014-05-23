#ifndef STOP_WATCH_VIEW_H_
#define STOP_WATCH_VIEW_H_

#include "cocos2d.h"

using namespace cocos2d;

class StopWatchView : public CCLabelAtlas{
public:
	StopWatchView(){}

	static StopWatchView * initView();
	void setSecond(int seconds);

	CREATE_FUNC(StopWatchView);
};

#endif