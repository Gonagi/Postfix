// ��ȣ �ִ� ���� ����ǥ��� --> ����ǥ��� ��ȯ
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
	while (Peek(Operator_stack) != '(') {	// �ݴ°�ȣ '('�� ���ö����� Pop
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
	while (n != NULL && n->data != 40)	// Operator_stack�� node�� �ϳ��ϳ� Ȯ���Ͽ� ���°�ȣ '('�� �ִ��� Ȯ��
		n = n->next;

	if (n == NULL)	// Operator_stack�� '('�� �ƴ� �����ڰ� �ϳ��� �ִ� ��� 
		return false;	
	else if (n->data == 40)	// Operator_stack�� '('�� �����ϴ� ���
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
		if ('0' <= token[0] && token[0] <= '9')	// token�� �ǿ������϶�
			Push(Operand_stack, atoi(token));
		else {	// token�� �������϶�
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
	if (Is_empty(Operator_stack) || token[0] == '(')	// ������ ������� �Ǵ� token�� '('�϶� Push
		Push(Operator_stack, token[0]);
	else {
		if ((Prec(Peek(Operator_stack)) > Prec(token[0]) || Is_bracket(Operator_stack)) && token[0] != ')') 
			// token�� �ݴ°�ȣ ')'�� �ƴϸ鼭 
			// ������ ������ �켱������ ��ū���� ���ų� ex) ����(+) > ��ū(*)
			// ���ÿ� ���°�ȣ '('�� �����Ҷ�																		
			Push(Operator_stack, token[0]);	// ���ÿ� * Push

		else {	// token�� �ݴ°�ȣ ')'�̰ų�
				// ������ ������ �켱������ ��ū���� ���ų� �����鼭 ex) ����(*) <= ��ū(*+)
				// ���ÿ� ���°�ȣ�� �������� ������
			if (token[0] == ')') 	// token�� �ݴ°�ȣ�϶�
				Push_with_Bracket(Postfix, Operator_stack);
			else {
				while (!Is_empty(Operator_stack) && Prec(Peek(Operator_stack)) <= Prec(token[0])) {	
					// ������ ������� ���� ��� && ���ÿ� �ִ� �������� �켱������ ��ū��  �켱�������� ������
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
		if ('0' <= token[0] && token[0] <= '9') {	// �����϶�
			strcat(Postfix, token);
			strcat(Postfix, " ");
		}
		else {	// �����϶�
			Make_operator_postfix(Postfix, Operator_stack, token);
		}
		token = strtok(NULL, " ");
	}
	while(!Is_empty(Operator_stack))	// ������ ������ �������� Pop
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
