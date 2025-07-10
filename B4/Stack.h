#include <iostream>
using namespace std;

#define MAX 50

struct Stack
{
	char* a[MAX];
	int top;
};


//Khoi tao rong
void init(Stack& s) {
	s.top = -1;
}

//Kiem tra rong
bool isEmpty(Stack s) {
	return s.top == -1;
}

bool isFull(Stack s) {
	return s.top == (MAX - 1);
}
//Them phan tu
void push(Stack& s, char* x) {
	if (!isFull(s))
		s.a[++s.top] = x;
}

//Lay phan tu ra
char* pop(Stack& s) {
	if (!isEmpty(s))
		return s.a[s.top--];

	return NULL;
}

//Lay ra xem
char* peek(Stack& s) {
	if (!isEmpty(s))
		return s.a[s.top];

	return NULL;
}