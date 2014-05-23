#ifndef EXPLOSION_VIEW_H_
#define EXPLOSION_VIEW_H_

#include "cocos2d.h"

USING_NS_CC;

class ExplosionView: public CCLayerColor{
public:
	~ExplosionView();
	virtual void onEnter();

	void setEmitPosition(const CCPoint p);

	CREATE_FUNC(ExplosionView);

private:
	CCParticleSystem * m_emitter;
};

#endif