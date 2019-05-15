//Rachel Festervand 5/13/2019
//This is the runtime file for the Compilor. It checks for runtime errors and creates an asm file to be interpreted by the virtual machine

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <ctype.h>
#include <sstream>
#include <bits/stdc++.h>
#include "parser.h"
#include "scanner.h"
#include "runtime.h"
#include "stack.h"

using namespace std;

Runtime:: Runtime() {


}

void Runtime::run(Node *&tree, string file) {

	Stack stack;
	stack.makeStack(*&tree);
	StackNode *stackPtr = new StackNode;
    //stackPtr = stack.printStack();
	asmFile.open(file.c_str(),ios::out);


	//Check statements
	statements(tree->right->right->left->center, stack);
	statements(tree->right->right->right,stack);
   	string result;
	printToFile("STOP",result);
	vars(tree->left);
	asmFile.close();
}

void Runtime::statements(Node *branch, Stack stack) {
   cout << "key in state" << branch->key << endl;
 if(branch != NULL){
	if (branch->key == "in") {
		string result;
		result = branch->value;
		global = result;
		printToFile( "READ", result);
		printToFile("LOAD",result);
		printToFile("STORE",result);

	}
	else if (branch->key == "out") {
	    string result = branch->center->value;
	   // cout << result << endl;
	    if(result == "-"){
            printToFile("LOAD",global);
            printToFile("MULT","-1");
            printToFile("STORE",global);
            printToFile("WRITE",global);
	    }
	    else{
            printToFile("STORE",result);
            printToFile("WRITE",result);
	    }
	}
	else if (branch->key =="block"){
        if(branch->right->left->center != NULL){
        statements(branch->right->left->center,stack);
        printToFile("STACKR","0");
        printToFile("POP","");
        printToFile("STORE","X3");
        printToFile("WRITE","X3");
        printToFile("STACKR","0");
        printToFile("POP","");
        printToFile("STORE","X2");
        printToFile("WRITE","X2");
        printToFile("STACKR","0");
        printToFile("POP","");
        printToFile("STORE","X1");
        printToFile("WRITE","X1");
        printToFile("STOP","");
        printToFile("X1","0");
        printToFile("X2","0");
        printToFile("X3","0");
        }
    }




	else if (branch->key == "IF"){
        cout << branch->left->id << "IFF" << endl;
        if(branch->left->id == "intNumTkn"){
            printToFile("WRITE","1");
        }
        else{
            cout << branch->left->key;
            string first = checkExpr(branch->left);
            printToFile("IN: LOAD",first);
            printToFile("STORE",first);
            printToFile("LOAD",first);
            string second = checkExpr(branch->center);
            printToFile("SUB",second);
            //cout << branch->operate << "operate" << endl;
            if(branch->operate == "= >"){
                printToFile("BRNEG","OUT");
                // printToFile("ADD",second);
            }
            if(branch->operate == "= <"){
                printToFile("BRPOS","OUT");
                // printToFile("ADD",second);
            }
            if(branch->right->center->key == "out"){
                string output = branch->right->center->center->value;
                printToFile("WRITE",output);
                printToFile("OUT:","STOP");
            }
            else{
                statements(branch->right->center,stack);
            }
    }

}

	else if (branch->key == "Loop"){
        //cout << branch->left->key;
        string first = checkExpr(branch->left);
        printToFile("In: LOAD",first);
        printToFile("SUB","1");
        printToFile("STORE",first);
        printToFile("BRZNEG","OUT");
        printToFile("WRITE",first);
        printToFile("LOAD",first);
        printToFile("SUB","1");
        printToFile("BR","In");
        printToFile("OUT:","STOP");


	}

	else if(branch->key =="assign"){
        printToFile("LOAD",branch->value);
		printToFile("ADD","1");
        printToFile("STORE",branch->value);
        printToFile("WRITE",branch->value);
	}
	else if (branch->key == "mstat"){
		if(branch->left != NULL)
			statements(branch->left,stack);
	}

	else{
		statements(branch->center,stack);
	}
  }
}

void Runtime:: checkA(Node *tree){
    string result;
    if(tree!= NULL){
        if(tree->key == "A"){
            if(tree->right->operate == "*"){
                printToFile("MULT",tree->center->value);
                checkA(tree->center);
            }
        }
        else{
            return;
        }
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

void Runtime::checkM(Node *tree){
    if(tree!= NULL){
        cout << tree->id << "m id" << endl;
        if(tree->id == "minusTkn") {
            printToFile("MULT","-1");

        }
    }
}

string Runtime:: checkExpr(Node *tree){

   //cout << tree->id << "check expr " << endl;
   if(tree != NULL){
       if(tree->id == "intNumTkn" | tree->id == "IDTkn") {
           return tree->value;
       }
   }

}

void Runtime::printToFile( string command, string value) {

		asmFile << command << " " << value << endl;

}
