#include "ExplosionView.h"

ExplosionView::~ExplosionView(){
	CCLog("hello there");
}

void ExplosionView::onEnter(){
	CCLayer::onEnter();

	m_emitter = CCParticleFlower::create();
    m_emitter->retain();
	m_emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("particle.png"));
	m_emitter->setAutoRemoveOnFinish(true);
	m_emitter->setDuration(0.75);
    m_emitter->setSpeed(100);
    m_emitter->setSpeedVar(0);
    m_emitter->setEmissionRate(1000);

	this->addChild(m_emitter);
}

void ExplosionView::setEmitPosition(const CCPoint p){
	m_emitter->setPosition(p);
}