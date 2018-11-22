//elevator.h 
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <iostream>
using namespace std;

class Elevator{
	private:
		int floor;
		enum {GoingUp, GoingDown, Idle} state;//"Idle" means no caling
		enum {Closing, Closed, Opening ,Opened} door;
		int callCar[5];
		int callUp[5];
		int callDown[5];
		
	public:
		bool InOrOut;//someone in or out door(D1)
		bool AtBase;
		bool Calling;
		
		bool isUp() const{return state==GoingUp;}
		bool isDown() const{return state==GoingDown;}
		bool isIdle() const{return state==Idle;}
		bool isOpening()const{return door==Opening;}
		bool hasClosed()const{return door==Closed;}
		bool hasOpened()const{return door==Opened;}
		bool isClosing()const{return door==Closing;}
		bool atFloor(int fl) const{return fl==floor;}
		bool CallUp(int fl) const{return callUp[fl];} 
		bool CallDown(int fl) const{return callDown[fl];} 
		bool CallCar(int fl) const{return callCar[fl];} 
		
		void setUp() {state=GoingUp;}
		void setDown()  {state=GoingDown;}
		void setOpening() {door=Opening;} 
		void setClosing() {door=Closing;} 
		void setOpened() {door=Opened;} 
		void setClosed() {door=Closed;}
		
		
		void set();
		bool upFloor();
		bool downFloor();
		void reCallCar(){callCar[floor]=0;}
		void reCallUp(){callUp[floor]=0;}
		void reCallDown(){callDown[floor]=0;}
		
		void setState(int fl);
		bool changeState();
		bool upShouldSlow();
		bool downShouldSlow();
		bool pressButtomCome(int inFloor,int outFloor);
		bool pressButtomOut(int outFloor);
		bool beCalled(int i) const{return callCar[i]||callUp[i]||callDown[i];}
		//bool stopAtBase() const{return (state==Idle&&floor==1);} 
		int getFloor() const{return floor;}
		int getState() const;
		bool getAimFloor(int &j) const;
		void printOut() const;
		bool shouldIdle() const;
		bool shouldOpen(int floor) const;
};

#endif
