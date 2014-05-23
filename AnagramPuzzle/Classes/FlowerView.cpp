#include "FlowerView.h"

FlowerView::~FlowerView(){

}

void FlowerView::onEnter(){
	CCLayer::onEnter();

	m_emitter = CCParticleFlower::create();
    m_emitter->retain();
	m_emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("particle.png"));

	this->addChild(m_emitter);
}

void FlowerView::setEmitPosition(const CCPoint p){
	m_emitter->setPosition(p);
}