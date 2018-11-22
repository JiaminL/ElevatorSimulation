#include "EventList.h"

EventList::EventList(){
	comeNum=succeedNum=allUseTime=allSuccTime=0;
	head=new Node;
	head->next=NULL;
}

EventList::~EventList(){
	Node *p=head;
	Node *temp;
	while(p){
		temp=p;
		p=p->next;
		delete temp;
	}
	cout<<" free el ";
}

void EventList::initSystem(){
	//get inputs
	ElSize=9;
	averGvUp=1010;
	averCome=500;
	ES.setSize(ElSize);//Set load of the elevator.
	elevator.set();//initialize
	addEvent(0,PE_COME,NeverUse);
}

bool EventList::addEvent(int when,int NType,const People &person){
	if(aboutEl(NType)||aboutPe(NType)){
		Node *add=new Node;
		add->event.NType=NType;
		add->event.OccurTime=when;
		if(aboutPe(NType)) add->event.person=person;
		Node* pre;
		findPreNode(when,pre);
		add->next=pre->next;
		pre->next=add; 
		return true; 
	}
	return false;
} 

bool EventList::deleFirst(){
	if(isEmpty()) return false;
	Node *p=head->next;
	head->next=p->next;
	delete p;
	return true;
}

void EventList::findPreNode(int when,Node* &pre){
	pre=head;
	Node *p=pre->next;
	while(p){
		if(p->event.OccurTime>when){
			break;
		}
		p=p->next;
		pre=pre->next;
	}
}

bool EventList::haveBeCalled(int when) const{
	Node *p=head->next;
	int last=when+1+START_TIME;
	while(p){
		if(p->event.OccurTime>last) break;
		if(p->event.NType==EL_OPEN||p->event.NType==EL_READY_UP||p->event.NType==EL_READY_DOWN)
			return true;
		p=p->next;
	}
	return false;
} 

bool EventList::canFindIdle(int &when) const{
	Node *p=head->next;
	int last=when+1+DOWN_DEC_TIME;
	while(p){
		if(p->event.OccurTime>last) break;
		if(p->event.NType==EL_START_IDLE)
			return true;
		p=p->next;
	}
	return false;
}

void EventList::outputEvent(const Event &event) {
//															cout<<endl<<"time:";
	cout<<event.OccurTime<<" ";
//															cout<<"type:";
	cout<<event.NType<<" ";
//	                                                        printType(event.NType);
//															cout<<"//floor state(up:0,down:1,idle:2) door(Closing:0,Closed:1,Opening:2,Opened:3) \nf s d callCar__ callUp___ callDown_"<<endl;
	elevator.printOut();
//															cout<<endl<<"n a g i o //n:orderNum a:arriveTime g:giveupTime i:inFloor o:outFloor"<<endl;
	if(aboutPe(event.NType)) event.person.printOut();
	else cout<<"0 0 0 0 0 ";
	cout<<endl;
}

void EventList::printType(int NType) const{
	switch(NType){
		case PE_COME: cout<<"people came \n";break;
		case PE_GVUP: cout<<"people gave up \n";break;
		case PE_IN:   cout<<"people entered elevator \n";break;
		case PE_OUT:  cout<<"people left elevator \n";break;
		case EL_OPEN: cout<<"elevator opened door \n";break;
		case EL_CLOSE:cout<<"elevator closed door \n";break;
		case EL_READY_UP:cout<<"elevator ready up \n";break;
		case EL_READY_DOWN:cout<<"elevator ready down \n";break;
		case EL_UP:   cout<<"elevator up \n";break;
		case EL_DOWN: cout<<"elevator down \n";break;
		case EL_STOP_UP:   cout<<"elevator stop up \n";break;
		case EL_STOP_DOWN: cout<<"elevator stop down \n";break;
		default :     cout<<"elevator start idle \n";break;
	}
}

void EventList::printResult() const{
	int gvUpNum=comeNum-succeedNum;
	cout<<" ComeNum "<<comeNum<<" succeedNum "<<succeedNum<<" giveupNum "<<gvUpNum<<endl;
	cout<<" AverUseTime "<<allUseTime/comeNum<<" SuccessUseTime "<<allSuccTime/succeedNum<<endl;
	cout<<"eof"<<endl; 
}

void EventList::cancelGvUp(int orderNum){
	Node *p,*pre;
	p=head->next;
	pre=head;
	while(p){
		if(p->event.NType==PE_GVUP&&p->event.person.getOrderNum()==orderNum){
			pre->next=p->next;
			delete p;
			break;
		}
		p=p->next;
		pre=pre->next;
	}
}

void EventList::cancelReady(){
	Node *p,*pre;
	p=head->next;
	pre=head;
	while(p){
		if(p->event.NType==EL_READY_UP||p->event.NType==EL_READY_DOWN||p->event.NType==EL_START_IDLE){
			pre->next=p->next;
			delete p;
			break;
		}
		p=p->next;
		pre=pre->next;
	}
} 

void EventList::cancelGoBase(){
	Node *p,*pre;
	p=head->next;
	pre=head;
	while(p){
		if(p->event.NType==EL_BASE){
			pre->next=p->next;
			delete p;
			break;
		}
		p=p->next;
		pre=pre->next;
	}
} 

bool EventList::dealEvent(int when){
	Node *item=head->next; 
	if(!item) return false;
	if(item->event.OccurTime!=when) return false;
	switch(item->event.NType){
		case PE_COME:       {dealPeCome(item->event);break;}
		case PE_GVUP:       {dealPeGvUp(item->event);break;}
		case PE_IN:         {dealPeIn(item->event);break;}
		case PE_OUT:        {dealPeOut(item->event);break;}
		case EL_BASE:       {dealElBase(item->event);break;}
		case EL_OPEN:  	    {dealElOpen(item->event);break;}
		case EL_CLOSE:      {dealElClose(item->event);break;}
		case EL_READY_UP:   {dealElUReady(item->event);break;}
		case EL_READY_DOWN: {dealElDReady(item->event);break;}
		case EL_UP:         {dealElUp(item->event);break;}
		case EL_DOWN:       {dealElDown(item->event);break;}
		case EL_STOP_UP:    {dealElUStop(item->event);break;}
		case EL_STOP_DOWN:  {dealElDStop(item->event);break;}
		case EL_START_IDLE: {dealElSttId(item->event);break;}
		default:           return false;
	}
	return true;
}

void EventList::dealPeCome(Event &event){
	int when=event.OccurTime;
	//deal with the event
	comeNum++;
	event.person.arrive(when,comeNum,averGvUp,averCome);
	int inFloor=event.person.getInFloor();
	int outFloor=event.person.getOutFloor();
	elevator.pressButtomCome(inFloor,outFloor);
	ControPress(when,inFloor,outFloor); 
	Q[inFloor].enQueue(event.person);
	//preset
	addEvent(event.person.getGvUpTime(),PE_GVUP,event.person);
	addEvent(event.person.getNextInTime(),PE_COME,NeverUse);
	//print
	outputEvent(event);
	deleFirst();
}

void EventList::dealPeGvUp(Event &event){
	int when=event.OccurTime;
	int inFloor=event.person.getInFloor();
	int orderNum=event.person.getOrderNum();
	if(elevator.atFloor(inFloor)&&(elevator.isOpening()||elevator.hasOpened()))//wait
		addEvent(when+PEOPLE_MOVE_TIME,PE_GVUP,event.person);
	else{//give up
		int arriveTime=event.person.getArriveTime();
		Q[inFloor].giveUp(orderNum);
		allUseTime+=when-arriveTime;
		//print
		outputEvent(event);
	}
	deleFirst();
}

void EventList::dealPeIn(Event &event){
	int floor=elevator.getFloor();
	if(Q[floor].isEmpty()||ES.isFull()){//nobody enters
		elevator.changeState();
		if(Q[floor].noDown(floor)) elevator.reCallDown();
		if(Q[floor].noUp(floor)) elevator.reCallUp();
		elevator.InOrOut=false;
	}
	else{//a person enters the elevator
		elevator.InOrOut=true;
		People person; 
		if(Q[floor].outQueue(person,elevator.isUp(),elevator.isDown())){
			ES.enStack(person);
			cancelGvUp(person.getOrderNum());
			elevator.pressButtomOut(person.getOutFloor());
			event.person=person;
			//print
			outputEvent(event);
			//preset
			addEvent(event.OccurTime+PEOPLE_MOVE_TIME,PE_IN,NeverUse);
		} 
		else {
			if(Q[floor].noDown(floor)) elevator.reCallDown();
			if(Q[floor].noUp(floor)) elevator.reCallUp();
			elevator.InOrOut=false;
		}
	}
	deleFirst();
}

void EventList::dealPeOut(Event &event){
	elevator.setOpened();
	int floor=elevator.getFloor();
	int when=event.OccurTime;
	People person; 
	if(ES.findOut(floor,person)){//out
		elevator.InOrOut=true;
		event.person=person;
		ES.outStack(person.getOrderNum());
		succeedNum++;
		int outTime=when+PEOPLE_MOVE_TIME;
		int useTime=outTime-person.getArriveTime();
		allUseTime+=useTime;
		allSuccTime+=useTime;
		//print
		outputEvent(event);
		//preset
		addEvent(outTime,PE_OUT,NeverUse);
	}
	else{//nobody wants to go out,so let people enter the elevator
		elevator.changeState();
		addEvent(when,PE_IN,NeverUse);
	}
	deleFirst();
	
}

void EventList::dealElBase(Event &event){
	elevator.setState(1);
	if(elevator.isUp()){
		addEvent(event.OccurTime,EL_READY_UP,NeverUse);
//		cout<<"                                                                          ready up"<<event.OccurTime<<"base"<<endl;
	}
	else if(elevator.isDown()){
		addEvent(event.OccurTime,EL_READY_DOWN,NeverUse);
//		cout<<"                                                                          ready down"<<event.OccurTime<<"base"<<endl;
	}
	deleFirst();
} 

void EventList::dealElOpen(Event &event){
	//open the door
	cancelGoBase();
	elevator.Calling=true;
	int when=event.OccurTime;
	if(elevator.beCalled(elevator.getFloor())){
		elevator.setOpening(); 
		//preset
		addEvent(when+DOOR_TIME,PE_OUT,NeverUse);//let people go in or go out
		addEvent(when+SET_CLOSE_TIME,EL_CLOSE,NeverUse);//close door
		outputEvent(event);
	} 
	deleFirst();	
}

void EventList::dealElClose(Event &event){
	int when=event.OccurTime;
	if(!elevator.InOrOut){//close the door
		elevator.setClosing();
		elevator.changeState();
		//preset
		if(elevator.isUp()){
			addEvent(when+DOOR_TIME,EL_READY_UP,NeverUse);
//			cout<<"                                                                          ready up"<<when+DOOR_TIME<<"close"<<endl;
		}
		else if(elevator.isDown()) {  
			addEvent(when+DOOR_TIME,EL_READY_DOWN,NeverUse); 
//			cout<<"                                                                          ready down"<<when+DOOR_TIME<<"close"<<endl;
		} 
		else{
			addEvent(when+DOOR_TIME,EL_START_IDLE,NeverUse); 
//			cout<<"                                                                          idle"<<when+DOOR_TIME<<"close"<<endl;
		}
		outputEvent(event);
	}
	//close leter
	else{
		addEvent(when+TEST_TIME,EL_CLOSE,NeverUse);
	} 
	deleFirst();
}

void EventList::dealElUReady(Event &event){
	cancelGoBase();
	elevator.setClosed();
	elevator.reCallCar();
	elevator.Calling=true;
	addEvent(event.OccurTime+ACC_TIME,EL_UP,NeverUse);
	outputEvent(event);
	deleFirst();
}

void EventList::dealElDReady(Event &event){
	cancelGoBase();
	elevator.setClosed();
	elevator.reCallCar();
	elevator.Calling=true;
	addEvent(event.OccurTime+ACC_TIME,EL_DOWN,NeverUse);
	outputEvent(event);
	deleFirst();
}

void EventList::dealElUp(Event &event){
	//up
	elevator.upFloor();
	elevator.setUp();
	//print
	outputEvent(event);
	int time=event.OccurTime+UP_FLOOR_TIME;
	if(elevator.upShouldSlow()){
		elevator.changeState();
		addEvent(time,EL_STOP_UP,NeverUse);
//		cout<<"                                                                          stop up"<<time<<"up"<<endl;
	}	
	else{
		addEvent(time,EL_UP,NeverUse);
//		cout<<"                                                                          up"<<time<<"up"<<endl;
	}
		
	deleFirst();
}

void EventList::dealElDown(Event &event){
	elevator.downFloor();
	elevator.setDown();
	//print
	outputEvent(event);
	//preset
	int time=event.OccurTime+DOWN_FLOOR_TIME;
	if(elevator.downShouldSlow()){
		elevator.changeState();
		addEvent(time,EL_STOP_DOWN,NeverUse);
//		cout<<"                                                                          stop down"<<time<<"down"<<endl;
	}
	else{
		addEvent(time,EL_DOWN,NeverUse);
//		cout<<"                                                                          down"<<time<<"down"<<endl;
	}
	deleFirst();
}

void EventList::dealElUStop(Event &event){
	int time=event.OccurTime+UP_DED_TIME;
	int floor=elevator.getFloor();
	elevator.changeState();
	if(elevator.shouldOpen(floor)){
		addEvent(time,EL_OPEN,NeverUse);
//		cout<<"                                                                          open"<<time<<"up stop"<<endl;
	}
	else if(elevator.isIdle()) {
		addEvent(time,EL_START_IDLE,NeverUse);
//		cout<<"                                                                          idle"<<time<<"up stop"<<endl;
	}
		
	else if(elevator.isUp()){
		addEvent(time,EL_READY_UP,NeverUse);
//		cout<<"                                                                          ready up"<<time<<"up stop"<<endl;
	}
	else{
		addEvent(time,EL_READY_DOWN,NeverUse);
//		cout<<"                                                                          ready down"<<time<<"up stop"<<endl;
	} 
	outputEvent(event);
	deleFirst();
}

void EventList::dealElDStop(Event &event){
	int time=event.OccurTime+DOWN_DEC_TIME;
	int floor=elevator.getFloor();
	elevator.changeState();
	if(elevator.shouldOpen(floor)){
		addEvent(time,EL_OPEN,NeverUse);
//		cout<<"                                                                          open"<<time<<"down stop"<<endl;
	}
	
	else if(elevator.isIdle()){
		addEvent(time,EL_START_IDLE,NeverUse);
//		cout<<"                                                                          idle"<<time<<"down stop"<<endl;
	}
		
	else if(elevator.isUp()) {
		addEvent(time,EL_READY_UP,NeverUse);
//		cout<<"                                                                          ready up"<<time<<"down stop"<<endl;
	}
	else{
		addEvent(time,EL_READY_DOWN,NeverUse);
//		cout<<"                                                                          ready down"<<time<<"down stop"<<endl;
	} 
	outputEvent(event);
	deleFirst();
}

void EventList::dealElSttId(Event &event){
	elevator.setClosed();
	elevator.reCallCar();
	if(elevator.shouldIdle()){
		elevator.Calling=false;
		if(elevator.getFloor()==1)
			elevator.AtBase=true;
		else
			addEvent(event.OccurTime+IDLE_TIME,EL_BASE,NeverUse);
		outputEvent(event);
	}
	else{
		int floor;
		if(elevator.getAimFloor(floor)){
			if(floor>elevator.getFloor()){
				addEvent(event.OccurTime,EL_READY_UP,NeverUse);
//				cout<<"                                                                          ready up"<<event.OccurTime<<"idle"<<endl;
			}
			
			else{
				addEvent(event.OccurTime,EL_READY_DOWN,NeverUse);
//				cout<<"                                                                          ready down"<<event.OccurTime<<"idle"<<endl;
			}
				
		}
		else{
			addEvent(event.OccurTime,EL_OPEN,NeverUse);
			//cout<<"                                                                          open"<<event.OccurTime<<"idle"<<endl;
		}
			
	}
	deleFirst();
}

void EventList::ControPress(int when,int inFloor,int outFloor){
	int floor=elevator.getFloor();
	if(floor==inFloor&&elevator.isClosing()){
			//电梯正在当前楼层且正在关门 
			if((!elevator.isDown()&&inFloor<outFloor)||(!elevator.isUp()&&inFloor>outFloor)){
				addEvent(when,EL_OPEN,NeverUse);
//				cout<<"                                                                          open"<<when<<"press"<<endl;
				cancelReady();
			}
	}
	else if(elevator.isIdle()&&elevator.hasClosed()){
		if(elevator.AtBase)
			when+=START_TIME;
		if (elevator.Calling==false){
			//如果电梯在等候命令 
			cancelGoBase();
			if(floor==inFloor){
				elevator.setState(outFloor);
				addEvent(when,EL_OPEN,NeverUse);
//				cout<<"                                                                          open"<<when<<"press"<<endl;
			}
			else if(floor>inFloor){
				elevator.setState(inFloor);
				addEvent(when,EL_READY_DOWN,NeverUse);
//				cout<<"                                                                          ready down"<<when<<"press"<<endl;
			}
			else{
				elevator.setState(inFloor);
				addEvent(when,EL_READY_UP,NeverUse);
//				cout<<"                                                                          ready up"<<when<<"press"<<endl;
			}
		}
	}
	if(elevator.isIdle())
		if(floor==inFloor)elevator.setState(outFloor);
		else elevator.setState(inFloor);
	elevator.Calling=true;
}
