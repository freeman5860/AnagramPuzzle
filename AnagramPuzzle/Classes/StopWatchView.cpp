#include "StopWatchView.h"
#include <cmath>

StopWatchView * StopWatchView::initView(){
	StopWatchView * p = (StopWatchView*)(CCLabelAtlas::create("11","fonts/tuffy_bold_italic-charmap.plist"));
	return p;
}

void StopWatchView::setSecond(int second){
	char strTime[50];
	float minutes = second / 60;
	minutes =  (minutes > 0.0) ? floor(minutes + 0.5) : ceil(minutes - 0.5); 
	int minu = (int)minutes;
	int sec = second % 60;
	sprintf(strTime," %02d:%02d",minu,sec);
	this->setString(strTime);
}