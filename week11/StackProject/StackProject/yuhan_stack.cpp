#include "yuhan_stack.h"
#include <iostream>

node::node(int value) : data(value), prev_node(nullptr) {}

node* node::getPrevNode() const {
	return prev_node;
}

void node::setPrevNode(node* prev) {
	prev_node = prev;
}

int node::getData() const {
	return data;
}

stack::stack() : top(nullptr) {}

stack::~stack() {
	while (top != nullptr) {
		pop();
	}
}

void stack::push(int input) {
	node* newNode = new node(input);
	newNode->setPrevNode(top);
	top = newNode;
}

int stack::pop() {
	if (top == nullptr) {
		std::cerr << "Stack is empty" << std::endl;
		return -1;
	}

	int popValue = top->getData();
	node* tempNode = top;
	top = top->getPrevNode();
	delete tempNode;
	return popValue;
}

int stack::peek() const {
	if (top == nullptr) {
		std::cerr << "Stack is empty" << std::endl;
		return -1;
	}
	return top->getData();
}

bool stack::isEmpty() const {
	return top == nullptr;
}