//Rachel Festervand
//Program Translation
//This is the scanner header file for project 1
#ifndef SCANNER_H
#define SCANNER_H
#include <string> 
#include <iostream> 
#include <fstream> 
#include "token.h" 

class Scanner{ 
	int lineNum;  
public:
   Token *head; 
   Token *tail;  
   int getLine();  
   void setLine();
   void deleteToken(); 
   void setHead(Token*);      
   void getToken(string, Token*);
   Token* getHead(); 
   void makeToken(string,string);
   void instance(string,Token*);  
   bool checkDelimiter(char);
   int checkKeyword(string); 
   int table(string);
   void processFile(ifstream &infile, string);
   bool validInt(string);  
   void print();    
   Scanner();
   ~Scanner();  
}; 



#endif 
