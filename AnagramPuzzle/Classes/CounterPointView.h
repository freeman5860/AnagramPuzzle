#ifndef COUNTER_POINT_VIEW_H_
#define COUNTER_POINT_VIEW_H_

#include "cocos2d.h"

using namespace cocos2d;

class CounterPointView: public CCLabelAtlas{
public:
	static CounterPointView* initWithValue(int v);

	void countTo(int p, float duration);
	void updateValueBy(float dt);

	void setValue(int v);

	CREATE_FUNC(CounterPointView);

private:
	CounterPointView(){};

	int value;
	float mDelta;
	int mEndValue;
	float mValueDelta;
};

#endif