//Rachel Festervand 4/29/2019 
//Program Translation
//This is the staic semetics file.  
#include <iostream>
#include <string> 
#include <fstream>
#include <stdlib.h>
#include <ctype.h>
#include <sstream>
#include <bits/stdc++.h> 
#include "node.h" 
#include "parser.h" 
#include "stack.h" 

using namespace std; 


Stack::Stack(){
    stackCount = 0;
	outFlag = 0;  
	block = 0; 
	top  = NULL;  
} 

void Stack:: print(Node *ptr) {
	string value; 
    if (ptr-> level != 0){
   			int printLevel = ptr->level;
    		string dash; 
			if(ptr->value != " "){
				value = ptr->value; 
			} 
    		for(int i = 1; i <= printLevel; i++){
        		cout << "--";
  		 	 }
    		cout << ptr->key << " " << ptr->id << value << endl;
			printCenter(ptr); 
    }
   else 
      cout << ptr->key << " " << value  << endl;
} 

void Stack:: printCenter(Node *ptr){
	int printLevel = ptr->level; 
	string dash, value;
	if(ptr->value != " "){
		value = ptr->value; 
	}  
	for(int i = 1; i <= printLevel; i++){
		cout << "--"; 
	} 
	cout << ptr->key << " " << value << endl;

	if(ptr->center != NULL){
		printCenter(ptr->center); 
	} 
	if(ptr->left != NULL){
		printCenter(ptr->left); 
	} 
	if(ptr->right != NULL){
		printCenter(ptr->right); 
	}  
}  



void Stack:: printPreorder(Node *ptr){ 

     if(ptr!= NULL){  
    	 print(ptr);
     	 //cout << "print left" << endl; 
     	 printPreorder(ptr->left);
     	 //cout << "print right" << endl; 
         printPreorder(ptr->right);
      }  
}

//This function pushes an argument on the stack 
void Stack:: pop(){
    StackNode *temp = new StackNode;
    temp = top;
     if(top == NULL){ 
         cout << "Stack underflow" << endl; 
	     exit(EXIT_FAILURE); 
      } 
      else{ 
	     temp = top; 
	     top = top->next; 
	     temp->next = NULL; 
	     temp = NULL;  
       }
} 

void Stack:: push(string i, string v,  int b){
	if(stackCount > 100){
		cout << "Stack overflow " << endl; 
		exit(EXIT_FAILURE); 
	} 
	else{ 
    	StackNode  *temp =  new StackNode;
    	temp->next = NULL;
    	temp->id = i; 
		temp->value = v; 
        temp->block = b;
		temp->index = stackCount;
		temp->multBlock = 0; 
		//	cout << indexNum << " index num " << endl;   

       //Make sure value is not created in same scope 
        int num = temp->block; //value to be added 
		int numBlock; //value on stack 
		int index = -1;  
		//cout << num << " block from num  from being pushed stack" << endl; 		
	    index  = find(i); //Number on stack  
		int defined = 0; 
 		//cout << "index " << endl; 
		if(index != - 1){ 
			StackNode *test = new StackNode; 
			test  = returnNode(index);
			//cout << "test value " << test->value << endl; 
			if(test->value != " ") { 
				defined = 1; 
			} 
			//cout << "test value in from value foudn on stack  " << test->value << endl;  
		    numBlock = test->block; //block from found on stack  			
			//cout << numBlock << "block from  item found on stack " <<  endl;
			if(numBlock ==  num  && outFlag != 0) { //In same block, already defined  
				cout <<"Stat sem error: Var already defined" << endl;
    	         exit(EXIT_FAILURE);
			}
			if(numBlock == num){ 
				cout << "Stat sem error: Var already defined" << endl; 
				exit(EXIT_FAILURE); 	
			} 	
		    if(numBlock != 0 && num < numBlock) {  //If not a global and if block is less, so underdefined  
				cout << " Stat sem error: var undefined " << endl; 
			}  
				
			if(outFlag != 0 && defined == 0 ){ 
				test->value == " "; 
				cout << "Stat sem error: Var undefined " << endl; 
				exit(EXIT_FAILURE); 
			}    
			if(outFlag != 0 && index == -1){ 
				cout << "Stat sem error: Trying to use a value that is not defined " << endl;
			}  
		} 	
     	else{ //index equals -1 
			if(outFlag != 0){  
				cout << "Stat sem error: Var undefined " << endl; 
				exit(EXIT_FAILURE); 
			} 
			if(top == NULL) { 
				top = temp;
			}  
			else{ 
    			temp->next = top; 
				top = temp; 
	 		} 
   	    }
   } 
  // printStack(); 
}  

//This arguemnt finds a value on the stack, returns -1 if not there and index if there
int Stack:: find(string value){
	int num; 
	StackNode *temp = new StackNode; 
	temp = top;
	
	while(temp != NULL){ 
		if(temp->id == value){ 
			num = temp->index;
			//cout << "index number in find " << num << endl;  
			return num; 
		} 
	 temp = temp->next; 
     } 
	return -1; 
}

StackNode* Stack::returnNode(int num){
	StackNode *temp = new StackNode; 
	temp = top; 
	while(temp != NULL){
		if(temp->index == num){
			return temp; 
		}
	temp = temp->next; 
	} 
}
 


void Stack::makeStack(Node* ptr){ 
	global(ptr);
  	block = block + 1;   
  	global(ptr->right);//check block vars 
  //	cout << "check stat" << endl;  
  	local (ptr->right->right->left); //Check stat  
  	local(ptr->right->right->right);   
  	//printStack(); 
}  

//Create the stack from the parse tree 
void Stack::global(Node* ptr){ 
	//Make global block
	//cout << "got in global" << endl;  
	//cout << "ptr " << ptr->key << endl;  
	if(ptr != NULL){ 
		if(ptr->left != NULL){ 
			string i = ptr->left->id; 
			string val = ptr->left->value;  
			push(i,val,block);
			stackCount = stackCount + 1;  
			global(ptr->left); 
		} 
    }    
}  

void Stack::local(Node* ptr){


	if(ptr != NULL){	
		//cout << ptr->key << "in local "   << endl;   
			
	    if(ptr->key  == "Stat"){ 
			string val = ptr->center->id;
		    string i; 
		//	cout << "value in stat " << val;  
			push(val,i,block); 
			stackCount = stackCount + 1;	
			local(ptr->center);  
		
		 } 
	      if(ptr->key == "expr"){
			string val = ptr->id;
			char ch = val[0]; 
			if(isupper(ch)){ //Was an identifier, so put on stack
				string i;  			
				//cout << "value with expr " << val << endl;
				push(val,i,block); 
				stackCount = stackCount + 1;
					if(outFlag != 0){ 
						StackNode *temp = new StackNode; 
						int ifThere = find(val); 
						temp = returnNode(ifThere); 
						//cout << temp->value << " temp value out " << endl; 
						outFlag = 0; 
							if(temp->value == " "){ 
								cout << "Stack Error: value undefined" << endl; 
								exit(EXIT_FAILURE); 
							} 
					} 
				local(ptr->left); 
			 } 
			 else{
				//cout << "Was not an identifier " << endl; 
			  
			 } 
	 
		}  
		 if(ptr->key == "out"){
			outFlag = 1; 
			//cout << outFlag << "flag set in out" << endl;
			local(ptr->center); 	 
	    } 
		else {
			local(ptr->center); 
		}  
   } 	
      
} 

//Prints stack for debugging purposes 
StackNode* Stack:: printStack(){ 
	StackNode *temp = new StackNode; 
	if(top == NULL){
		cout << "Nothing in stack" << endl; 
		exit(EXIT_FAILURE); 
	} 
	else{ 
		temp = top; 	
		while(temp != NULL){ 
			cout << " id " << temp->id <<  " block " << temp->block; 
			cout  << " value " <<  temp->value << "index " << temp->index; 
			cout << endl; 
			temp = temp->next; 
		} 
	} 
	return temp; 
} 


