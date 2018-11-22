//elestack.cpp
#include "EleStack.h"

EleStack::EleStack():eSize(8){
	head=new Node;
	head->next=NULL;
	items=0;
}

EleStack::~EleStack(){
	Node *p=head;
	Node *temp;
	while(p){
		temp=p;
		p=p->next;
		delete temp;
	}
	cout<<" free es ";
}

bool EleStack::setSize(int size){
	if(size>MAX_STACK_SIZE) return false;
	eSize=size;
	return true;
}

bool EleStack::isEmpty() const{
	return items==0;
}

bool EleStack::isFull() const{
	return items>=eSize;
}

int EleStack::outNum(int floor) const{
	Node *p=head->next;
	int n=0;
	while(p){
		if(p->person.getOutFloor()==floor) n++;
		p=p->next;
	}
	return n;
}

bool EleStack::enStack(const People & person){
	if(isFull()) return false;
	Node *add=new Node;
	add->person=person;
	add->next=head->next;
	head->next=add;
	items++;
	return true;
}

bool EleStack::outStack(int orderNum){
	Node *p=head->next;
	Node *pre=head;
	while(p){
		if(p->person.getOrderNum()==orderNum){
			pre->next=p->next;
			delete p;
			items--;
			return true;
		}
		p=p->next;
		pre=pre->next;
	}
	return false;
}

bool EleStack::findOut(int floor,People &person){
	if(isEmpty())return false;
	Node *p=head->next;
	while(p){
		if(p->person.getOutFloor()==floor){
			person=p->person;
			return true;
		}
		p=p->next;
	}
	return false;
}
