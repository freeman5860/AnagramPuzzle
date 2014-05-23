#ifndef TARGET_VIEW_H_
#define TARGET_VIEW_H_

#include "cocos2d.h"

using namespace cocos2d;

class TargetView : public CCNode
{
public:
	TargetView(void);
	~TargetView(void);

	static TargetView * initWithLetter(const char * l,float sideLen);
	bool containPoint(CCPoint touchPoint);
	char getLetter();
	void setMatch(bool r);
	bool getIsMatch();

private:
	CCSprite * pSprite;
	char mLetter;
	bool mIsMatch;
};

#endif

