//people.h
#ifndef PEOPLE_H
#define PEOPLE_H
#include <cstdlib>
#include <iostream>
using namespace std;

class People{
	private:
		int arriveTime;
		int orderNum;
		int inFloor,outFloor;
		int giveupTime;
		int interTime;//After "interTime",next peope will coming.
	public:
		bool arrive(int when,int order,int averGU=300,int averCome=100);
		bool setOrder(int order);
		bool wantGiveup(int when) const;
		bool wantUp() const{return outFloor>inFloor;}
		bool wantDown() const{return outFloor<inFloor;}
		int getOutFloor() const{return outFloor;}
		int getInFloor() const{return inFloor;} 
		int getOrderNum() const{return orderNum;}
		int getGvUpTime() const{return arriveTime+giveupTime;}
		int getNextInTime() const{return arriveTime+interTime;}
		int getArriveTime() const{return arriveTime;}
		void printOut() const;
};

#endif
