//elevator.cpp
#include "Elevator.h"

void Elevator::set(){
	floor=1;
	Calling=false;
	InOrOut=false;
	AtBase=true;
	state=Idle;
	door=Closed;
	for(int i=0;i<5;i++){
		callCar[i]=callUp[i]=callDown[i]=0;
	} 
}

bool Elevator::upFloor(){
	if(floor==4)
		return false; 
	floor++;
	return true;
}

bool Elevator::downFloor(){
	if(floor==0)
		return false; 
	floor--;
	return true;
}

bool Elevator::changeState(){
	int someCallUp=0;
	int someCallDown=0;
	for(int i=floor-1;i>=0;i--)
		if(beCalled(i)) {
			someCallDown=1;
			break;
		}
	for(int i=floor+1;i<5;i++)
		if(beCalled(i)) {
			someCallUp=1;
			break;
		}
	if(callUp[floor])someCallUp=1;
	if(callDown[floor])someCallDown=1;
	if(!someCallUp&&!someCallDown&&!callCar[floor])
		if(floor>1)someCallDown=1;
		else if(floor<1)someCallUp=1;
	if(state==GoingDown&&!someCallDown){
		if(someCallUp){
			state=GoingUp; 
			return true;
		} 
		else{
			state=Idle; 
			return true; 
		}
	}
	else if(state==GoingUp&&!someCallUp){
		if(someCallDown){
			state=GoingDown; 
			return true;
		} 
		else{
			state=Idle;
			return true; 
		}
	}
	return false;
} 

bool Elevator::upShouldSlow(){
	if(callCar[floor]||callUp[floor]) return true;
	int somecallUp=0;
	int somecallDown=0;
	for(int j=floor-1;j>=0;j--)
		if(beCalled(j)){
			somecallDown=1;
			break;
		}
	if(callDown[floor])somecallDown=1;
	for(int j=floor+1;j<5;j++)
		if(beCalled(j)){
			somecallUp=1;
			break;
		}		
	if(floor>=1&&!somecallUp) return true;
	if(somecallDown&&!somecallUp) return true;
	return false;
}


bool Elevator::downShouldSlow(){
	if(callCar[floor]||callDown[floor]) return true;
	int somecallDown=0;
	int somecallUp=0;
	for(int j=floor+1;j<5;j++)
		if(beCalled(j)){
			somecallUp=1;
			break;
	}
	if(callUp[floor])somecallUp=1;
	for(int j=floor-1;j>=0;j--)
		if(beCalled(j)){
			somecallDown=1;
			break;
		}
	if(floor<=1&&!somecallDown) return true;
	if(somecallUp&&!somecallDown) return true;
	return false;
}

bool Elevator::pressButtomCome(int inFloor,int outFloor){
	if (inFloor<outFloor) callUp[inFloor]=1;
	else if(inFloor>outFloor) callDown[inFloor]=1;
	else return false;
	return true;
}

bool Elevator::pressButtomOut(int outFloor){
	if(outFloor>=0&&outFloor<5) callCar[outFloor]=1;
	else return false;
	return true;
}

int Elevator::getState() const{
	switch(state){
		case GoingUp:return 1;
		case GoingDown:return -1;
		case Idle:return 0;
	}
}

bool Elevator::getAimFloor(int &j) const{
	for(int i=0;i<5;i++)
		if(i!=floor&&beCalled(i)){
			j=i;
			return true;
		}	
	return false;
}

void Elevator::setState(int fl){
	if(fl>floor) state=GoingUp;
	else if(fl<floor) state=GoingDown;
	else state=Idle;
} 

void Elevator::printOut() const{
	cout<<floor<<" "<<state<<" "<<door<<" ";
	for(int i=0;i<5;i++)cout<<callCar[i]<<" ";
	for(int i=0;i<5;i++)cout<<callUp[i]<<" ";
	for(int i=0;i<5;i++)cout<<callDown[i]<<" ";
	
}


bool Elevator::shouldIdle() const{
	for(int i=0;i<5;i++)
		if(beCalled(i)) return false;
	return true;
}

bool Elevator::shouldOpen(int floor) const{
	return isDown()&&CallDown(floor)||isUp()&&CallUp(floor)||CallCar(floor);
}
