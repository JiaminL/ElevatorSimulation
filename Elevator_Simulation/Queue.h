//queue.h
#ifndef QUEUE_H
#define QUEUE_H
#include "People.h" 


class Queue{
	private:
		struct Node{
			People person;
			struct Node *next; 
		}; 
		Node *front;
		Node *rear;
		int items;
	public:
		Queue();
		~Queue();
		
		bool getNext() const{return front->next;}
		bool isEmpty() const{return items==0;}
		bool enQueue(const People & person);
		int getItems() const{return items;}
		int inFrontOf(int orderNum) const; 
		
		bool outQueue(People &person,bool ElUp,bool ElDown);
		bool giveUp(int orderNum);
		bool noUp(int inFloor);
		bool noDown(int inFloor);
};
#endif
