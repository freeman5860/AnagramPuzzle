#ifndef FLOWER_VIEW_H_
#define FLOWER_VIEW_H_

#include "cocos2d.h"

USING_NS_CC;

class FlowerView: public CCLayer{
public:
	~FlowerView();
	virtual void onEnter();

	void setEmitPosition(const CCPoint p);

	CREATE_FUNC(FlowerView);

private:
	CCParticleSystem * m_emitter;
};

#endif