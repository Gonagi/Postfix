#include "postfix.h"
#include "stack.h"

void Make_operator_postfix(char* Postfix, char* token)
{
	if (Is_empty(Operator_stack))	// 스택이 비었을시
		Push(Operator_stack, token[0]);
	else {
		if(Prec(Peek(Operator_stack))
	}
}

int Prec(char Operator)
{
	switch (Operator) {
	case '+' : case '-' :
		return 1;
	case '*' : case '/' :
		return 2;
	}
}

char* Make_postfix(char* Infix)
{
	char Postfix[BUFFER_SIZE] = "\0";
	char* token = strtok(Infix, " ");

	while (token != NULL) {
		if ('0' <= token[0] && token[0] <= '9') {	// 숫자일때
			strcat(Postfix, token);
			strcat(Postfix, " ");
		}
		else {	// 문자일때
			Make_operator_postfix(Postfix, token);
		}
		token = strtok(NULL, " ");
	}

	return Postfix;
}

int read_line(FILE* fp, char str[], int num)
{
	int ch, i = 0;

	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
		if (i < num - 1)
			str[i++] = ch;
	str[i] = '\0';
	return i;
}
