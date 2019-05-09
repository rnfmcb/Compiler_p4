//Rachel Festervand
//Program Translation
//This is the runtime header file 
#ifndef RUNTIME_H 
#define RUNTIME_H
#include <string> 
#include <iostream> 
#include <fstream> 
#include "token.h" 
#include "node.h"
#include "stack.h"
#include "parser.h"
#include "stackNode.h" 

using namespace std; 

class Runtime {
	
public:
	void run(Node*&); 
	void printToFile(string, string); 
	void statements(Node*&,Stack);
	void vars(Node*&);  
	Runtime(); 

	
};
#endif 
