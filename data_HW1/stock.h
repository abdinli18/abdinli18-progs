/* @Author
Student Name: Elvin Abdinli
Student ID: 150180904
Date: 10/21/2019*/


#ifndef FILEOPERATIONS_DYNAMIC_H
#define FILEOPERATIONS_DYNAMIC_H

#include <stdio.h>

#define strnicmp strncasecmp //strnicmp function was renamed to strncasecmp, and strnicmp made into a wrapper for the new strncasecmp to avoid breaking existing users.

#include "node.h"                 // including Shoe_node struct definition

struct List{                      // declaration of all functions used in shop_program.cpp
 	Shoe_node *headptr;           // and pointer which has type Shoe_node* type showing the head of linked list
	void create();                // creating empty list
	void read_fromfile(char*);    // reading from file and sending to other functions 
	Shoe_node* createnode(int);   // creating newnode
	void add_decrease(int);       // increasing or decreasing quantity, if quantity is 1 removing it without decreasing 
	void insert(Shoe_node *);     // inserting node to the head or between two nodes or to the end of the linked list 
	bool search(int);             // search that number coming from input.txt exists in linked list or doesn't 
	void print();                 // printing whole linked list
	void clear();                 // clearing linked list from memory after printing to the screen
};
#endif 

