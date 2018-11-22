//eventList.h
#ifndef EVENTLIST_H
#define EVENTLIST_H
#include "Elevator.h"
#include "Queue.h"
#include "EleStack.h"
#include <cstdlib>

//For people
const int PE_BEGIN=0;
const int PE_COME=1;//A person enter System£¬then press the button and wait in the queue
const int PE_GVUP=2;//Give up
const int PE_IN=3;//Enter elevator
const int PE_OUT=4;//Leave elevator
const int PE_END=5;

//For elevator
const int EL_BEGIN=10;
const int EL_BASE=11;//Go to base floor
const int EL_OPEN=12;//Open door
const int EL_CLOSE=13;//Close door
const int EL_READY_UP=14;//Ready to up
const int EL_READY_DOWN=15;//Ready to down
const int EL_UP=16;//Up a floor
const int EL_DOWN=17;//Down a floor
const int EL_STOP_UP=18;//From up to stop
const int EL_STOP_DOWN=19;//From down to stop
const int EL_START_IDLE=20;
const int EL_END=21; 

const int DOOR_TIME=20;
const int START_TIME=20;
const int PEOPLE_MOVE_TIME=25;
const int TEST_TIME=40; 
const int IDLE_TIME=300;
const int SET_CLOSE_TIME=76; 

const int ACC_TIME=15;//acceleration
const int UP_FLOOR_TIME=51;
const int DOWN_FLOOR_TIME=61;
const int UP_DED_TIME=14;//deceleration
const int DOWN_DEC_TIME=23;//deceleration

typedef struct Event{
	int OccurTime;
	int NType;//PE_XX or EL_XX 
	People person;
}Event;

class EventList
{
	private:
		struct Node{
			Event event;
			struct Node *next;
		};
		Node *head; 
		
		Elevator elevator;
		Queue Q[5];
		EleStack ES;
		
		People NeverUse;//Just use for addEvent,because some events don't have any information of people.
		int ElSize;
		int averGvUp,averCome;
		int comeNum,succeedNum;
		long allUseTime,allSuccTime;
		
	public:
		
		EventList();
		~EventList();
		void initSystem();
		
		bool isEmpty() const{return (head->next==NULL);}
		bool aboutPe(int NType) const{return (NType>PE_BEGIN&&NType<PE_END);}
		bool aboutEl(int NType) const{return (NType>EL_BEGIN&&NType<EL_END);}
		bool haveBeCalled(int when) const;
		void outputEvent(const Event &event) ;
		void printType(int NType) const;
		void printResult()const;
		bool canFindIdle(int &when) const;
		
		bool addEvent(int when,int NType,const People &person);
		bool deleFirst(); 
		void findPreNode(int when,Node* &pre);
		void cancelGvUp(int orderNum);
		void cancelReady(); 
		void cancelGoBase();
		
		bool dealEvent(int when);
		
		void dealPeCome(Event &event);
		void dealPeGvUp(Event &event);
		void dealPeIn(Event &event);
		void dealPeOut(Event &event);
		
		void dealElBase(Event &event);
		void dealElOpen(Event &event);
		void dealElClose(Event &event);
		void dealElUReady(Event &event);
		void dealElUp(Event &event);
		void dealElUStop(Event &event);
		void dealElDReady(Event &event);
		void dealElDown(Event &event);
		void dealElDStop(Event &event);
		void dealElSttId(Event &event);
		
		void ControPress(int when,int inFloor,int outFloor);
		
};

#endif
