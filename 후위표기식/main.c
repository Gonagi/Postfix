// ��ȣ �ִ� ���� ����ǥ��� --> ����ǥ��� ��ȯ
#include "postfix.h"
#include <stdio.h>

int main()
{
	char command[BUFFER_SIZE] = "\0";
	char Infix[BUFFER_SIZE] = "\0";
	char Postfix[BUFFER_SIZE] = "\0";

	while (1) {
		printf("���� �Է��ϼ���\n");
		printf("����ǥ��� : ");

		if (read_line(stdin, command, BUFFER_SIZE) > 0) {
			if (strcmp(command, "exit") == 0) {
				printf("����\n");
				break;
			}

			printf("Infix : %s\n", strcpy(Infix, command));
			printf("Postfix : %s\n", strcpy(Postfix, Make_postfix(Infix)));
			printf("Result : %d\n\n", Eval(Postfix));
			_CrtDumpMemoryLeaks();
		}
		else {
			printf("�ٽ��Է����ּ���.\n");
		}
	}

	return 0;
}