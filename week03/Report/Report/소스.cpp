#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

using namespace std;

// ���� �迭 �ʱ�ȭ
void reset(int array[], int x)
{
    for (int i = 0; i < x; i++) {
        array[i] = 0;
    }
}

int main()
{
    char input = ' '; // ����ڿ��� �Է� ����
    int result[100] = {}; // �Է¹��� ���ڸ� ������ �迭
    int index = 0; // �迭�� �Էµ� ���� ��


    while (input != 27) {
        // ���� �迭�� �� �� ��� ���α׷� ����

        if (index > 92) {
            break;
        }
        else if (index >= 5) {

            for (int i = 0; i < index; i++) {
                // LEFT RIGHT 'p'
                if ((result[i] == -32 && result[i + 1] == 3) &&
                    (result[i + 2] == -32 && result[i + 3] == 4) &&
                    ((char)(result[i + 4] == 'p'))) {
                    cout << "���� ű" << endl;
                    reset(result, index);
                    index = 0;
                }

                // RIGHT DOWN RIGHT 'p'
                if ((result[i] == -32 && result[i + 1] == 4) &&
                    (result[i + 2] == -32 && result[i + 3] == 2) &&
                    (result[i + 4] == -32 && result[i + 5] == 4) &&
                    ((char)(result[i + 6] == 'p'))) {
                    cout << "��Ƽ�� �Ѹ�" << endl;
                    reset(result, index);
                    index = 0;
                }

                // UP RIGHT DOWN RIGHT 'p'
                if ((result[i] == -32 && result[i + 1] == 1) &&
                    (result[i + 2] == -32 && result[i + 3] == 4) &&
                    (result[i + 4] == -32 && result[i + 5] == 2) &&
                    (result[i + 6] == -32 && result[i + 7] == 2) &&
                    ((char)(result[i + 8] == 'p'))) {
                    cout << "�����޺�" << endl;
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
				printf("\b�� ");
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
				printf("\b�� ");
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
				printf("\b�� ");
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
				printf("\b�� ");
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