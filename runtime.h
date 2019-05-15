//Rachel Festervand
//Program Translation
//This is the runtime header file
#ifndef RUNTIME_H
#define RUNTIME_H
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctype.h>
#include <sstream>
#include <bits/stdc++.h>
#include "token.h"
#include "node.h"
#include "stack.h"
#include "parser.h"
#include "stackNode.h"

using namespace std;

class Runtime {

public:
    string global;
	ofstream asmFile; 
    string filename;
	void run(Node*&,string);
	void printToFile(string, string);
	void statements(Node*,Stack);
	void vars(Node*&);
	string checkExpr(Node*);
	void checkM(Node*);
	void checkA(Node*);
	Runtime();


};
#endif
