//simulation.cpp
#include "EventList.h"
#include <ctime>

void initialize(EventList &L,int &TotalTime){
	//get input
	TotalTime=1000000; 
	srand(time(0));
	L.initSystem();
}

int main(){
	EventList L;
	int TotalTime;
	initialize(L,TotalTime);

	int nowTime=0;
	while(nowTime<TotalTime)
		if(L.dealEvent(nowTime)==false)
			nowTime++;
	
	L.printResult();
	return 0;
}




