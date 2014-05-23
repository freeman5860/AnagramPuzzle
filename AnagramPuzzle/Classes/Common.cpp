/*
 * Common.cpp
 *
 *  Created on: 2014-2-11
 *      Author: apple
 */

#include "Common.h"

using namespace freemanapp;

int Common::kWidth = 0;
int Common::kHeight = 0;

int Common::random(int s,int e){
	float i = CCRANDOM_0_1()*(e-s+1)+s;
	return (int)i;
}

long Common::millisecondNow(){
	struct cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void Common::setCameraWidth(int width){
	kWidth =width;
}

int Common::getCameraWith(){
	return kWidth;
}

void Common::setCameraHeight(int height){
	kHeight = height;
}

int Common::getCameraHeight(){
	return kHeight;
}