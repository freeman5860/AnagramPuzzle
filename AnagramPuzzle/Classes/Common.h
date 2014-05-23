/*
 * Common.h
 *
 *  Created on: 2014-2-11
 *      Author: apple
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "cocos2d.h"

#define kTileMargin 20

//audio defines
#define kSoundDing  "ding.mp3"
#define kSoundWrong "wrong.m4a"
#define kSoundWin   "win.mp3"

using namespace cocos2d;

namespace freemanapp{
	class Common {
	public:
		static int random(int s,int e);
		static long millisecondNow();

		static int getCameraWith();
		static void setCameraWidth(int width);
		static int getCameraHeight();
		static void setCameraHeight(int height);

	private:
		static int kWidth;
		static int kHeight;
	};
}

#endif /* COMMON_H_ */