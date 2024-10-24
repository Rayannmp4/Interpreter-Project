#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "interpret.h"

int main () {
   interpret("a = 1 + 4 "); 
   interpret("a = 4 * 5 "); 
   interpret("a = 1 - 4 * 5"); 
}
