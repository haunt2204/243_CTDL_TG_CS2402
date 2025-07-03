#include <iostream>
using namespace std;

//Khai bao cau truc
struct Node
{
	int info;
	Node* next;
};

struct CircularLinkedList {
	Node* head, * tail;
};

void init(CircularLinkedList& l) {
	l.head = l.tail = NULL;
}

Node* createNode(int x) {
	Node* p = new Node;
	p->info = x;
	p->next = NULL;

	return p;
}

void insertFirst(CircularLinkedList& l, int x) {
	Node* p = createNode(x);
	if (l.head == NULL) {
		p->next = p;
		l.head = l.tail = p;
	}
	else {
		p->next = l.head;
		l.head = p;
		l.tail->next = l.head;
	}
}

void printList(CircularLinkedList l) {
	if (l.head == NULL) {
		cout << "DS rong!\n";
		return;
	}

	Node* p = l.head;

	while (p->next != l.head) {
		cout << p->info << " ";
		p = p->next;
	}

	cout << p->info << endl;
}

void delFirst(CircularLinkedList& l) {
	if (l.head == NULL)
		return;

	Node* p = l.head;

	l.head = l.head->next;

	if (l.head == p) {
		l.head = l.tail = NULL;
	}
	else {
		l.tail->next = l.head;
	}

	p->next = NULL;
	delete p;
}


void detroyList(CircularLinkedList &l) {
	while (l.head != NULL) {
		delFirst(l);
	}
}

int main() {
	CircularLinkedList l;
	init(l);

	insertFirst(l, 1);
	insertFirst(l, 3);
	insertFirst(l, 5);
	insertFirst(l, 4);

	printList(l);

	detroyList(l);
	printList(l);
	return 0;
}