//Rachel Festervand
//Program Translation
//This is the header file for the parser 
#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
#include <fstream>
#include "node.h"
#include "token.h"
#include "scanner.h" 

class Parser{ 
   Node *root; 
   int level;
    
   public:
     Token *tkn;
     Token *head;
	 int varNum; 
	 Node *branch; 
     int getLevel();
	 int addLevel();
	 int setLevel(int); 
	 void findEmpty(Node*,Node*);  
     Node* newNode(string); 
  	 void FADriver(ifstream &infile, string, Scanner&);
  	 Node* parse(ifstream &infile,string); 
  	 Token* getToken(Token*);
	 void RO(Token*&, Node*&); 
	 void R(Token*&, Node*&); 
	 void M(Token*&, Node*&); 
	 void N(Token*&, Node*&); 
   	 void A(Token*&,Node*&);
	 void expr(Token*&,Node*&);
	 void mstat(Token*&,Node*&);  
  	 void stat(Token*&,Node*&);
     void begin(Token*&,Node*&); 
  	 Node* prog(Token*&,Node*&);
   	 void vars(Node*&);
	 Token* vars2(Token*&,Node*&);     
     Parser();
      
}; 
 
#endif


