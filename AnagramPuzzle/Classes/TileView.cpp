#include "TileView.h"
#include "Common.h"
#include "TileDropDelegate.h"

using namespace freemanapp;

TileView * TileView::initWithLetter(const char * l, float sideLen){
	TileView * tile = new TileView();
	CCSprite * bg = CCSprite::create("tile.png");
	tile->addChild(bg);
	tile->pSprite = bg;
	float scale = sideLen / bg->getContentSize().width;
	bg->setScale(scale);

	char chLetter[2];
	sprintf(chLetter,"%c",l[0] - 32);
	CCLabelTTF * letter = CCLabelTTF::create(chLetter,"Arial",75 * scale);
	letter->setColor(ccWHITE);
	tile->addChild(letter);

	tile->mIsMatch = false;
	tile->mLetter = chLetter[0];

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(tile,0,true);
	tile->isControl = false;
	
	return tile;
}

void TileView::randomize(){
	float rotation = Common::random(0,50) /(float)100 - 0.2;
	this->setRotation(rotation * 10);

	int yOffset = Common::random(0,10);
	this->setPositionY(this->getPositionY() + yOffset);
}

void TileView::setTileDropDelegate(TileDropDelegate * p){
	pDropDelegate = p;
}

void TileView::removeTouchDelegate(){
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

char TileView::getLetter(){
	return mLetter;
}

void TileView::setMatch(bool r){
	mIsMatch = r;
}

bool TileView::getIsMatch(){
	return mIsMatch;
}

bool TileView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	if(!containTouchLocation(pTouch)){
		return false;
	}

	isControl = true;
	this->setZOrder(999);

	CCPoint point = pTouch->getLocationInView();
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(point);
	this->xOffset = touchPoint.x - this->getPositionX();
	this->yOffset = touchPoint.y - this->getPositionY();

	return true;
}

void TileView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
	if(!isControl){
		return;
	}

	CCPoint point = pTouch->getLocationInView();
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(point);
	float x = touchPoint.x - this->xOffset;
	float y = touchPoint.y - this->yOffset;

	this->setPosition(ccp(x,y));
}

void TileView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
	CCPoint point = pTouch->getLocationInView();
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(point);

	if(isControl){
		isControl = false;
		if(pDropDelegate != NULL){
			pDropDelegate->dropToPoint(this,touchPoint);
		}
	}	
}

void TileView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
	ccTouchEnded(pTouch, pEvent);
}

bool TileView::containTouchLocation(CCTouch * pTouch){
	
	CCPoint point = pTouch->getLocationInView();
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(point);
	CCRect c = CCRectMake(
                          getPositionX() - pSprite->getTextureRect().size.width * 0.5f * pSprite->getScaleX(),
                          getPositionY() - pSprite->getTextureRect().size.height * 0.5f * pSprite->getScaleY(),
                          pSprite->getTextureRect().size.width * pSprite->getScaleX(),
                          pSprite->getTextureRect().size.height * pSprite->getScaleY()
                          );
	return c.containsPoint(touchPoint);
}