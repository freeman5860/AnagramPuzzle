#include "MainScene.h"
#include "Common.h"
#include "TileView.h"
#include "TargetView.h"
#include "SimpleAudioEngine.h"
#include "ExplosionView.h"
#include "FlowerView.h"
#include "stdlib.h"

USING_NS_CC;
using namespace freemanapp;
using namespace CocosDenshion;

MainScene::~MainScene(){
	pTiles->release();
	pTargets->release();
	if(pLevel != NULL){
		delete pLevel;
		pLevel = NULL;
	}
	if(pData != NULL){
		delete pData;
		pData = NULL;
	}
}

CCScene* MainScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainScene *layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	Common::setCameraHeight(visibleSize.height);
	Common::setCameraWidth(visibleSize.width);

	CCSprite * bg = CCSprite::create("board.jpg");
	bg->setPosition(ccp(visibleSize.width * 0.5f,visibleSize.height * 0.5f));
	this->addChild(bg);

	pHUD = HUDView::create();
	this->addChild(pHUD);
	pHUD->pButton->setTarget(this,menu_selector(MainScene::menuHintCallback));
	pHUD->pButton->setEnabled(false);

	pData = new Data();

	pLevel = Level::levelWithNum(1);
	dealRandomAnagram();
    
    return true;
}

void MainScene::dropToPoint(TileView * tile,CCPoint point){
	TargetView * target = NULL;
	CCObject * tv;
	CCARRAY_FOREACH(pTargets,tv){
		TargetView* pTarget = (TargetView*) tv;
		if(pTarget->containPoint(point)){
			target = pTarget;
			break;
		}
	}

	if(target != NULL){
		if(target->getLetter() == tile->getLetter()){
			placeTile(tile,target);

			pData->addPoint(pLevel->mPointPerTile);
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(kSoundDing);
			pHUD->pPointView->countTo(pData->getPoint(),1.5);
		}else{
			tile->randomize();

			CCActionInterval * actionTo = CCMoveTo::create(0.35,
				ccp(tile->getPositionX() + Common::random(-20,20),
				tile->getPositionY() + Common::random(-20,30)));
			tile->runAction(actionTo);

			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(kSoundWrong);
			pData->subtractPoint(pLevel->mPointPerTile / 2);
			pHUD->pPointView->countTo(pData->getPoint(),0.75);
		}
	}

	checkForSuccess();
}

void MainScene::placeTile(TileView * tile,TargetView * target){
	tile->setMatch(true);
	target->setMatch(true);

	tile->removeTouchDelegate();

	CCActionInterval * actionTo = CCMoveTo::create(0.35,ccp(target->getPositionX(),target->getPositionY()));
	tile->runAction(actionTo);
	tile->setRotation(0);
	target->setVisible(false);

	ExplosionView * explode = ExplosionView::create();
	this->addChild(explode);
	explode->setEmitPosition(ccp(target->getPositionX(),target->getPositionY()));
}

void MainScene::checkForSuccess(){
	CCObject * tv;
	CCARRAY_FOREACH(pTargets,tv){
		TargetView* pTarget = (TargetView*) tv;
		if(pTarget->getIsMatch() == false){
			return;
		}
	}

	pHUD->pButton->setEnabled(false);
	stopStopWatch();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(kSoundWin);
	CCLog("Game Over!");

	FlowerView * flower = FlowerView::create();
	this->addChild(flower);
	TargetView * firstTarget = (TargetView*) pTargets->objectAtIndex(0);
	flower->setEmitPosition(ccp(firstTarget->getPositionX(),firstTarget->getPositionY()));
	CCActionInterval * action = CCMoveBy::create(4,ccp((float)(Common::getCameraWith() + 30),flower->getPositionY()));
	flower->runAction(action);
}

void MainScene::startStopWatch(){
	mTimeLeft = pLevel->mTimeToSovle;
	pHUD->pWatch->setSecond(mTimeLeft);

	schedule(schedule_selector(MainScene::downTime),1.0f);
}

void MainScene::stopStopWatch(){
	unschedule(schedule_selector(MainScene::downTime));
}

void MainScene::downTime(float dt){
	mTimeLeft --;
	pHUD->pWatch->setSecond(mTimeLeft);

	if(mTimeLeft == 0){
		stopStopWatch();
	}
}

void MainScene::dealRandomAnagram(){
	Common::random(0, pLevel->pAnagrams->count() - 1);
	int randomIndex =  Common::random(0, pLevel->pAnagrams->count() - 1);

	CCAssert((randomIndex >= 0 && randomIndex < pLevel->pAnagrams->count()),"error random index!");

	CCArray * anagram = (CCArray*)pLevel->pAnagrams->objectAtIndex(randomIndex);

	CCString * ana1 = (CCString*)anagram->objectAtIndex(0);
	CCString * ana2 = (CCString*)anagram->objectAtIndex(1);

	int ana1len = ana1->length();
	int ana2len = ana2->length();

	float tileSide = ceilf( Common::getCameraWith()*0.9 / (float)std::max(ana1len, ana2len) ) - kTileMargin;

	float xOffset = (Common::getCameraWith() - std::max(ana1len,ana2len) * (tileSide + kTileMargin)) / 2;
	xOffset += tileSide/2;

	pTiles = CCArray::createWithCapacity(ana1len);

	const char * ana1Letter = ana1->getCString();
	for(int i = 0;i < ana1len; i++){
		char letter[3];
		sprintf(letter,"%c",ana1Letter[i]);

		if(letter[0] != ' '){
			TileView * tile = TileView::initWithLetter(letter,tileSide);
			tile->setPosition(ccp(xOffset + i * (tileSide + kTileMargin),Common::getCameraHeight() / 4));
			this->addChild(tile);
			tile->randomize();
			tile->setTileDropDelegate(this);
			pTiles->addObject(tile);
		}
	}
	pTiles->retain();

	pTargets = CCArray::createWithCapacity(ana2len);

	const char * ana2Letter = ana2->getCString();
	for(int i = 0;i < ana2len; i++){
		char letter[3];
		sprintf(letter,"%c",ana2Letter[i]);

		if(letter[0] != ' '){
			TargetView * target = TargetView::initWithLetter(letter,tileSide);
			target->setPosition(ccp(xOffset + i * (tileSide + kTileMargin),Common::getCameraHeight() / 4 * 3));
			this->addChild(target);
			pTargets->addObject(target);
		}
	}
	pTargets->retain();

	startStopWatch();

	pHUD->pButton->setEnabled(true);
}

void MainScene::menuHintCallback(CCObject* pSender){
	pHUD->pButton->setEnabled(false);

	pData->subtractPoint(pLevel->mPointPerTile);
	pHUD->pPointView->countTo(pData->getPoint(),1.5);

	TargetView * target = NULL;
	CCObject * obj = NULL;
	CCARRAY_FOREACH(pTargets,obj){
		if(!((TargetView*) obj)->getIsMatch()){
			target = (TargetView*) obj;
			break;
		}
	}

	TileView * tile = NULL;
	CCARRAY_FOREACH(pTiles,obj){
		if(!((TileView*) obj)->getIsMatch() && (target->getLetter() == ((TileView*) obj)->getLetter())){
			tile = (TileView*) obj;
			break;
		}
	}

	tile->setZOrder(999);

	placeTile(tile,target);

	pHUD->pButton->setEnabled(true);

	checkForSuccess();
}

void MainScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
