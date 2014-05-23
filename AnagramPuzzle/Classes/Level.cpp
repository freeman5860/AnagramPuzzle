#include "Level.h"

Level * Level::levelWithNum(int levelNum){
	char fileName[50];
	char fullPath[150];
	sprintf(fileName,"level%d.plist",levelNum);
	CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(fileName,fullPath);
	CCDictionary * pListDict = CCDictionary::createWithContentsOfFile(fileName);

	if(pListDict == NULL){
		CCLog("level config not found");
	}

	Level * l = new Level();
	CCString * tempStr;
	tempStr = dynamic_cast<CCString*>(pListDict->objectForKey("pointsPerTile"));
	l->mPointPerTile = tempStr->intValue();
	tempStr = dynamic_cast<CCString*>(pListDict->objectForKey("timeToSolve"));
	l->mTimeToSovle = tempStr->intValue();
	l->pAnagrams = dynamic_cast<CCArray*>(pListDict->objectForKey("anagrams"));
	l->pAnagrams->retain();

	return l;
}