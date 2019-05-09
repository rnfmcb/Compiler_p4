//Rachel Festervand 
//Program Translation
//This is the parser file  
//This file uses a parser
#include <iostream> 
#include <string> 
#include <fstream>
#include <stdlib.h> 
#include <ctype.h> 
#include <sstream>
#include <bits/stdc++.h>   
#include "token.h" 
#include "scanner.h"
#include "parser.h"  
#include "node.h"
#include "stack.h"  

using namespace std; 

Parser::Parser(){


} 

int Parser::getLevel(){ 
		return level; 
}

int Parser::addLevel(){ 
	level = level + 1;  
}
int Parser::setLevel(int i){
	level = i; 
}  


Node* Parser::newNode(string k){
	Node *node = new Node; 
	node->key = k; 
	node->level = getLevel(); 
	node->left = NULL; 
	node->right = NULL; 
	node->center = NULL;  
	return node; 
}   

void Parser:: findEmpty(Node *tree, Node *leaf){ 
	if(tree->left != NULL){ 
		findEmpty(tree->left,leaf); 
    } 
	else { 
		tree->left = leaf; 
	} 
} 

void Parser::FADriver(ifstream &infile,string filename,Scanner& scanner){ 
	string line;
	string type;
	infile.open(filename.c_str());
    if(infile.fail()){
		cout << "File does not exit " << endl; 
        exit(EXIT_FAILURE); 
    }  
	if(infile.is_open()){  
		if(!infile){
			cout << "Scanner Error: unable to open file" << endl;
					exit(EXIT_FAILURE); 
			}
				if (infile.peek() == ifstream::traits_type::eof() ){
				  cout << "{EOFTkn,EOF,1}" << endl;
				  exit(EXIT_FAILURE);
				 }

	string word;
	int state;
	while(getline(infile,line)){
		scanner.setLine();
		//Comment filter 
		if (line[0]!= 92){      

			istringstream stm(line); 
			while(stm >> word){
				if(word.empty()){ 
					scanner.setLine();                              
			    }    	  	
				state = scanner.table(word); 
				}
			}
		else { 
		  
	    }        		  
		} 
  
		infile.close();

  } 
} 


Token* Parser:: getToken(Token *tkn){
    Token *temp = new Token; 
    temp = head; 
    head == NULL; 
 
    while(temp != NULL){ 
		if(temp->instance == tkn->instance){ 	 
			if(temp->next == NULL){ 
				head = temp; 
				return temp;
			}  
            else{
			   head = temp->next; 
			   return temp->next; 
            } 
         }
        temp = temp->next;   
     } 
   
}

//I do not put this process in the tree 
void Parser::RO(Token *&tkn, Node*& tree){ 
  
   	if(tkn->instance == "<" ) {
	  *&tkn = getToken(tkn); 
         
	} 
    else if (tkn->instance == ">"){ 
		*&tkn = getToken(tkn); 
    } 
	
    else if (tkn->instance == "="){
		Token *temp = new Token; 
		temp = tkn; 
		tkn = getToken(tkn); 
		if (tkn->instance == ">" | tkn->instance == "<" | tkn->instance == "="){  
			tkn = getToken(tkn); 
		    *&tkn = tkn; 
	     
		}  
	} 
	else { 
		cout << "Parser error in RO: Expected < | = < | = > | = = | ="; 
		cout << "recieved " << tkn -> instance << endl;
		exit(EXIT_FAILURE);  
	}
    
} 
 
void Parser::R(Token *&tkn, Node*& tree){
	addLevel(); 
	if(tkn->tokenType == "IDTkn" | tkn->tokenType == "intNumTkn"){ 
		tree->center = new Node; 
		tree->center = newNode("R");
		tree->center->id = tkn->instance;   
	   
	}
     else if(tkn->instance == "["){
		tree->center = new Node; 
		tree->center =  newNode("expr"); 
		expr(tkn,tree->center); 
		
	 
    } 
    else{ 
		cout << "Parser error in R:  expected [, got "; 
		cout << tkn->instance << endl;  
		exit(EXIT_FAILURE); 
	} 
    
 
} 

void Parser:: M(Token *&tkn, Node*& tree){ 
	addLevel();
	if( tkn->tokenType == "IDTkn" | tkn->tokenType == "intNumTkn"|tkn->instance == "["){ 
		tree->center = new Node; 
		tree->center = newNode("M"); 
	    R(tkn,tree->center); 
    } 
   else	if(tkn->instance == "-"){
		*&tkn = getToken(tkn);
		tree->center = new Node; 
		tree->center = newNode("M"); 
		tree->center->value = tkn->instance;  
		M(tkn,tree->center); 
    } 
	
   else{ 
		cout << "Parser error in M: expected id, int or [ or - but got " << endl; 
		exit(EXIT_FAILURE); 
   } 
} 

void Parser::N(Token *&tkn, Node*& tree){ 
	addLevel(); 
	if(tkn->tokenType == "IDTkn" | tkn->tokenType == "intNumTkn" | tkn->instance == "["){
		tree->center = new Node; 
		tree->center = newNode("N");
		/*if(next ->instance == "//"){
			tree->left = new Node; 
			tree->left = newNode("M"); 
			tkn = *&next; 
			M(tkn,tree->left); 
 		} 
	   else{ 
	     tkn = *&temp; 
		 M(tkn,tree->center);
		} */  
	}
	else{    
		cout << "Parser error in N, expected id, int or [ " << endl; 
		exit(EXIT_FAILURE); 
    }
}  

void Parser::A(Token *&tkn, Node*& tree){
	addLevel(); 
    if(tkn->tokenType == "IDTkn" | tkn->tokenType == "intNumTkn"| tkn->instance == "["){
	  
	   tree->center = new Node; 
	   tree->center = newNode("A");
	   tree->center->id = tkn->instance;
	   N(tkn, tree->center);
       //Token *temp = new Token; 
	   //temp = tkn;  
	   //tkn = getToken(tkn);

	    
      if (tkn->instance == "*"){
		  tree->right = new Node; 
		  tree->right = newNode("A"); 
		  tree->right->value = "*"; 
		  *&tkn = tkn; 
		  tree->right->id = tkn->instance;    
		  A(tkn,tree->right);
	   } 

	  else{ 
		//tkn = *&temp; 
	  }  	
   }
  else{ 
    cout << "Parser error in A: Expected ID, int or [, but got " << tkn->instance;  
	exit(EXIT_FAILURE); 	
   } 
} 

//<expr>-> <A> + <expr> | <A> - <expr> | <A>
void Parser:: expr(Token *&tkn, Node *&tree){ 
	addLevel(); 
	if( tkn->tokenType == "intNumTkn" | tkn->tokenType == "IDTkn") {    
		addLevel();
		tree->center = new Node; 
	    tree->center = newNode("A"); 
		A(tkn,tree->center);
		//cout << "Token after A " << tkn->instance << endl;
		//tkn = getToken(tkn);  
		//cout << "Token next " << tkn->instance << endl;
  
		if(tkn->tokenType == "+" | tkn->tokenType == "-"){ 
			tkn = getToken(tkn); 	
            if( tkn->tokenType == "intNumTkn" | tkn->tokenType == "IDTkn" | tkn->tokenType == "[") { 
				tree->right = new Node; 
				tree->right = newNode("expr"); 
				tkn = *&tkn; 
				tree->right->id = tkn->tokenType; 			 
				expr(tkn,tree->right); 
			}  
        }
	 	else{ 
     		tkn = *&tkn; 
		} 	 
    }      
	 else if(tkn->tokenType == "["){
		tree->center = new Node; 
		tree->center = newNode("expr"); 
		expr(tkn,tree->center); 
	} 
	else{ 
//		cout <<  "Parser error in expr: expected int, id or [ but recieved " << tkn->instance << endl; 
	} 
}
void Parser::mstat(Token *&tkn, Node *&tree){ 
	addLevel(); 
	tree->right = new Node; 
	tree->right = newNode("mstat"); 
	*&tkn = getToken(tkn);
	//cout << "Token in mstat " << tkn->instance << endl;  
	if(tkn->instance == "Read" | tkn->instance == "Output"  |
       tkn->instance == "IFF" | tkn->instance == "Loop" |
       tkn->tokenType == "IDTkn" | tkn->instance == "Begin") {
       tree->left = new Node; 
	   tree->left = newNode("stat"); 
	   stat(tkn,tree->left); 
	   *&tkn = getToken(tkn); 
	   if(tkn->instance == "End"){ 
	       *&tkn = getToken(tkn); 
		   if(tkn->instance == ":"){
		       mstat(tkn,tree->right); 
			} 
		}     

	 } 
	else if(tkn->instance == "End"){
	} 

	else{ 
		cout << " Parser error in mstat: Expected a end or keyword  token, got " << tkn->instance << endl; 
		exit(EXIT_FAILURE); 
	} 
} 


//Stat <in> | <out> | <block> | <if> | <loop> | <assign>
void Parser::stat(Token *&tkn, Node *&tree){ 
	addLevel(); 
	//cout << "Token in stat " << tkn->instance << endl; 
 
	if(tkn->instance == "Output"){ 
		tree->center  = new Node; 
		tree->center = newNode("out");

	  //  cout << "out node " << tree->right->key << endl; 
		*&tkn = getToken(tkn);
		//cout << "tkn after output " << tkn->instance << endl;  
		if(tkn->instance == "["){
			tkn = getToken(tkn);  
		//	cout << "After [ " << tkn->instance << endl; 
		    tree->center->center = new Node; 
			tree->center->center = newNode("expr"); 
			tree->center->center->id = tkn->instance;
			tree->center->center->value = tkn->tokenType;  
		   	expr(tkn,tree->center->center);
			*&tkn = getToken(tkn); 
			//cout << "after expr in out " << tkn->instance << endl;  
				if(tkn->instance == "]"){
				 
				} 
				else{
				    cout << "Parser error in output/stat: expect ], recieved " << tkn->instance << endl; 
					exit(EXIT_FAILURE);
			    }
          }
	      else{ 
			cout << "Parser error in output/stat: expected [, got ";
			cout << tkn->instance << endl;
            exit(EXIT_FAILURE);
          }
      } 
      
	  else if (tkn->instance == "Read"){
		  string data;
		  string value;   
	      tkn = getToken(tkn); 
		  if(tkn->instance == "["){
			 tkn = getToken(tkn); 
			 if( tkn->tokenType == "IDTkn" ) {
				data = tkn->instance;  
				value = tkn->tokenType; 
				tkn = getToken(tkn); 
					if(tkn->instance == "]"){ 
						tree->center = new Node; 
						tree->center = newNode("in");
					    tree->center->id = data;
						tree->center->value = value;  
					//	cout << " read data in parser " << tree->center->id << endl; 
						 
					} 
				  /*	else { 
						cout << "Parser error: expected ], recieved "; 
						cout << endl;
						exit(EXIT_FAILURE);
				 	 }*/
  			  }  
              else { 
			      cout << "Parser error: expected indetifier, recieved ";  
				  cout << tkn->tokenType << endl; 
				  exit(EXIT_FAILURE);
			  } 
           }
		  /* else { 
		       cout << "Parser error: expected [ recieved "; 
			   cout << endl;
			   exit(EXIT_FAILURE);
		    }*/ 
        	
    } 
	else if(tkn->instance == "Begin"){
		//cout << "Second begin " << endl;  
		tree->center = new Node; 
		tree->center = newNode("Block"); 
		begin(tkn,tree->center); 
	} 

	else if(tkn->instance == "IFF"){
 	 	tree->center = new Node; 
		tree->center = newNode("IF"); 
		tkn = getToken(tkn);  
		if(tkn->instance == "[") { 
		    *&tkn = getToken(tkn);  
			tree->left = new Node; 
			tree->left = newNode("expr");  
			expr(tkn, tree->left); 
			RO(tkn,tree->left); 
			tree->right = new Node; 
			*&tkn = getToken(tkn); 
			tree->right = newNode("expr"); 
			expr(tkn, tree->right);  
			if(tkn->instance == "]"){
				tree->center = new Node; 
				tree->center = newNode("stat");
				*&tkn = getToken(tkn); 		 
				stat(tkn,tree->center); 
			} 
		/*	else{ 
				cout << "parser error in IFF: expected ], recieved "; 
				cout << tkn->instance << endl;
				exit(EXIT_FAILURE);
			}  */	
		}
		/*else{ 
			cout << "Parser error in Iff: Expected [, recieved "; 
			cout << tkn->instance << endl;
			exit(EXIT_FAILURE); 
		} */
 
	} 
    else if(tkn->instance == "Loop"){
        tree->center = new Node;
        tree->center = newNode("loop");
        tkn = getToken(tkn);
        if(tkn->instance == "[") {
            tkn = getToken(tkn);
            tree->left = new Node;
            tree->left = newNode("expr");
            expr(tkn, tree->left);
            RO(tkn,tree->left);
            tree->right = new Node;
            tree->right = newNode("expr");
            expr(tkn, tree->right);
            if(tkn->instance == "]"){
                tree->center = new Node;
                tree->center = newNode("stat");
                tkn = getToken(tkn);
                stat(tkn,tree->center);
             }
             else{
                cout << "parser error: expected ], recieved ";
                cout << tkn->instance << endl;
                exit(EXIT_FAILURE);
             }
         }
		 else{
			cout << "parser error: expected [ but got " << tkn->instance << endl; 
			exit(EXIT_FAILURE); 
		 } 

     } 
	else if (tkn->tokenType == "IDTkn"){
		string data = tkn->instance; 
		*&tkn = getToken(tkn);
		if(tkn->instance == "="){ 
			tree->center = new Node; 
			tree->center = newNode("assign");
 			tree->center->id = data;   
			*&tkn = getToken(tkn); 
		   	expr(tkn,tree->center); 
		} 
		else{
			cout << "Parser error: Expected =, recieved "; 
			cout << endl; 
			exit(EXIT_FAILURE);
		} 
	} 

	else { 
		cout << "Parser error in expr: expected a keyword, got "; 
		cout << tkn->instance << endl;
		exit(EXIT_FAILURE);  
     } 
  
} 


 
//Block -> Begin<vars><stats>End 
void Parser:: begin(Token *&tkn, Node *&tree){ 
   //  cout << "Token in begin " << tkn->instance;       
     if (tkn->instance == "Begin"){
		setLevel(1);   	
        tree->right = new Node; 
		tree->right = newNode("Block"); 
        tkn = getToken(tkn);
		//cout << "tkn in begin " << tkn->instance; 
		addLevel(); 
	   	if(tkn->instance == "INT"){ //Vars
			 setLevel(1);  
			 vars(tree->right);          
		}  
         
       }
         //<stats> -><stat>:<mStat> 
	   	if(tkn->tokenType  == "keyword" ){ //Stats 
		   setLevel(2);  
	       tree->right->right = new Node; 
		   tree->right->right = newNode("Stats");
		   addLevel(); 
		   tree->right->right->left = new Node; 
		   tree->right->right->left = newNode("Stat");  
		   stat(tkn,tree->right->right->left);
		   tkn = getToken(tkn);
		   //cout << "tkn after stat" << tkn->instance << endl;
           if(tkn->instance == ":") {  
			  mstat(tkn,tree->right->right);
			 // cout << "tkn after mstat" << tkn->instance;  
					if(tkn->instance == "Read" | tkn->instance == "Output"  |
   					    tkn->instance == "IFF" | tkn->instance == "Loop" |
       					tkn->tokenType == "IDTkn" | tkn->instance == "Begin") {
       					tree->right->left = new Node;
						tree->right->left = newNode("stat"); 
						stat(tkn,tree->right->left);
					 	*&tkn = getToken(tkn);  
					} 
				
 				 
			  
				/*else{ 
					cout << "Parser error in begin: expected end token " << endl; 
				 	exit(EXIT_FAILURE); 
				 } */  
			
			} 
			else{ 
				// cout << "pairser erro in begin, expected : "; 
				// cout << "received " << tkn->instance; 
				// exit(EXIT_FAILURE); 
			   }   

	       }  	 
  
}

//Vars empty| INT Identifier Integer <vars>
void Parser::vars( Node *&tree){
   addLevel();  
  // cout << tkn->instance << "token in vars " << endl; 
   string id; 
   string num; 
   Token *tkn1 = getToken(tkn); 
   Token *tkn2 = getToken(tkn1);
   id = tkn1->instance; 
   num = tkn2->instance;   
   //cout << "is and num " << id << " " << num;  
   if(tkn->instance  == "INT" && tkn1->tokenType == "IDTkn" && tkn2->tokenType == "intNumTkn"){ 
      
       tree->left= new Node;  
	   tree->left = newNode("Vars");  
	   tree->left->id = id; 
	   tree->left->value = num; 
    
   }
   else { 
		cout << "Parser error: INT was not followed by initialization " ; 
		exit(EXIT_FAILURE); 
   } 
   tkn = *&tkn2;
   Token *nexttkn = new Token; 
   nexttkn = getToken(tkn); 
   tkn = *&nexttkn;
  // cout << "token " << tkn->instance << endl;  
	if(tkn->instance == "INT"){
		vars(tree->left); 
	} 
    // cout << "tkn in vars after first" << tkn->instance << endl;      
} 



//Starts here <vars><block> 
Node* Parser::prog(Token *&tkn, Node *&tree){
	Token *temp = tkn; 
   
   // cout << "tokenType from prog " << tkn->instance << endl;
    //Vars 
    if(tkn->instance == "INT"){
        vars(tree);

    }
//	cout << "got to begin" << endl;  
    //<Block> 
    if (tkn->instance == "Begin"){
        begin(tkn,tree);
    }

   /* else{ //Error
        cout << "Parser error in program: Expected begin or INT, recieved ";
        cout << tkn->instance << endl;
		exit(EXIT_FAILURE); 
     }*/
 
 return tree;
}


Node*  Parser::parse (ifstream &infile,string filename){
    Scanner scan;      
    root = NULL; 
	branch = NULL;
	varNum = 0;   
    FADriver(infile,filename,scan);
   // Token *tkn = scanner(scan);     
   // cout << "parsing tkn " << tkn->instance << endl; 
	level = 0;  
	root = newNode("Program"); 
    head = scan.head; 
    tkn = scan.head; //First token 
    //cout << tkn->instance << " token " << endl;  
   root =  prog(tkn,root);
   /* if(tkn->tokenType == "EOFtk")
         cout << "parsing was a success" << endl;
    else {
        cout << "Parser error, expected EOFtkn" << endl;
     }*/
     return root; 

}
 
