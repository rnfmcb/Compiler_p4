//Rachel Festervand
//Program Translation
//This is the linked list nodes for the stack 


#ifndef STACKNODE_H 
#define STACKNODE_H 	

#include <string> 
using namespace std; 


struct StackNode{   
    int block;
	int index;  
	int multBlock; 
    string id;
	string value; 
    StackNode *next;   
};  

#endif 
