#include <iostream>
#include <conio.h>

using namespace std;

int main() {

	cout << "장현서의 행복한 VC++" << endl;
	
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
							cout << "qwer 화이팅" << endl;
							break;
						case 'w':
							cout << "과제 너무 좋다" << endl;
							break;
						case 'e':
							cout << "담주부턴 과제량 3배다" << endl;
							break;
						case 'r':
							cout << "행복합니다." << endl;
							break;
						default:
							cout << "오류: 잘못된 입력입니다. 다시 입력하세요" << endl;
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
