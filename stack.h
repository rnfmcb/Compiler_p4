//Rachel Festervand 
// Compilors 
//This is the header file for the stack file  
#include <iostream> 
#include <string> 
#include "node.h"  
#include "stackNode.h" 

#ifndef STACK_H 
#define STACK_H 

using namespace std; 
class Stack { 
     
	 public:
	 StackNode *top; 
	 int stackCount; 
	 int outFlag;   
	 int block; 
     void printPreorder(Node*);
	 void printCenter(Node*);  
     void print(Node*);  
     void push(string,string,int);
	 void pop();  
	 int find(string);
	 StackNode* returnNode(int); 
	 void global(Node*);
	 void makeStack(Node*);  
	 void local(Node*); 
	 StackNode* printStack(); 
     Stack();  
}; 
  
#endif 
 
