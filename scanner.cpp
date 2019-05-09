
//Rachel Festervand
//Program Translation 
//This is the scanner file for the compilor 

#include <iostream>
#include <ctype.h>
#include <fstream>
#include <sstream> 
#include <string> 
#include <stdlib.h>    
#include "token.h"
#include "scanner.h"  


using namespace std;

Scanner::Scanner(){
	lineNum = 0; 
    head  = NULL; 
    tail = NULL; 
} 

Scanner :: ~Scanner(){ 
	while(head != NULL) { 
		Token *temp = head; 
	 	head = head->next; 
		delete temp; 
	} 
} 

int Scanner::getLine(){ 
	return lineNum; 
} 

Token* Scanner::getHead(){
	return head;
}

void Scanner::setHead(Token* tkn){ 
	head = tkn; 
} 

void Scanner::deleteToken(){ 
    
   if(head == NULL) { 
		cout << "EOF" << endl; 
		return; 
   } 
   if(head == tail){ 
	    head = tail = NULL; 
    } 
	else { 
		head = head->next; 
    } 

}  

//Sets line number 
void Scanner:: setLine(){ 
	lineNum = lineNum + 1; 
}  

//Creates the token 
void Scanner::makeToken(string type,string inst){
      
    Token *temp =  new Token; 
	temp->next = NULL; 
	temp->lineNum = getLine(); 
	temp->tokenType = type;
	temp->instance = inst;
    
	//if linked list is empty set head 
    if( head  == NULL) { 
       head  = temp; 	  
    } 
    else { //List not empty 
       Token *last = new Token; 
	   last = head; 
  	   while(last->next!= NULL){ 
			last = last->next; 
       } 
	   last->next = temp;  
     } 
}  

void Scanner::getToken(string type, Token *token){ 
	token->lineNum = getLine(); 
	token->tokenType = type; 
} 

//Checks what type of token 
bool Scanner:: checkDelimiter (char x) { 
	string type; 
	string inst; 

    // =  <  >  :   +  -  *  /   %  . (  ) , { } ; [ ]
    if (x == '=') {
	   type = "eqTkn"; 
	   inst = "="; 
	   makeToken(type,inst);
		return true;  
	} 
	 if (x == '<') {
        type = "LaTkn";
        inst = "<";
        makeToken(type,inst);
		return true; 
     }
	 if (x == '>') {
        type = "RaTkn";
        inst = ">";
        makeToken(type,inst);
		return true; 
     }
	 if (x == ':') {
        type = "colanTkn";
        inst = ":";
        makeToken(type,inst);
		return true; 
     }
	 if (x == '+') {
        type = "plusTkn";
        inst = "+";
        makeToken(type,inst);
		return true; 
     }
	 if (x == '-') {
        type = "minusTkn";
        inst = "-";
        makeToken(type,inst);
		return true; 
     }
	 if (x == '/') {
        type = "slashTkn";
        inst = "/";
        makeToken(type,inst);
		return true; 
     }
	 if (x == '%') {
        type = "percentTkn";
        inst = "%";
        makeToken(type,inst);
		return true; 
     }
	 if (x == '.') {
        type = "periodTkn";
        inst = ".";
        makeToken(type,inst);
		return true; 
     }
	 if (x == '*') {
        type = "starTkn";
        inst = "*";
        makeToken(type,inst);
		return true; 
     }
	 if (x == '(') {
        type = "lparaTkn";
        inst = "(";
        makeToken(type,inst);
		return true; 
     }
	 if (x == ')') {
        type = "RparaTkn";
        inst = ")";
        makeToken(type,inst);
		return true; 
     }
	 if (x == '{') {
        type = "LbraceTkn";
        inst = "{";
        makeToken(type,inst);
		return true; 
     }
      if (x == '}') {
        type = "RBraceTkn";
        inst = "}";
        makeToken(type,inst);
		return true; 
     }
	 if (x == '[') {
        type = "LBraceTkn";
        inst = "[";
        makeToken(type,inst);
		return true; 
     }
	 if (x == ']') {
        type = "RBracketTkn";
        inst = "]";
        makeToken(type,inst);
		return true; 
     }
	 if (x == ',') {
        type = "commaTkn";
        inst = ",";
        makeToken(type,inst);
		return true; 
     }

	 if( x == ';'){ 
		type = "semiTkn"; 
		inst = ";"; 
		makeToken(type, inst); 
		return true; 
	} 
	else  
		return false; 
   	
}
//Check if keyword 
int  Scanner::checkKeyword(string word){ 
 	string type;
	string inst;    
	if(word == "Begin"){ 
		type = "keyword";
		inst = "Begin";  
		makeToken(type,inst); 
		return 5; 
 	}  
    else if(word == "End"){ 
        type = "keyword";
		inst = "End"; 
		makeToken(type,inst);
		return 6;  
	}	
    else if(word == "Loop"){
		type = "keyword";
		inst = "Loop";  
		makeToken(type,inst);
		return 8;  
	} 
	else if(word == "Void"){ 
		type = "keyword";
		inst = "Void";  
		makeToken(type,inst);
		return 9;  
	} 
	else if(word == "Return"){
		type = "keyword"; 
		inst = "Return"; 
		makeToken(type,inst);
		return 10;  
	} 
	else if(word == "Read"){
		type = "keyword";
		inst = "Read";  
		makeToken(type,inst);
		return 11;  
	} 
	else if(word == "Output"){
		type = "keyword";
		inst = "Output";  
		makeToken(type,inst);
		return 12;  
 	} 
	else if(word == "Program"){ 
		type = "keyword";
		inst = "Program";  
		makeToken(type,inst);
		return 13;  
	} 
	else if(word == "IFF"){ 
		type = "keyword"; 
		inst = "IFF"; 
		makeToken(type,inst); 
		return 14;   
	} 
	else if(word == "Then"){ 
		type = "keyword";
		inst = "Then";  
		makeToken(type,inst);
		return 15; 
	} 
	else if (word == "Let"){ 
		type = "keyword";
		inst = "Let";  
	    makeToken(type,inst);
		return 16; 
	}
	else if (word == "INT") { 
		type = "keyword";
		inst = "INT";  
		makeToken(type,inst); 
		return 7; 
	} 
	else { 
		return 0;   
	} 
	

} 

//This is the eof table. Numbers refer to the attached table  
int Scanner::table (string s){
  string type;   
  char p[s.length()];    
    for (int i = 0; i < sizeof(p); i++) { 
        p[i] = s[i]; 
    } 
  for(int i = 0; i < p[i]!= '\0'; i++) { 
	  //If char is // return comTkn and filter rest of strings  
	 if(isdigit(p[i])){ 
    	bool isvalid =  true; 
		isvalid = validInt(s);   
	  	type = "intNumTkn"; 
	  	string inst = s;  
	 	makeToken(type,inst);
	  	return 2;  
   	 }
	else if(s[0] >= 65 && s[0] <= 90 ){ //If uppercase string, check for keyword 
	 
			bool isKey = checkKeyword(s); 
			if (isKey != 0) //Is keyword  
				return isKey; 
            else{ //Is identifier 
				type = "IDTkn";
				string inst = s;   
				makeToken(type,inst); 
				return 4; 
			}
     }
	else if (s[0] >= 97 && s[0] <= 122){ 
		cout << "Error, tokens can not start with lower case" << endl;
		exit(EXIT_FAILURE);  
	}  
    else if ((s[0] >= 58 && s[0] <= 62 )|| ( s[0] >= 40 && s[0] <= 74 )||
             s[0] == 37 || s[0] == 123 ||s[0] == 125 || s[0] == 91 ||s[0] == 93 ){ 
		  
		  bool isKey  = checkDelimiter(s[0]);		  
		  return 1; 
	} 
  
	else if (bool isKey = checkDelimiter(p[i])){ 
    	if(s[0] == '-' && isdigit(s[1])) { 
			cout << "Scanner error: no negative number" << endl; 
			exit(EXIT_FAILURE); 
			return 3; 
         } 
    } 
	else if (p[i] == '\\'  && p[i+1] == 'n'){ //whitespace 
	    type = "wsTkn"; 
		string inst = "Whitespace instance"; 
		makeToken(type,inst); 
		return 1; 
    }
	else if (p[i] == 92) {
		return 1; 
    } 
	else if (p[i] == EOF){  
		type = "EOFTkn"; 
		string inst = "EOF"; 
		makeToken(type,inst); 
		return 0;  
    } 
	else{ //invalid charactor 
		cout << "Scanner error: Invalid charactor, line number: " <<  getLine()  << endl; 
	//	exit(EXIT_FAILURE); 
    } 
  }  		  
}  

bool Scanner::validInt(string s) { 
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
	 
}        


void Scanner:: print(){
	Token *tkn = new Token; 
	tkn = head;
    while (tkn != NULL) {  
		cout << "{" <<  tkn->tokenType << ",'" <<  tkn->instance; 
		cout << "'," << tkn->lineNum << "}" << endl;
        tkn = tkn->next;  
    } 
} 
