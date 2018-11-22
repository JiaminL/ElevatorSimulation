//people.cpp
#include "People.h"
bool People::arrive(int when,int order,int averGU,int averCome){
	arriveTime = when;
	orderNum=order;
	giveupTime = rand()%averGU+averGU/2;
	interTime = rand()%(2*averCome)+1;
	inFloor = rand()%5;
	int distance = rand()%4+1;
	outFloor = (inFloor+distance)%5;
	return true;
} 

bool People::setOrder(int order){
	if(order<=0)return false;
	orderNum=order;return true;
} 

bool People::wantGiveup(int when) const{
	return arriveTime-when>=giveupTime;
}

void People::printOut() const{
	cout<<orderNum<<" "<<arriveTime<<" "<<giveupTime<<" "<<inFloor<<" "<<outFloor;
}
