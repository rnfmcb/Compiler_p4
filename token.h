//Rachel Festervand
//Program Translation
//This is the types including token file 


#ifndef TOKEN_H 
#define TOKEN_H 	

#include <string> 
using namespace std; 


struct Token{  
    int lineNum;
    string tokenType; 
	string instance;
    Token *next;   
};  

  

#endif 
