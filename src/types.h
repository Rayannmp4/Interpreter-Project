#ifndef TYPES
#define TYPES 

typedef enum {
   NUMBER , 
   OPERATOR , 
   OPEN_BRACKET , 
   TOKEN_VAR, 
   CLOSE_BRACKET  
} char_type ;

typedef struct Token Token ; 

struct Token {
   char_type type ; 
   union {
   int number ; 
   char op ; 
   char b_open ; 
   char b_close ;
   char name[20];
   char var_name[20]; 
   // char type;
   } my_token; 
   int periorite ; 
   struct Token *next ; 
}; 

// Structure pour stocker la variable + sa valaur 
typedef struct{
   char name[20];
   int value;
} Variable;

// AST struct 
typedef struct Node{
   union {
   char operator;
   int value; 
   } content;
   struct Node * left;
   struct Node * right;
} Node;

#endif