// 괄호 있는 최종 중위표기식 --> 후위표기식 변환
#ifndef __POSTFIX_H__ 
#define __POSTFIX_H__ 

#endif
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "stack.h"
#define BUFFER_SIZE 100

static char Operator[] = "+-*/";

void Push_with_Bracket(char*, Stack);
bool Is_bracket(Stack);
int Eval(char*);
void Make_operator_postfix(char*, Stack, char*);
int Prec(char);
char* Make_postfix(char*);
int Eval(char*);
int read_line(FILE*, char[], int);