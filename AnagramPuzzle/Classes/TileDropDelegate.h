#ifndef TILE_DROP_DELEGATE_H_
#define TILE_DROP_DELEGATE_H_

#include "cocos2d.h"

class TileView;

using namespace cocos2d;

class TileDropDelegate{
public:
	virtual void dropToPoint(TileView * tile,cocos2d::CCPoint point) = 0;
};
#endif