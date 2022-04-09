// 괄호 있는 최종 중위표기식 --> 후위표기식 변환
#include "postfix.h"
#include "stack.h"

struct node {
	Item data;
	Node next;
};

struct stack {
	Node top;
};

void Push_with_Bracket(char* Postfix, Stack Operator_stack)
{
	while (Peek(Operator_stack) != '(') {	// 닫는괄호 '('가 나올때까지 Pop
		switch (Pop(Operator_stack)) {
		case 42: strcat(Postfix, "*"); strcat(Postfix, " "); break;
		case 43: strcat(Postfix, "+"); strcat(Postfix, " "); break;
		case 45: strcat(Postfix, "-"); strcat(Postfix, " "); break;
		case 47: strcat(Postfix, "/"); strcat(Postfix, " "); break;
		}
	}
	Pop(Operator_stack);	// '(' Pop
	if (Is_empty(Operator_stack))
		Operator_stack = Create_stacK();
}

bool Is_bracket(Stack Operator_stack)
{
	Node n = Operator_stack->top;
	while (n != NULL && n->data != 40)	// Operator_stack의 node를 하나하나 확인하여 여는괄호 '('가 있는지 확인
		n = n->next;

	if (n == NULL)	// Operator_stack에 '('이 아닌 연산자가 하나만 있는 경우 
		return false;	
	else if (n->data == 40)	// Operator_stack에 '('가 존재하는 경우
		return true;
	else
		return false;
}

int Eval(char* Postfix)
{
	Stack Operand_stack = Create_stacK();
	char* token = strtok(Postfix, " ");
	int result, num1, num2;

	while (token != NULL) {
		if ('0' <= token[0] && token[0] <= '9')	// token이 피연산자일때
			Push(Operand_stack, atoi(token));
		else {	// token이 연산자일때
			num2 = Pop(Operand_stack);
			num1 = Pop(Operand_stack);

			switch (token[0]) {
			case 42: result = num1 * num2; break;
			case 43: result = num1 + num2; break;
			case 45: result = num1 - num2; break;
			case 47: result = num1 / num2; break;
			}
			if (Is_empty(Operand_stack))
				Operand_stack = Create_stacK();
			Push(Operand_stack, result);
		}
		token = strtok(NULL, " ");
	}	
	return Pop(Operand_stack);
}

void Make_operator_postfix(char* Postfix, Stack Operator_stack, char* token)
{
	if (Is_empty(Operator_stack) || token[0] == '(')	// 스택이 비었을시 또는 token이 '('일때 Push
		Push(Operator_stack, token[0]);
	else {
		if ((Prec(Peek(Operator_stack)) > Prec(token[0]) || Is_bracket(Operator_stack)) && token[0] != ')') 
			// token이 닫는괄호 ')'가 아니면서 
			// 스택의 연산자 우선순위가 토큰보다 낮거나 ex) 스택(+) > 토큰(*)
			// 스택에 여는괄호 '('가 존재할때																		
			Push(Operator_stack, token[0]);	// 스택에 * Push

		else {	// token이 닫는괄호 ')'이거나
				// 스택의 연산자 우선순위가 토큰보다 높거나 같으면서 ex) 스택(*) <= 토큰(*+)
				// 스택에 여는괄호가 존재하지 않을때
			if (token[0] == ')') 	// token이 닫는괄호일때
				Push_with_Bracket(Postfix, Operator_stack);
			else {
				while (!Is_empty(Operator_stack) && Prec(Peek(Operator_stack)) <= Prec(token[0])) {	
					// 스택이 비어있지 않은 경우 && 스택에 있는 연산자의 우선순위가 토큰의  우선순위보다 높을때
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
			}
		}
	}
}

int Prec(char Operator)
{
	switch (Operator) {
	case '(': case ')':
		return 0;
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
	while(!Is_empty(Operator_stack))	// 연산자 스택이 빌때까지 Pop
		switch (Pop(Operator_stack)) {
		case 42: strcat(Postfix, "*"); strcat(Postfix, " "); break;
		case 43: strcat(Postfix, "+"); strcat(Postfix, " "); break;
		case 45: strcat(Postfix, "-"); strcat(Postfix, " "); break;
		case 47: strcat(Postfix, "/"); strcat(Postfix, " "); break;
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
