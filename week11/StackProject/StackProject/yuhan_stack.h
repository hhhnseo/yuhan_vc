#pragma once
#ifndef Y_STACK_H
#define Y_STACK_H

#include <iostream>

class node {
private:
	int data;
	node* prev_node;

public:
	node(int value);
	node* getPrevNode() const;
	void setPrevNode(node* prev);
	int getData() const;
};

class stack {
	node* top;

public:
	stack();
	~stack();

	void push(int input);
	int pop();
	int peek() const;
	bool isEmpty() const;
};

#endif