// 괄호 있는 최종 중위표기식 --> 후위표기식 변환
#include "postfix.h"
#include <stdio.h>

int main()
{
	char command[BUFFER_SIZE] = "\0";
	char Infix[BUFFER_SIZE] = "\0";
	char Postfix[BUFFER_SIZE] = "\0";

	while (1) {
		printf("식을 입력하세요\n");
		printf("중위표기식 : ");

		if (read_line(stdin, command, BUFFER_SIZE) > 0) {
			if (strcmp(command, "exit") == 0) {
				printf("종료\n");
				break;
			}

			printf("Infix : %s\n", strcpy(Infix, command));
			printf("Postfix : %s\n", strcpy(Postfix, Make_postfix(Infix)));
			printf("Result : %d\n\n", Eval(Postfix));
			_CrtDumpMemoryLeaks();
		}
		else {
			printf("다시입력해주세요.\n");
		}
	}

	return 0;
}