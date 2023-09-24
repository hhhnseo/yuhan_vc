#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

using namespace std;

// 문자 배열 초기화
void reset(int array[], int x)
{
    for (int i = 0; i < x; i++) {
        array[i] = 0;
    }
}

int main()
{
    char input = ' '; // 사용자에게 입력 받음
    int result[100] = {}; // 입력받은 문자를 저장할 배열
    int index = 0; // 배열의 입력된 문자 수


    while (input != 27) {
        // 문자 배열이 꽉 찬 경우 프로그램 종료

        if (index > 92) {
            break;
        }
        else if (index >= 5) {

            for (int i = 0; i < index; i++) {
                // LEFT RIGHT 'p'
                if ((result[i] == -32 && result[i + 1] == 3) &&
                    (result[i + 2] == -32 && result[i + 3] == 4) &&
                    ((char)(result[i + 4] == 'p'))) {
                    cout << "더블 킥" << endl;
                    reset(result, index);
                    index = 0;
                }

                // RIGHT DOWN RIGHT 'p'
                if ((result[i] == -32 && result[i + 1] == 4) &&
                    (result[i + 2] == -32 && result[i + 3] == 2) &&
                    (result[i + 4] == -32 && result[i + 5] == 4) &&
                    ((char)(result[i + 6] == 'p'))) {
                    cout << "버티컬 롤링" << endl;
                    reset(result, index);
                    index = 0;
                }

                // UP RIGHT DOWN RIGHT 'p'
                if ((result[i] == -32 && result[i + 1] == 1) &&
                    (result[i + 2] == -32 && result[i + 3] == 4) &&
                    (result[i + 4] == -32 && result[i + 5] == 2) &&
                    (result[i + 6] == -32 && result[i + 7] == 2) &&
                    ((char)(result[i + 8] == 'p'))) {
                    cout << "슈퍼콤보" << endl;
                    reset(result, index);
                    index = 0;
                }

            }
        }

        input = _getch();
        
        switch (input)
        {
		case UP:
			if (result[index - 1] == -32) {
				printf("\b↑ ");
				result[index] = 1;
			}
			else {
				cout << input;
				result[index] = input;
			}
			index++;
			break;

		case DOWN:
			if (result[index - 1] == -32) {
				printf("\b↓ ");
				result[index] = 2;
			}
			else {
				cout << input;
				result[index] = input;
			}
			index++;
			break;
		case LEFT:
			if (result[index - 1] == -32) {
				printf("\b← ");
				result[index] = 3;
			}
			else {
				cout << input;
				result[index] = input;
			}
			index++;
			break;

		case RIGHT:
			if (result[index - 1] == -32) {
				printf("\b→ ");
				result[index] = 4;
			}
			else {
				cout << input;
				result[index] = input;
			}
			index++;
			break;

		default:
			if (input != 32) {
				printf("%c ", input);
				result[index] = input;
			}
			else {
				result[index] = input;
			}
			index++;
			break;
        }

        Sleep(300);
    }
}