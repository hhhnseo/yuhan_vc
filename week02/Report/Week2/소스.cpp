#include <iostream>
#include <conio.h>

using namespace std;

int main() {

	cout << "�������� �ູ�� VC++" << endl;
	
	char command = ' ';
	char input;
	char exitProgram;

	while (true) {

		cout << "command> ";
		
			while (true) {

				input = _getch();

				if (input == 13) {
					cout << endl;

					switch (command) {
						case 'q':
							cout << "qwer ȭ����" << endl;
							break;
						case 'w':
							cout << "���� �ʹ� ����" << endl;
							break;
						case 'e':
							cout << "���ֺ��� ������ 3���" << endl;
							break;
						case 'r':
							cout << "�ູ�մϴ�." << endl;
							break;
						default:
							cout << "����: �߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���" << endl;
							break;
					}
					break;
				}

				else {
					cout << input;
					command = input;
				}

				if (input == 27) {
					return 0;
				}
			}
		}
	
	return 0;
}
