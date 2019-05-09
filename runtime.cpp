//Rachel Festervand 5/13/2019 
//This is the runtime file for the Compilor. It checks for runtime errors and creates an asm file to be interpreted by the virtual machine 

#include <iostream>
#include <string>
#include <fstream> 
#include "parser.h"
#include "scanner.h"
#include "runtime.h"
#include "stack.h" 

using namespace std; 

Runtime:: Runtime() {


}

void Runtime::run(Node *&tree) {
	
	Stack stack; 
	stack.makeStack(*&tree); 
	StackNode *stackPtr = new StackNode; 
    stackPtr = stack.printStack(); 

	//Check statements 
	statements(tree->right->right->left->center, stack);
	string result; 
	printToFile("STOP",result); 
	vars(tree->left);  
}

void Runtime::statements(Node *&branch, Stack stack) {
 
	if (branch->key == "in") { 
		string result; 
		if(branch->value == "IDTkn"){ 
			result = branch->value;  
		}  
		else{ 
			result = branch->id; 
		}  
		printToFile( "READ", result); 		
	}

	else if (branch->key == "out") {		
	    string result = branch->center->id; 
		printToFile( "WRITE", result); 
	}

	else{ 
		cout << "error" << endl; 
	} 
}

void Runtime::vars(Node *&tree){
	string result;
	if (tree!= NULL){
		result = tree->id; 
		printToFile(result,"0");  
    	vars(tree->left); 
	} 
} 

void Runtime::printToFile( string command, string value) {
	ofstream asmFile; 
	asmFile.open("output.asm",ofstream::app); 
	if(asmFile.is_open()){ 	
		asmFile << command << " " << value << endl;
		asmFile.close();  
	} 
}
