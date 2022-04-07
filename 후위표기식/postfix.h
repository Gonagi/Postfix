#ifndef __POSTFIX_H__ 
#define __POSTFIX_H__ 

#endif
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#define BUFFER_SIZE 100

static char Operator[] = "+-*/";

void Make_operator_postfix(char*, Stack, char*);
int Prec(char);
char* Make_postfix(char*);
int Eval(char*);
int read_line(FILE*, char[], int);