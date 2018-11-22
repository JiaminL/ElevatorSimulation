//elestack.h
#ifndef ELESTACK_H
#define ELESTACK_H
#include "People.h"
#define MAX_STACK_SIZE 15

class EleStack
{
	private:
		struct Node{
			People person;
			struct Node *next; 
		}; 
		Node *head;
		int eSize;
		int items;
	public:
		EleStack();
		~EleStack();
		bool setSize(int size);
		
		bool isEmpty() const;
		bool isFull() const;
		int outNum(int floor) const;
		
		bool enStack(const People & person);
		bool outStack(int orderNum);
		bool findOut(int floor,People &person);
		int getSpace()const {return eSize-items;}
};

#endif
