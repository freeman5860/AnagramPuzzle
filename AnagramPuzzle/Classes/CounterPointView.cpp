#include "CounterPointView.h"

CounterPointView* CounterPointView::initWithValue(int v){
	CounterPointView * p = (CounterPointView*)(CCLabelAtlas::create("11","fonts/tuffy_bold_italic-charmap.plist"));
	char strPoint[10];
	sprintf(strPoint,"%d",v);
	p->setString(strPoint);
	p->value = v;
	p->setScale(0.5);
	return p;
}

void CounterPointView::setValue(int v){
	this->value = v;
	char strPoint[10];
	sprintf(strPoint,"%d",v);
	setString(strPoint);
}

void CounterPointView::updateValueBy(float dt){
	this->value += (int)mValueDelta;

	if((int)mValueDelta > 0){
		if(this->value > mEndValue){
			this->value = mEndValue;
			return;
		}
	}else{
		if(this->value < mEndValue){
			this->value = mEndValue;
			return;
		}
	}

	setValue(value);

	schedule(schedule_selector(CounterPointView::updateValueBy),mDelta);
}

void CounterPointView::countTo(int to, float duration){
	this->mDelta = duration / (abs(to - value) + 1);
	if(mDelta < 0.05) mDelta = (float)0.05;

	mEndValue = to;

	unscheduleAllSelectors();

	if(to - this->value > 0){
		mValueDelta = 1;
		updateValueBy(1);
	}else{
		mValueDelta = -1;
		updateValueBy(-1);
	}
}