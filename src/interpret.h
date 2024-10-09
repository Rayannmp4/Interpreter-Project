#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"

int get_result(Token *temp);

Token* add_token_number(Token *head, char num);

Token* add_token_operator(Token *head, char op);