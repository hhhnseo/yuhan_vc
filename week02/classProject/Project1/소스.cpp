#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <iostream>

int main() {

	printf("\t202207032\n");
	printf("\t장현서님의\n");
	printf("\tApplicpation\n");

	char alpha;

	printf("command>");

	while (1) {

		scanf("%c", &alpha);

		if (alpha == 'p') {
			printf("나는 과제를 겁나 잘하는 학생이다");
		}
		else if (alpha == 'f') {
			printf("나는 과제가 너무 즐겁다");
		}
		else if (alpha == 'j') {
			printf("교수님 과제 더 내주세요");
		}
		else if (alpha == 'esc') {
			printf("종료");
			break;
		}
		else {
			printf("잘못된 키를 입력하셨습니다.");
		}

		printf("command>");
			
	}

	
	return 0;
	

	
}