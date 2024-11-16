#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "types.h"

// initialiser les piles 
    Node * node_pile[100];
    char operator_pile[100];
    int nodeTop = -1,  opTop = -1;

Node* add_operator_node ( char operator) {
    Node* node = (Node*) malloc (sizeof(Node));
    node->content.operator = operator ; 
    node->isOperator = 1; 
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* add_value_node (int value) {
    Node* node = (Node*) malloc (sizeof(Node));
    node->content.value = value ;
    node->isOperator = 0; 
    node->left = NULL;
    node->right = NULL;
    return node;
}

void pushOperator ( char operator) {
        operator_pile[++opTop] = operator;
}

void pushNode ( Node * node) {
        node_pile[++nodeTop] = node ; 
}

Node * popNode () {
        return node_pile[nodeTop --]; 
}

char popOperator () {
        return operator_pile[opTop --]; 
}

void add_sub_tree () {
    char op = popOperator() ; 
    Node * operatorNode = add_operator_node(op);
    operatorNode->right = popNode(); 
    operatorNode->left = popNode();
    pushNode(operatorNode); 
}

int getPriority(char op) {
    switch (op) {
        case '+': 
        case '-': return 1;
        case '*': 
        case '/': return 2;
        default: return 0;
    }
}

Node * buildAST ( Token * operation) {   

    Node * root = NULL ; 

    while(operation) {
        if (operation->type == NUMBER || operation->type == TOKEN_VAR ) {
            // on crée un noeud pour nombre 
            Node * valueNode = add_value_node (operation->my_token.number);
            // on l'ajoute dans la pile des nombres
            pushNode(valueNode);
        } else if (operation->type == OPERATOR) {
            // on dépile les operateur d'une faible periorité 
            while (opTop >= 0 && operation->periorite <= getPriority(operator_pile[opTop])) {
                add_sub_tree();
            }
            pushOperator(operation->my_token.op);
        } else if (operation->type == OPEN_BRACKET) {
            pushOperator(operation->my_token.b_open);
        } else if (operation->type == CLOSE_BRACKET) {
            // parcourir jusqu'à la fin de l'opération entre ()
            while(opTop >= 0 && operator_pile[opTop] != '(') {
                add_sub_tree();
            }
            // enlever la (
            popOperator();
        }
        operation = operation->next ; 
    }
    
    // continuer avec les opérateurs restants 
    while(opTop >= 0) {
        add_sub_tree();
    }
    
    // récupérer la racine 
    root = popNode();
    return root ; 
}

int evaluateAST(Node* root) {
    if (!root) return 0;
    if (root->left == NULL && root->right == NULL) {
        printf("Evaluating leaf node: %d\n", root->content.value);
        return root->content.value;
    }

    int leftValue = evaluateAST(root->left);
    int rightValue = evaluateAST(root->right);

    int result = 0;
    switch (root->content.operator) {
        case '+': 
            result = leftValue + rightValue;
            break;
        case '-': 
            result = leftValue - rightValue;
            break;
        case '*': 
            result = leftValue * rightValue;
            break;
        case '/': 
            result = rightValue != 0 ? leftValue / rightValue : 0;  // Gestion de la division par zéro
            break;
    }
    printf("Evaluating %d %c %d = %d\n", leftValue, root->content.operator, rightValue, result);
    return result;
}

void freeAST(Node* root) {
    if (root == NULL) {
        return; // Rien à libérer si l'arbre est vide
    }

    // Libérer les sous-arbres gauche et droit
    freeAST(root->left);
    freeAST(root->right);

    // Libérer le nœud courant
    free(root);
    nodeTop = -1;
    opTop = -1 ; 
}


void printAST(Node *node, int niveau) {
    if (node != NULL) {
        
        if ( niveau == 0 ) {
            printf(" (AST) \n");
        }

        for (int i = 0 ; i < niveau ; i ++) {
            printf("   ");
        }

        // afficher le contenu du noeud  
        if (node->isOperator) {
            printf("N%d |_ %c \n", niveau, node->content.operator);
        } else {
            printf("N%d |_ %d \n", niveau, node->content.value);
        }

        // Afficher le sous-arbre gauche
        printAST(node->left, niveau + 1);

        // Afficher le sous-arbre droit
        printAST(node->right, niveau + 1);
    }
}



int parser (Token * operation ) {
   Node * AST = buildAST(operation); 
   int result = evaluateAST(AST);
   printAST(AST, 0);
   freeAST (AST); 
   return result ; 
}
