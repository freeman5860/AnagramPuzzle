#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Level.h"
#include "TileDropDelegate.h"
#include "HUDView.h"
#include "Data.h"

class TargetView;

class MainScene : public cocos2d::CCLayer, public TileDropDelegate
{
public:
	~MainScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void menuHintCallback(CCObject* pSender);

	void dealRandomAnagram();
	void dropToPoint(TileView * tile,cocos2d::CCPoint point);
	void placeTile(TileView * tile,TargetView * target);
	void checkForSuccess();
	void startStopWatch();
	void stopStopWatch();
	void downTime(float dt);
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainScene);
private:
	Level * pLevel;
	CCArray * pTiles;
	CCArray * pTargets;
	HUDView * pHUD;
	Data * pData;
	int mTimeLeft;
};

#endif // __MAIN_SCENE_H__
