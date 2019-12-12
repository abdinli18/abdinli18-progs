/*
PLEASE, DO NOT CHANGE void display(bool verbose, bool testing), int getUsableDay() and int getUsableTime() FUNCTIONS.
YOU HAVE TO WRITE THE REQUIRED  FUNCTIONS THAT IS MENTIONED ABOVE. YOU CAN ADD NEW FUNCTIONS IF YOU NEED.
*/
/* @Author
Student Name: Elvin Abdinli
Student ID: 150180904
Date: 15/11/2019*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

#include "task_management_tool.h"

using namespace std; 


void WorkPlan::display(bool verbose,bool testing)
{
	string inone="***";
	if (head!=NULL)
	{
		Task *pivot =new Task;
		Task *compeer =new Task;
			
		pivot=head;
		do
		{
			if(testing)
				inone+=" ";
			else
				cout << pivot->day <<". DAY"<< endl;
			compeer=pivot;
			while(compeer!=NULL)
			{
				string PREV= compeer->previous!=NULL?compeer->previous->name:"NULL";
				string NEXT=compeer->next!=NULL?compeer->next->name:"NULL";
				string CONT=compeer->counterpart!=NULL?compeer->counterpart->name:"NULL";
				if (testing)
					inone+=compeer->name;
				else
					if(verbose)
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< PREV<<"\t<- "<< compeer->name <<"("<< compeer->priority <<")->\t"<<NEXT <<"\t |_"<<CONT<<endl;
					else
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< compeer->name <<"("<< compeer->priority <<")"<<endl;				
				compeer=compeer->counterpart;
			}
			pivot=pivot->next;
		}while(pivot!=head);
		if(testing)
		{
			cout<<inone<<endl;
			cout<<"(checking cycled list:";
			if (checkCycledList())
				cout<<" PASS)"<<endl;
			else
				cout<<" FAIL)"<<endl;
		}
	}
	else
		cout<<"There is no task yet!"<<endl;
}

int WorkPlan::getUsableDay()
{
	return usable_day;
}

int WorkPlan::getUsableTime()
{
	return usable_time;
}


void WorkPlan::create()
{		
	//THIS FUNCTION WILL BE CODED BY YOU
	head = NULL;
	
}

void WorkPlan::close()
{
	//THIS FUNCTION WILL BE CODED BY YOU
	Task *traverse = head;
	Task *tail = head;
	if(head==NULL){                                   //if user tries to end program without adding appointments
		return;
	}else{
		do{
			tail = traverse;
			while(tail->counterpart != NULL){         //while appointments on the same day are not deleted, we can not delete the first appointment of that day
				traverse = tail;
				traverse = traverse->counterpart;
				tail->counterpart = traverse->counterpart;
				delete [] traverse->name;
				delete traverse;
				
			}
			traverse = tail->next;                    //after deleting all appointments of a day except first one, we can delete first appointment
			delete [] tail->name;
			delete tail;
			
		}while(traverse!=head);
		head=NULL;
		return;
	}
	
}

void WorkPlan::add(Task *task)
{
	//THIS FUNCTION WILL BE CODED BY YOU
	Task *traverse = head; 
	Task *tail= head;
	Task *control = head;
	Task *newnode = new Task;                           //allocating memory
	*newnode = *task;
	newnode->next = NULL;
	newnode->previous = NULL;
	newnode->counterpart = NULL;
	newnode->name = new char[strlen(task->name)+1];      //allocating memory for char pointer
	strcpy(newnode->name, task->name);                   //copying name of task to newnode's name
	
	if(head==NULL){                                      //controls if we adding first node or not
		head = newnode;
		head->next = head;
		head->previous = head;
		head->counterpart = NULL;
		return;
	}
	if(newnode->day < head->day && head->next != head){  //controls if we are adding node to the head and if there is more appointment day than 1
		(head->previous)->next = newnode;
		newnode->next = head;
		newnode->previous = head->previous;
		head->previous = newnode;
		head = newnode;
		head->counterpart = NULL;
		return;
	}
	if(newnode->day < head->day && head->next == head){ //controls if we are adding to the head and if there is only 1 appointment day
		newnode->next = head;
		head->previous = newnode;
		head->next = newnode;
		newnode->previous = head;
		head = newnode;
		return;
	}
	control = getTask(newnode->day,newnode->time);            //controls if there is appointment at the same day and hour, if not it returns NULL, else it returns the address of the node in the list which has the same appointment day and hour
	if(control == NULL){                                      //if there is not it enters here
		traverse = head;
		while(traverse->day < newnode->day && traverse->next!=head){  //searching for proper day
			traverse = traverse->next;
		}
		if(traverse->day != newnode->day && traverse == head->previous){ //we are adding the appointment which has biggest day 
			if(traverse->day < newnode->day){                            //if it is bigger than the biggest day of list
				traverse->next = newnode;
				newnode->previous = traverse;
				newnode->next = head;
				head->previous = newnode;
				return;
			}else if(traverse->day > newnode->day){                      // if it is smaller than the biggest day number of list
				(traverse->previous)->next = newnode;
				newnode->next = traverse;
				newnode->previous = traverse->previous;
				traverse->previous = newnode;
				return;
			}	
		}
		if(traverse->day != newnode->day){                              // if it enters code will add not existing day to the middle of the list 
			if(traverse->day > newnode->day){
				(traverse->previous)->next = newnode;
				newnode->previous = traverse->previous;
				newnode->next = traverse;
				traverse->previous = newnode;
				return;
			}
		}
		if(traverse->day==newnode->day){                                //if we are adding to the aready existing day
			if(traverse->time < newnode->time){
				while(traverse->time < newnode->time && traverse->counterpart!=NULL){ //if its time is bigger than the first appointment of that day 
					tail = traverse;                                                  //searching for proper place to add
					traverse = traverse->counterpart;
				}
				if(tail!=head){                                         //if we are not adding to the head node
					if(traverse != head && traverse->time > newnode->time){// it will enter here if it didn't enter to the while loop
						tail->counterpart = newnode;
						newnode->counterpart = traverse;
						return;
					}else{                                                 // if it entered to the while loop it means there is more than 1 appointments in the same day
						traverse->counterpart = newnode;
						newnode->counterpart = NULL;
						return;
					}
				}else{                                          
					if(traverse->time < newnode->time){                     // if newnode will be added to the end of that day
						traverse->counterpart = newnode;
						newnode->counterpart = NULL;
						return;
					}else{
						tail->counterpart = newnode;                       // if newnode will be added between 2 already existing time 
						newnode->counterpart = traverse;
						return;
						
					}
				}
			}else{                                                         // if code will enter here means we are making newnode the first appointment of that day
				if(head->next!=head){                                      // if there is not only one appointment day
					tail = traverse;
					traverse = newnode;
					traverse->counterpart = tail;
					(tail->previous)->next = traverse;
					traverse->previous = tail->previous;
					tail->previous = NULL;
					traverse->next = tail->next;
					(tail->next)->previous = traverse;
					tail->next = NULL;
					if(traverse->day == head->day){                        // if we are adding to the day that are same with head's day we must move head
						head = traverse;
					}
					return;
				}else{                                                     // if there is only 1 appointment day
					tail = traverse;
					traverse = newnode;
					traverse->counterpart = tail;
					tail->next = NULL;
					tail->previous = NULL;
					head = traverse;
					head->next = head;
					head->previous = head;
					return;
				}
			}	
		}
	}else{                                                                 // if there is an appointment which has same day and time with newnode's  
		checkAvailableNextTimesFor(control);                               // checking avaiable time for that day and time to delay
		
		if(newnode->priority > control->priority){                         // if newnode's priority is bigger than control's then we must change their palace in list and move control to it's delayed time
			if(control->day != head->day){
				newnode->next = control->next;
				newnode->previous = control->previous;
				(control->next)->previous = newnode;
				(control->previous)-> next = newnode;
				control->next = NULL;
				control->previous = NULL;
				if(control->counterpart !=NULL){                               // if control is not only appointment in that day  
					newnode->counterpart = control->counterpart;
				}
				control->day = usable_day;
				control->time = usable_time;
				add(control);                                                 // after assigning new usable day and time add that node to list again
				return;
			}else{                                                            //if control day is same with head's day there is probability of moving head  
				if(control->next == head){                                    //if there is only 1 appointment day and control is same with head 
					newnode->next = newnode;
					newnode->previous = newnode;
					head = newnode;
				}else{                                                         //if control's day is same with head's we must search for proper time
					Task *tail = head;
					while(tail->counterpart != control && tail->counterpart!=NULL){                       //searching for proper time
						tail = tail->counterpart;
					}
					//tail->counterpart = newnode;                               //not to lose other datas on that day we assign tail's counterpart to newnode's
				}
				if(control->next != NULL && control == head){
					(control->previous)->next = newnode;
					(control->next)->previous = newnode;
					newnode->next = control->next;
					newnode->previous = control->previous;
					head = newnode;
					if(control->counterpart != NULL){
						newnode->counterpart = control->counterpart;
					}else{
						newnode->counterpart=NULL;
					}
					//newnode->counterpart = control->counterpart;                // other data's is assigned to newnode's counterpart  
				}else{
					newnode->counterpart = control->counterpart;
				}
	
				control->next = NULL;
				control->previous = NULL;
				control->day = usable_day;
				control->time = usable_time;
				add(control);
				return;
			}
		}else{                                                            // if newnodes priority is smaller than control's then don't change control's place just assign delayable time and day to newnode and add again
			newnode->day = usable_day;
			newnode->time = usable_time;
			add(newnode);
			return;
		}
		
	}
	
} 

Task * WorkPlan::getTask(int day, int time)           //this function controlling newnode's day and time with day and times in the list if there is any has same day and time returns its address if not returns NULL
{
	Task* traverse = head;
	
	while(traverse->day < day && traverse->next!=head){   //searching for proper day
		traverse = traverse->next;
	}
	if(traverse->day == day){                            //if there is a day same with newnode's
		while(traverse->time < time && traverse->counterpart!=NULL){  //searching for proper time
			traverse = traverse->counterpart;
		}
		if(traverse->time != time){                       // if there is not time same with newnode's 
			return NULL;
		}else{                                            // else return its address
			return traverse;
		}
	}else{
		return NULL;                                     // if there is not a day same with newnode's return NULL
	}
	//THIS FUNCTION WILL BE CODED BY YOU
}


void WorkPlan::checkAvailableNextTimesFor(Task *delayed)	
{
	//THIS FUNCTION WILL BE CODED BY YOU
	Task* tail = head;
	Task* traverse = head;
	while(traverse->day < delayed->day){         //search for day
		traverse = traverse->next;
		if(traverse == head){                    
			break;
		}
	}
	tail = traverse;
	if(traverse->day == delayed->day){                // if there is a day
		while(traverse->time != delayed->time){       // then search for time
			traverse = traverse->counterpart;
		}
	}
	if(traverse->counterpart != NULL){                //if counter part is not NULL means there can be an avaiable time on the same day
		if(traverse->time > 8 && traverse->day > delayed->day){  //if the first appointment of day is later than 8 enters here and makes usable time 8 and usable day traverse->day 
			usable_time = 8;
			usable_day = traverse->day;
			return;
		}
		
		while(traverse->counterpart !=NULL && !(traverse->counterpart->time > traverse->time+1)){ //this line controlles if there is time between traverse and its counterpart if not move traverse to traverse->counterpart 
			traverse = traverse->counterpart;
		}
		if(traverse->counterpart != NULL){          // if traverse counterpart is not NULL means we find an avaiable time in the same day
			usable_day = traverse->day;
			usable_time = (traverse->time)+1;
			return;
		}else{
			if(tail->next->time == 8){              // but before we must control if there is appointment on next day at time of 8
				tail = tail->next;                  //if there is we will search in that day
				traverse = tail;
				checkAvailableNextTimesFor(traverse);
				return;
			}else{
				usable_day = tail->next->day;  // if there is not appointment in next day at time of 8 then return it as usable day and time
				usable_time = 8;
			}
		}
	}else{                                     // if code enters here means there is only 1 appointment in that day 
		if(tail->next->time == 8){             // then search for next day's first appointment if it is time of 8 start searching from here
			tail = tail->next;
			traverse = tail;
			checkAvailableNextTimesFor(traverse);
			return;
		}else{                                 // else make it as usable day and time
			usable_day = tail->next->day;
			usable_time = 8;
		}
	}
}

void WorkPlan::delayAllTasksOfDay(int day)    //delaying all task's of a day to the next avaiable time
{
	//THIS FUNCTION WILL BE CODED BY YOU
	Task *tail = head;
	Task *traverse = head;
	while(traverse->day != day){              //finding proper day
		traverse = traverse->next;
	}
	if(traverse==head){                      // we must be very carefull because we can delay head's day so if we don't move head we will lose it, so move head to its next
		head=head->next;
	}
	(traverse->previous)->next = traverse->next;
	(traverse->next)->previous = traverse->previous;
	traverse->next = NULL;
	traverse->previous = NULL;
	tail = traverse;
	while(traverse != NULL){
		
		checkAvailableNextTimesFor(tail);  // here we chech avaiable times for it
		traverse = traverse->counterpart;
		tail->day = getUsableDay();
		tail->time = getUsableTime();
		tail->counterpart = NULL;
		add(tail);             //and here we add it
		tail = traverse;
	}
	
	
	
}

void WorkPlan::remove(Task *target)
{
	//THIS FUNCTION WILL BE CODED BY YOU
	Task* traverse = head;
	Task* tail = head;
	
	while(traverse->day < target->day){  //searching proper day
		tail = traverse;
		traverse = traverse->next;
	}
	if(traverse->time != target->time){     //if it is not the first appointments of the day
		while(traverse->time < target->time && traverse->counterpart != NULL){    // searching proper time
			tail = traverse;
			traverse = traverse->counterpart;
		}
		tail->counterpart = traverse->counterpart;
		traverse->name = NULL;
		delete traverse;
		return;
	}else{                              // if it is first appointment of day
		if(traverse != head){           // if it is not the same day with head's day
			if(traverse->counterpart != NULL){   //if it only appointment in that day
				tail->next = traverse->counterpart;
				(traverse->counterpart)->next = traverse->next;
				(traverse->counterpart)->previous = tail;
				(traverse->next)->previous = traverse->counterpart;
				traverse->name = NULL;
				delete traverse;
				return;
			}else{                               // if there is more than 1 appointment of that day
				tail->next = traverse->next;
				(traverse->next)->previous = tail;
				traverse->name = NULL;
				delete traverse;
				return;
			}
		}else{                                  // if we are trying to remove head
			if(traverse->counterpart == NULL){  // first control if there is only 1 appointment in that day or not
				(traverse->next)->previous = traverse->previous;
				(traverse->previous)->next = traverse->next;
				head = head->next;                // if code enters here means there is only 1 appointment in that day so we must move head to next day's first appointment
				traverse->name = NULL;
				delete traverse;
			}else{                                // there is more than 1 appointment on that day
				(traverse->counterpart)->next = traverse->next;
				(traverse->counterpart)->previous = traverse->previous;
				(traverse->previous)->next = traverse->counterpart;
				(traverse->next)->previous = traverse->counterpart;
				head = head->counterpart;         // so we must move head to same day's counterpart appointment
				traverse->name=NULL;
				delete traverse;
			}
		}	
	}
}

bool WorkPlan::checkCycledList()
{				
	Task *pivot=new Task();
	pivot=head;
	int patient=100;
	bool r=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->previous;
		if(pivot==head)
		{
			r=true;
			break;
		}
	}
	cout<<"("<<100-patient<<")";
	patient=100;
	bool l=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->next;
		if(pivot==head)
		{
			l=true;
			break;
		}
	}
	return r&l;
}
