/* @Author
Student Name: Elvin Abdinli
Student ID: 150180904
Date: 10/21/2019*/



#include <iostream>                    
#include <stdio.h>                      //printf and fscanf
#include <fstream>                      // file operatins
                                        

#include "stock.h"                      // including structure List which is containing function declerations and headptr

using namespace std;

void List::create(){
	headptr = NULL;                     //create empty list
}

Shoe_node* List::createnode(int value){ 
	Shoe_node * nn = new Shoe_node;     // allocating memory for newnode
	nn->size = value;                   // assigning size value
	nn->quant = 1;                      // assigning initial quantity
	nn->next = NULL;                    // next is pointer showing next node's address
	return nn;                          // returning the address of newnode
}

void List::read_fromfile(char*str)
{

	
	bool found = false;
	 

	char* filename = str;                    //filename is char pointer which points to address of input.txt file   

	FILE* fptr;
	if((fptr = fopen(filename,"r"))==NULL){  // controlling and opening file if it exits
		printf("File couldn't be opened");   // if it is not exist this output will be printed
		return;
	}
	int num;                                   // num is used to get numbers from input.txt one by one 
	while(!feof(fptr)){                        // it means while it is not the end of file do operations in while
		Shoe_node *newnode;                    // new node with Shoe_node* type
		fscanf(fptr,"%d ",&num);               // getting num one by one from input.txt
		if(num==0){							   // if num is 0 we must print all numbers in linked list
			print();    					   // print all numbers using print function
		}else{
			found = search(num);               // if node is exist in our linked list it will return false if it is already exist return true so that we can recognize whether to add a new node or to do add and decrease process depending on num's sign 
			if(num>0){                         // if num is bigger than zero 
				if(found == false){            // if it is not exist go to createnode function
					newnode = createnode(num); // sending num to createnode and getting address of newnode
					insert(newnode);           // inserting node to its position due to its int size value in ascending order in linked list
				}else{
					add_decrease(num);         // if that node is exist its quantity must be either increased by 1 because num is already controlled it is positive
				}	
			}else{
				add_decrease(num);             // if that node is exist and if num is negative then decrease that nodes quantity by 1, if num is zero then it will call print function insite the add_decrease function 
			}
		}
	}
	clear();                                   // clearing whole linked list from memory after printing it to the screen

	fclose(fptr);                              // close the file input.txt at the end
}

void List::insert(Shoe_node *toadd){
	
	Shoe_node *traverse, *tail;                 // traverse and tail is used for moving through the linked list and finding proper position for node
	
	traverse = headptr;                         // traverse now has address of headptr we use that method not to lose address of headptr in moving position process
	tail = headptr;                             // same as traverse's assign reason
	toadd->next = NULL;                         // toadd is pointer coming from read_fromfile function and represents address of newnode 
	
	if (headptr == NULL){                       // if it is first time we add number to linked list it must be headptr so that headptr can show the address of the beginning of linked list
		headptr = toadd;                        // assigning address of newnode to headptr
		return;
	}
	
	if (toadd->size < headptr->size){           // inserting to head of list (newnode's size value comes before headptr's)
		toadd->next = headptr;                  // in this process headptr must be moved to one node back.To do this first assign newnodes next to headptr
		headptr = toadd;                        // then assign to add in other words move headptr to one back node  
		return;
	}
	
	while(traverse != NULL && toadd->size > traverse->size){ //finding proper position for newnode to insert
		tail = traverse;
		traverse = traverse->next;
	}

	if(tail->next==NULL){                                    //it controls if newnode is ad the end of link list
		tail->next = toadd;                                  // adding to the end of the linked list
		toadd->next = NULL;                                  // as newnode is the lastest element in linked list for now, its next must be NULL
	}else{
		tail->next = toadd;                                  // if its position is not at the end of linked list 
		toadd->next = traverse;                              // insering process will be like this 
		
	}
}

bool List::search(int value){                                // search through linked list and look for value and returns tru if it exists else returns false 
	
	Shoe_node *temp;                                         // declearing new pointer moving through linked list
	temp = headptr;
	while(temp!=NULL && temp->size != value){                // finding position
		temp = temp->next;	
	}
	
	if(temp==NULL){                                          // it doesn't exist temp will be NULL, beacuse it will reach last node's next which is NULL
		return false; 
	}else{
		return true;                                         // if it exist returns true
	}
	
}


void List::add_decrease(int value){
	
	Shoe_node *temp, *tail;                      // for the possibility of removing node declare 2 additional pointers for moving through the linked list  
	tail = headptr;  							 // for starting for beginning assign headptr				
	temp = headptr;                              // same reason as assigning to tail

	if(value >0){                                // if value is positive then addition to quantity process occurs
		while(temp!=NULL && temp->size < value){ // finding its position in linked list
		
			temp = temp->next;	
		}
		(temp->quant)++;                         // increasing quantity by 1
		return;
	}else if(value < 0){                         // if value is negative then it will be decreased or removed from linked list due to its quantity
		value *= -1;                             // to find its position its value must be converted to positive
		bool checker = search(value);            // if it exist in linked list then find position and remove node or decrease quantity 
		if(checker == true){                          
			while(temp!=NULL && temp->size < value){  // finding its position in linked list
			tail = temp;
			temp = temp->next;	
			}
			if(temp->quant == 1){                     // if quantity is 1 it means after decreasing quantity will be 0, so node must be removed from linked list 
				if(temp == headptr){                  // if it is headptr node then not to lose the access to headptr, headptr's next must show next of headptr
					headptr = headptr->next;
					delete temp;                      // after moving headptr operation can be perfomed, node is deleted
					return;
				}
				tail->next = temp->next;              // if it is not headptr then assign tail's next to temp's. Then easily delete the node 
				delete temp;
			}else{
				(temp->quant)--;                      // if its quantity is bigger than 1 then decrease it by 1
				return;
			}
		}else{
			printf("NO_STOCK\n");                // if doesn't exist then print NO_STOCK
			return;
		}
	}
}

void List::print(){                               // printing whole linked list to the screen 
	Shoe_node *temp;                              // declare temp pointer to move through linked list
	temp = headptr;                               // to start from beginning assign headptr
	while(temp!=NULL){
		printf("%d:%d\n",temp->size,temp->quant); // while temp is not NULL it will print size and existing quantity 
		temp = temp->next;                        // moving to next node
	}
	
	return;
	
}


void List::clear(){                              // after printing linked list must be deleted from memory
	while(headptr!=NULL){                        // while headptr is not NULL this function will move and delete all nodes in linked list 
		Shoe_node *temp;
		temp = headptr;
		headptr = temp->next;
		delete temp;
	}
	delete headptr;                              // at the end delete headptr which is showing last node in linked list,so that no node exists
}
