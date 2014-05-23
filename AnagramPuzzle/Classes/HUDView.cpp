#include "HUDView.h"
#include "Common.h"

using namespace freemanapp;

bool HUDView::init(){
	if(! CCLayer::init()){
		return false;
	}

	pWatch = StopWatchView::initView();
	pWatch->setSecond(0);
	pWatch->setPosition(ccp(Common::getCameraWith()*0.5,
		Common::getCameraHeight() * 0.95));
	pWatch->setScale(0.7);
	CCPoint p = pWatch->getAnchorPoint();
	CCLog("%f,%f",p.x,p.y);
	this->addChild(pWatch);

	pPointView = CounterPointView::initWithValue(0);
	pPointView->setColor(ccc3(97,25,9));
	pPointView->setPosition(ccp(Common::getCameraWith()*0.05,Common::getCameraHeight() * 0.9));
	this->addChild(pPointView);

	pButton = CCMenuItemImage::create("btn.png","btn.png");
	pButton->setOpacity(255*0.8);
	pMenu = CCMenu::create(pButton,NULL);
	pMenu->setPosition(CCPointZero);
	pButton->setPosition(ccp(Common::getCameraWith() * 0.9,Common::getCameraHeight() * 0.9));
	this->addChild(pMenu);
	pLabel = CCLabelTTF::create("Hint!","fonts/Comic_Andy.ttf",23);
	pLabel->setPosition(ccp(Common::getCameraWith() * 0.9,Common::getCameraHeight() * 0.9));
	this->addChild(pLabel);
		
	return true;
}