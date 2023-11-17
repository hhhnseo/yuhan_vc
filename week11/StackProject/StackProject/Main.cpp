#include "yuhan_stack.h"
#include <iostream>

using namespace std;

int main() {
	stack myStack;

	cout << "스택이 비어있나?" << (myStack.isEmpty() ? "Yes" : "No") << endl;

	myStack.push(1);
	myStack.push(2);
	myStack.push(3);

	cout << "Top Stack: " << myStack.peek() << endl;

	cout << "Pop: " << myStack.pop() << endl;
	cout << "Pop: " << myStack.pop() << endl;

	cout << "스택이 비어있나?" << (myStack.isEmpty() ? "Yes" : "No") << endl;

	cout << "Top Stack: " << myStack.peek() << endl;

	return 0;
}