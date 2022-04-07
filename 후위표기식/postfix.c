// 괄호 없는 중위표기식 --> 후위표기식 변환
#include "postfix.h"
#include "stack.h"

void Make_operator_postfix(char* Postfix, Stack Operator_stack, char* token)
{
	if (Is_empty(Operator_stack))	// 스택이 비었을시
		Push(Operator_stack, token[0]);
	else {
		if (Prec(Peek(Operator_stack)) > Prec(token[0]))		// 스택(+) > 토큰(*)
			Push(Operator_stack, token[0]);	// 스택에 * Push
		else {	// 스택(*) <= 토큰(*+)
			while (!Is_empty(Operator_stack) && Prec(Peek(Operator_stack)) <= Prec(token[0])) {	// 스택이 비어있지 않은 경우 && \
																*				+				스택에 있는 연산자의 우선순위가 높을시
				switch (Pop(Operator_stack)) {
				case 42: strcat(Postfix, "*"); strcat(Postfix, " "); break;
				case 43: strcat(Postfix, "+"); strcat(Postfix, " "); break;
				case 45: strcat(Postfix, "-"); strcat(Postfix, " "); break;
				case 47: strcat(Postfix, "/"); strcat(Postfix, " "); break;
				}
				if (Is_empty(Operator_stack))
					Operator_stack = Create_stacK();
			}
			Push(Operator_stack, token[0]);
			
			if (Is_empty(Operator_stack))
				Operator_stack = Create_stacK();
		}
	}
}

int Prec(char Operator)
{
	switch (Operator) {
	case '*': case '/':
		return 1;
	case '+' : case '-' :
		return 2;

	}
}

char* Make_postfix(char* Infix)
{
	char Postfix[BUFFER_SIZE] = "\0";
	char* token = strtok(Infix, " ");
	Stack Operator_stack = Create_stacK();

	while (token != NULL) {
		if ('0' <= token[0] && token[0] <= '9') {	// 숫자일때
			strcat(Postfix, token);
			strcat(Postfix, " ");
		}
		else {	// 문자일때
			Make_operator_postfix(Postfix, Operator_stack, token);
		}
		token = strtok(NULL, " ");
	}
	while(!Is_empty(Operator_stack))
		switch (Pop(Operator_stack)) {
		case 42: strcat(Postfix, "*"); strcat(Postfix, " "); break;
		case 43: strcat(Postfix, "+"); strcat(Postfix, " "); break;
		case 45: strcat(Postfix, "-"); strcat(Postfix, " "); break;
		case 47: strcat(Postfix, "/"); strcat(Postfix, " "); break;
		}
	//if (Is_empty(Operator_stack))
	//	Operator_stack = Create_stacK();
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
