#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <iostream>

int main() {

	printf("\t202207032\n");
	printf("\t����������\n");
	printf("\tApplicpation\n");

	char alpha;

	printf("command>");

	while (1) {

		scanf("%c", &alpha);

		if (alpha == 'p') {
			printf("���� ������ �̳� ���ϴ� �л��̴�");
		}
		else if (alpha == 'f') {
			printf("���� ������ �ʹ� ��̴�");
		}
		else if (alpha == 'j') {
			printf("������ ���� �� ���ּ���");
		}
		else if (alpha == 'esc') {
			printf("����");
			break;
		}
		else {
			printf("�߸��� Ű�� �Է��ϼ̽��ϴ�.");
		}

		printf("command>");
			
	}

	
	return 0;
	

	
}