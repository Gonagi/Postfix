// ��ȣ ���� ����ǥ��� --> ����ǥ��� ��ȯ
#include "postfix.h"
#include "stack.h"

void Make_operator_postfix(char* Postfix, Stack Operator_stack, char* token)
{
	if (Is_empty(Operator_stack))	// ������ �������
		Push(Operator_stack, token[0]);
	else {
		if (Prec(Peek(Operator_stack)) > Prec(token[0]))		// ����(+) > ��ū(*)
			Push(Operator_stack, token[0]);	// ���ÿ� * Push
		else {	// ����(*) <= ��ū(*+)
			while (!Is_empty(Operator_stack) && Prec(Peek(Operator_stack)) <= Prec(token[0])) {	// ������ ������� ���� ��� && \
																*				+				���ÿ� �ִ� �������� �켱������ ������
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
		if ('0' <= token[0] && token[0] <= '9') {	// �����϶�
			strcat(Postfix, token);
			strcat(Postfix, " ");
		}
		else {	// �����϶�
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
