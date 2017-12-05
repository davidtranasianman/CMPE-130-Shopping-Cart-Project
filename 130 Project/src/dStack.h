#ifndef DSTACK_H_
#define DSTACK_H_

class dStack {
private:
	int size;
	int top;
	char* list;

public:
	dStack(int = 100);
	~dStack();
	void push(char);
	char pop();
	bool isEmpty();
};



#endif /* DSTACK_H_ */
