#include "dStack.h"
#include <iostream>
using namespace std;

dStack::dStack(int a) {
	list = new char[a];
	size = a;
	top = -1; //-1 indicates empty stack
}

dStack::~dStack() {
	delete[] list;
}

void dStack::push(char a) {
	if (top == size) {
		return;
	} else {
		if (a != '\n') {
			top++;
			list[top] = a;
		}
	}
}
char dStack::pop() {
	if (top == -1) {
		return 0;
	} else {
		char a = list[top];
		top--;
		return a;
	}
}

bool dStack::isEmpty() {
	if (top == -1)
		return 1;
	else
		return 0;
}
