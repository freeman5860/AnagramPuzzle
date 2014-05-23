#ifndef DATA_H_
#define DATA_H_

#include "cocos2d.h"

using namespace cocos2d;

class Data : public CCObject{
public:
	Data();
	virtual ~Data(){}

	void setPoint(int point);
	int getPoint();
	void addPoint(int point);
	void subtractPoint(int point);
	
private:
	int mPoints;
};

#endif