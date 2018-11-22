//queue.cpp
#include "Queue.h"

Queue::Queue(){
	front=new Node;
	front->next=NULL;
	rear=front ; 
	items=0;
}

Queue::~Queue()
{
	Node *p=front;
	Node *temp;
	while(p){
		temp=p;
		p=p->next;
		delete temp;
	}
	cout<<" free q ";
}

int Queue::inFrontOf(int orderNum) const{
	Node *p=front->next;
	int n;
	while(p){
		if(p->person.getOrderNum()==orderNum) break;
		n++;
		p=p->next;
	}
	return n;
}

bool Queue::enQueue(const People & person){
	Node *add=new Node;
	add->person=person;
	add->next=NULL;
	rear->next=add;
	rear=add;
	items++;
	return true;
}

bool Queue::outQueue(People &person,bool ElUp,bool ElDown){
	Node *p=front->next;
	Node *pre=front;
	while(p){
		bool wantUp=p->person.wantUp();
		if((wantUp&&ElUp)||(!wantUp&&ElDown)){
			pre->next=p->next;
			person=p->person;
			delete p;
			items--;
			if (p==rear) rear=pre;
			return true;
		}
		p=p->next;
		pre=pre->next;
	}
	return false;
}

bool Queue::giveUp(int orderNum){
	Node *p=front->next;
	Node *pre=front;
	while(p){
		if(p->person.getOrderNum()==orderNum){
			pre->next=p->next;
			if(p==rear) rear=pre;
			delete p;
			items--;
			return true;
		}
		p=p->next;
		pre=pre->next;
	}
	return false;//can't find the person
}

bool Queue::noUp(int inFloor){
	Node *p=front->next;
	while(p){
		if(p->person.wantUp())
			return false;
		p=p->next;
	}
	return true;
}


bool Queue::noDown(int inFloor){
	Node *p=front->next;
	while(p){
		if(p->person.wantDown())
			return false;
		p=p->next;
	}
	return true;
}

