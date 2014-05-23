#include "TargetView.h"
#include "Common.h"

using namespace freemanapp;

TargetView::TargetView(void)
{
}


TargetView::~TargetView(void)
{
}

TargetView * TargetView::initWithLetter(const char * l, float sideLen){
	TargetView * tile = new TargetView();
	CCSprite * bg = CCSprite::create("slot.png");
	tile->addChild(bg);
	tile->pSprite = bg;

	float scale = sideLen / bg->getContentSize().width;
	bg->setScale(scale);

	char chLetter[2];
	sprintf(chLetter,"%c",l[0] - 32);
	/*
	CCLabelTTF * letter = CCLabelTTF::create(chLetter,"Arial",78 * scale);
	letter->setColor(ccWHITE);
	tile->addChild(letter);*/

	tile->mIsMatch = false;
	tile->mLetter = chLetter[0];
	
	return tile;
}

bool TargetView::containPoint(CCPoint touchPoint){
	CCRect c = CCRectMake(
                          getPositionX() - pSprite->getTextureRect().size.width * 0.5f * pSprite->getScaleX(),
                          getPositionY() - pSprite->getTextureRect().size.height * 0.5f * pSprite->getScaleY(),
                          pSprite->getTextureRect().size.width * pSprite->getScaleX(),
                          pSprite->getTextureRect().size.height * pSprite->getScaleY()
                          );
	return c.containsPoint(touchPoint);
}

char TargetView::getLetter(){
	return mLetter;
}

void TargetView::setMatch(bool r){
	mIsMatch = r;
}

bool TargetView::getIsMatch(){
	return mIsMatch;
}
