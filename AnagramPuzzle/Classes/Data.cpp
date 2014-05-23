#include "Data.h"

Data::Data(){
	mPoints = 0;
}

void Data::setPoint(int point){
	if(point > 0){
		mPoints = point;
	}else{
		mPoints = 0;
	}
}

int Data::getPoint(){
	return mPoints;
}

void Data::addPoint(int point){
	mPoints += point;
}

void Data::subtractPoint(int point){
	mPoints -= point;
}