#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include "Queue.h"
#include <stack>
#include <iostream>
using namespace std;

//Chuyen tu he thap phan sang nhi phan
void convertDecToBin(int n) {
	stack<int> s;

	while (n != 0) {
		s.push(n%2);
		n = n / 2;
	}

	while (!s.empty()) {
		cout << s.top();
		s.pop();
	}
	cout << endl;
}

//Tinh gia tri bieu thuc
void calExp(char str[]) {
	stack<int> s;

	int a, b;

	char*p = strtok(str, " ");
	while (p != NULL) {
		if (isdigit(*p)) {
			s.push(atoi(p));
		}
		else {
			b = s.top();
			s.pop();
			a = s.top();
			s.pop();

			switch (*p)
			{
			case '+':
				s.push(a + b);
				break;
			case '-':
				s.push(a - b);
				break;
			case '*':
				s.push(a * b);
				break;
			case '/':
				if (b == 0) {
					cout << "Loi chia cho 0!\n";
					return;
				}
				s.push(a / b);
				break;
			default:
				break;
			}
		}

		p = strtok(NULL, " ");
	}
	
	cout << "Ket qua tinh: " << s.top() << endl;
}

int getPriority(string op) {
	if (op == "/" || op == "*")
		return 2;
	if (op == "+" || op == "-")
		return 1;
	return 0;
}

char* infixToPostfix(char str[]) {
	Queue postfix;
	init(postfix);

	Stack s;
	init(s);

	char*p = strtok(str, " ");
	while (p != NULL) {

		if (isdigit(*p)) {
			enQueue(postfix, p);
		}
		else if (*p == '(') {
			push(s, p);
		}
		else if (*p == ')') {
			char* op = pop(s);
			while (*op != '(') {
				enQueue(postfix, op);
				op = pop(s);
			}
		}
		else {
			while (!isEmpty(s)&&getPriority(p)<=getPriority(peek(s))) {
				char* op = pop(s);
				enQueue(postfix, op);
			}
			push(s, p);
		}

		p = strtok(NULL, " ");
	}

	while (!isEmpty(s)) {
		enQueue(postfix, pop(s));
	}

	char* res = new char[strlen(str)];
	res[0] = '\0';
	while (!isEmpty(postfix)) {
		strcat(res, deQueue(postfix));
		if(!isEmpty(postfix))
			strcat(res, " ");
	}
	cout << res <<endl;
	return res;
}

int main() {
	//convertDecToBin(4);

	char str[] = "2 + 4 - ( 5 - 3 ) / 2 + 3 - 1 * 5";
	char *res = infixToPostfix(str);
	calExp(res);

	return 0;
}