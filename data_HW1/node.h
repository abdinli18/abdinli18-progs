/* @Author
Student Name: Elvin Abdinli
Student ID: 150180904
Date: 10/21/2019*/


// node.h
// Shoe_node struct definition
struct Shoe_node
{
	int size;	                   // the size of shoe
	int quant;                     // number of shoes by size
	Shoe_node *next;               // pointer to another object of the same type
};
