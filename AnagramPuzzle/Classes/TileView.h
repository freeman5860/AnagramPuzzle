#ifndef TILE_VIEW_H_
#define TILE_VIEW_H_

#include "cocos2d.h"

using namespace cocos2d;

class TileDropDelegate;

class TileView: public CCNode, public CCTargetedTouchDelegate{
public:
	static TileView * initWithLetter(const char * l,float sideLen);
	void randomize();
	void setTileDropDelegate(TileDropDelegate * p);
	void removeTouchDelegate();

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	bool containTouchLocation(CCTouch * pTouch);
	char getLetter();
	void setMatch(bool r);
	bool getIsMatch();

private:
	CCSprite * pSprite;
	char mLetter;
	bool mIsMatch;
	int xOffset;
	int yOffset;
	bool isControl;
	TileDropDelegate * pDropDelegate;
};

#endif