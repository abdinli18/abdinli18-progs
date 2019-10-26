/* @Author
Student Name: Elvin Abdinli
Student ID: 150180904
Date: 10/21/2019*/


#include <iostream> 
 
#include "stock.h"                    // including structure List which is containing function declerations and headptr

using namespace std;

typedef Shoe_node shoe_record;
typedef List Datastructure;        

Datastructure book;                   // creating object named book

int main(int arg_count, char**args){
	
	book.create();                    //calling function create located in list2.cpp file
	book.read_fromfile(args[1]);	  // calling function read_fromfile located in list2.cpp
	return 0;
	
	
}
