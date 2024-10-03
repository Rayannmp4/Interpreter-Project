#ifndef TYPES
#define TYPES 

typedef enum {
   NUMBER , 
   OPERATOR , 
   OPEN_BRACKET , 
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
   } my_token; 
   int periorite ; 
   Token *next ; 
}; 

#endif