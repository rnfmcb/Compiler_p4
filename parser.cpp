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
        //scanner.print();
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

    //cout << "token in RO" << tkn->instance << endl;

   	if(tkn->instance == "<" ) {
	  tree->operate = tkn->instance;

	}
    else if (tkn->instance == ">"){
		 tree->operate = tkn->instance;
    }

    else if (tkn->instance == "="){
		*&tkn = getToken(tkn);
	//	cout << "token after equals" << tkn->instance << endl;
		if (tkn->instance == ">" | tkn->instance == "<" | tkn->instance == "="){
            string operators = "= " + tkn->instance;
            tree->operate = operators;
            *&tkn = getToken(tkn);
		}
	}
   else {
    cout << "Error: expected an operator camparison, got " << tkn->instance;
   }
}


void Parser::expr(Token *&tkn, Node *&tree){
    //<expr>-><A> + <expr> | <A> - <expr> | <A>
    if( tkn->tokenType == "intNumTkn" | tkn->tokenType == "IDTkn"){
        tree->center = new Node;
        tree->center = newNode("A");
        tree->center->id = tkn->tokenType;
        tree->center->value = tkn->instance;
        *&tkn = getToken(tkn);
         if(tkn->instance == "["){
                tree->center->center = new Node;
                tree->center->center = newNode("expr");
                tree->center->center->id = tkn->tokenType;
                tree->center->center->value = tkn->instance;
                tree->center->center->operate = "[";
                *&tkn = getToken(tkn);
                expr(tkn,tree->center->center);
         }
         else if(tkn->instance == "+" | tkn->instance == "-"){
            tree->center->operate = tkn->instance;
            tree->left = new Node;
            tree->left = newNode("expr");
            tree->left->id = tkn->tokenType;
            tree->left->value = tkn->instance;
            expr(tkn,tree->left);
         }
        //<A>-> <N> * <A> | <N>
        else if(tkn->instance == "*"){
            tree->center->left = new Node;
            tree->center->left = newNode("N");
            tree->center->left->id = tkn->tokenType;
            tree->center->left->value = tkn->instance;
            tree->center->left->operate = "*";
            *&tkn = getToken(tkn);
            expr(tkn,tree->center->center);
        }
        else if (tkn->instance == "/"){
            tree->center->center = new Node;
            tree->center->center = newNode("N");
            tree->center->center->id = tkn->tokenType;
            tree->center->center->value = tkn->instance;
            tree->center->center->operate = "/";

            tree->center->center->center = new Node;
            tree->center->center->center = newNode("M");
            tree->center->center->center->id = tkn->tokenType;
            tree->center->center->center->value = tkn->instance;
            tree->center->center->center = new Node;
             *&tkn = getToken(tkn);
            tree->center->center->left = newNode("N");
            tree->center->center->left->id = tkn->tokenType;
            tree->center->center->left->value = tkn->instance;
            *&tkn = getToken(tkn);
            if(tkn->instance == "["){
                tree->center->center->left->center = newNode("expr");
                tree->center->center->left->center->id = tkn->tokenType;
                tree->center->center->left->center->value = tkn->instance;
                tree->center->center->left->center->operate = "[";
                *&tkn = getToken(tkn);
                expr(tkn,tree->center->center->left->center);
            }

        }

        else{
            return;
        }
    }
    //Negative number
    else if(tkn->instance == "-"){
        tree->operate = "- ";
        *&tkn = getToken(tkn);
        expr(tkn,tree);

    }
    else{
      //  cout << "got this in expr" << tkn->instance << endl;
    }

}


void Parser::mstat(Token *&tkn, Node *&tree){
	addLevel();
	*&tkn = getToken(tkn);
	//cout << tkn->instance << endl;
	if(tkn->instance == "Read" | tkn->instance == "Output"  |
       tkn->instance == "IFF" | tkn->instance == "Loop" |
       tkn->tokenType == "IDTkn" | tkn->instance == "Begin") {
       tree->left = new Node;
	   tree->left = newNode("stat");
	   stat(tkn,tree->left);
	   *&tkn = getToken(tkn);
	  // cout << tkn->instance << endl;
	   if(tkn->instance == "End"){
	       *&tkn = getToken(tkn);
           if(tkn->instance == ":"){
                tree->right = new Node;
                tree->right = newNode("mstat");
                tree->right->id = tkn->tokenType;
                tree->right->value = tkn->instance;
                mstat(tkn,tree->right);
			}
		}
		else if (tkn->instance == ":"){
		    tree->right = new Node;
            tree->right = newNode("mstat");
            tree->right->id = tkn->tokenType;
            tree->right->value = tkn->instance;
            mstat(tkn,tree->right);
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

	if(tkn->instance == "Output"){
		tree->center  = new Node;
		tree->center = newNode("out");
		*&tkn = getToken(tkn);
		if(tkn->instance == "["){
			*&tkn = getToken(tkn);
		    tree->center->center = new Node;
			tree->center->center = newNode("expr");
            tree->center->center->id = tkn->tokenType;
            tree->center->center->value = tkn->instance;
            expr(tkn,tree->center->center);
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
				data = tkn->tokenType ;
				value = tkn->instance;
				//cout << tkn->instance << tkn->tokenType << endl;
				tkn = getToken(tkn);
               // cout << tkn->instance << endl;
					if(tkn->instance == "]"){
						tree->center = new Node;
						tree->center = newNode("in");
					    tree->center->id = data;
						tree->center->value = value;

					}
                    else {
					//	cout << "Parser error: expected ], recieved ";
					//	cout << endl;
					//	exit(EXIT_FAILURE);
				 	 }
			 }
              else {
			     // cout << "Parser error: expected indetifier, recieved ";
				 // cout << tkn->tokenType << endl;
				 // exit(EXIT_FAILURE);
			  }
           }
		   else {
		       //cout << "Parser error: expected [ recieved ";
			   //cout << endl;
			   //exit(EXIT_FAILURE);
		    }

    }
	else if(tkn->instance == "Begin"){
		tree->center = new Node;
		tree->center = newNode("block");
		tree->center->left = new Node;
		tree->center->left = newNode("vars");
		tree->center->left->id = tkn->tokenType;
		tree->center->left->value = tkn->instance;
		*&tkn = getToken(tkn);
		//cout << tkn->instance << "begin" << endl;
		if(tkn->instance == "INT"){
            vars(tree);

		}
		tree->center->right = new Node;
		tree->center->right = newNode("stats");
		tree->center->right->left = new Node;
		tree->center->right->left = newNode("stat");
		//cout << "value in begin" << tkn->instance << endl;
		tree->center->right->left->id = tkn->tokenType;
		tree->center->right->left->value = tkn->instance;
		stat(tkn,tree->center->right->left);

	}

	else if(tkn->instance == "IFF"){
 	 	tree->center = new Node;
		tree->center = newNode("IF");
		*&tkn = getToken(tkn);
		if(tkn->instance == "[") {
		    tkn = getToken(tkn);
			tree->center->left = new Node;
			tree->center->left = newNode("expr");
			tree->center->left->id = tkn->tokenType;
			tree->center->left->value = tkn->instance;
			expr(tkn, tree->center->left);
			//cout << "tkn after expr" << tkn->instance << endl;
			RO(tkn,tree->center);
			tree->center->center = new Node;
			tree->center->center = newNode("expr");
			tree->center->center->id = tkn->tokenType;
			tree->center->center->value = tkn->instance;
			expr(tkn, tree->center->center);
			//cout << tkn->instance << "in expr" << endl;
			if(tkn->instance == "]"){
				tree->center->right = new Node;
				tree->center->right = newNode("stat");
				tree->center->right->id = tkn->tokenType;
				tree->center->right->value = tkn->instance;
                *&tkn = getToken(tkn);
				stat(tkn,tree->center->right);
			}
			else{
			//	cout << "parser error in IFF: expected ], recieved ";
			//	cout << tkn->instance << endl;
			//	exit(EXIT_FAILURE);
			}
		}
		else{
			//cout << "Parser error in Iff: Expected [, recieved ";
			//cout << tkn->instance << endl;
			//exit(EXIT_FAILURE);
		}

	}
    else if(tkn->instance == "Loop"){
 	 	tree->center = new Node;
		tree->center = newNode("Loop");
		*&tkn = getToken(tkn);
		if(tkn->instance == "[") {
		    tkn = getToken(tkn);
			tree->center->left = new Node;
			tree->center->left = newNode("expr");
			tree->center->left->id = tkn->tokenType;
			tree->center->left->value = tkn->instance;
			expr(tkn, tree->center->left);
			//cout << "tkn after expr" << tkn->instance << endl;
			RO(tkn,tree->center);
			tree->center->center = new Node;
			tree->center->center = newNode("expr");
			tree->center->center->id = tkn->tokenType;
			tree->center->center->value = tkn->instance;
			expr(tkn, tree->center->center);
			//cout << tkn->instance << "in expr" << endl;
			if(tkn->instance == "]"){
				tree->center->right = new Node;
				tree->center->right = newNode("stat");
				tree->center->right->id = tkn->tokenType;
				tree->center->right->value = tkn->instance;
                *&tkn = getToken(tkn);
				stat(tkn,tree->center->right);
			}
			else{
				//cout << "parser error in Loop: expected ], recieved ";
			//	cout << tkn->instance << endl;
			//	exit(EXIT_FAILURE);
			}
		}
		else{
			//cout << "Parser error in Loop: Expected [, recieved ";
			//cout << tkn->instance << endl;
			//exit(EXIT_FAILURE);
		}

	}
	else if (tkn->tokenType == "IDTkn"){
		string value = tkn->instance;
		string id = tkn->tokenType;
		*&tkn = getToken(tkn);
		if(tkn->instance == "="){
			tree->center = new Node;
			tree->center = newNode("assign");
 			tree->center->id = id;
 			tree->center->value = value;
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
     if (tkn->instance == "Begin"){
		setLevel(1);
        tree->right = new Node;
		tree->right = newNode("Block");
        tkn = getToken(tkn);
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
		   *&tkn = getToken(tkn);
		   //cout<<tkn->instance << endl;
           if(tkn->instance == ":") {
              tree->right->right->right = new Node;
              tree->right->right->right = newNode("mstat");
			  mstat(tkn,tree->right->right->right);
			 // cout << tkn->instance << endl;
					if(tkn->instance == "Read" | tkn->instance == "Output"  |
   					    tkn->instance == "IFF" | tkn->instance == "Loop" |
       					tkn->tokenType == "IDTkn" | tkn->instance == "Begin") {
       					tree->right->right->right->left = new Node;
						tree->right->right->right->left = newNode("stat");
						stat(tkn,tree->right->right->right->left);
					 	*&tkn = getToken(tkn);
					}
                    else if(tkn->instance == "End"){
                        *&tkn = getToken(tkn);
                    }
                    else{
                       // cout << "Parser error in begin: expected end token, received ";
                       // cout <<tkn->instance << endl;
                       // exit(EXIT_FAILURE);
                    }

			}
			else{
				 cout << "Parser error in begin, expected : ";
				 cout << "received " << tkn->instance;
				 exit(EXIT_FAILURE);
			   }

	       }

}

//Vars empty| INT Identifier Integer <vars>
void Parser::vars( Node *&tree){
   addLevel();
   string id;
   string num;
   Token *tkn1 = getToken(tkn);
   Token *tkn2 = getToken(tkn1);
   id = tkn1->instance;
   num = tkn2->instance;
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
	if(tkn->instance == "INT"){
		vars(tree->left);
	}
}



//Starts here <vars><block>
Node* Parser::prog(Token *&tkn, Node *&tree){
	Token *temp = tkn;
    //Vars
    if(tkn->instance == "INT"){
        vars(tree);

    }
    //<Block>
    if (tkn->instance == "Begin"){
        begin(tkn,tree);
    }

    else{ //Error
        cout << "Parser error in program: Expected begin or INT, recieved ";
        cout << tkn->instance << endl;
		exit(EXIT_FAILURE);
     }

 return tree;
}


Node*  Parser::parse (ifstream &infile,string filename){
    Scanner scan;
    root = NULL;
	branch = NULL;
	varNum = 0;
    FADriver(infile,filename,scan);
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

