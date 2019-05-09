//Rachel Festervand 
//Project Translation 
//This is the header file for the nodes and where they are defined.
 
#ifndef NODE_H
#define NODE_H 
#include <string>
 
using namespace std;

struct Node {
   string  key;  
   struct Node *left; 
   struct Node *right;
   struct Node *center; 
   string id;
   string value;      
   int level; 
};  

#endif  
