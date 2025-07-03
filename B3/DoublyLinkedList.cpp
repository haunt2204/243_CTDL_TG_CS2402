#include <iostream>
using namespace std;

//Khai bao cau truc
struct Node
{
	int info;
	Node* next, * prev;
};

struct DoublyLinkedList {
	Node* head,* tail;
};

//Khoi tao rong
void init(DoublyLinkedList& l) {
	l.head = l.tail = NULL;
}

//Tim kiem
Node* search(DoublyLinkedList l, const int key) {
	Node* p = l.head;

	while (p != NULL && p->info != key) {
		p = p->next;
	}

	return p;
}

//Tim phan tu lon nhat, nho nhat trong danh sach
bool isMax(int a, int b) {
	return a > b;
}

bool isMin(int a, int b) {
	return a < b;
}

Node* findExtremum(DoublyLinkedList& l, bool func(int, int)=isMax) {
	if (l.head == NULL)
		return NULL;
	Node* res = l.head;
	Node* p = l.head->next;
	while (p != NULL) {
		if (func(p->info, res->info))
			res = p;
		p = p->next;
	}
	return res;
}
//Them dau, cuoi, sau node q
Node* createNode(int x) {
	Node* p = new Node;
	p->info = x;
	p->next = p->prev = NULL;
	return p;
}

void insertFirst(DoublyLinkedList& l, int x) {
	Node* p = createNode(x);

	if (l.head == NULL) {
		l.tail = p;
	}
	else {
		p->next = l.head;
		l.head->prev = p;
	}

	l.head = p;
}

void insertLast(DoublyLinkedList& l, int x) {
	Node* p = createNode(x);

	if (l.head == NULL) {
		l.head = p;
	}
	else {
		p->prev = l.tail;
		l.tail->next = p;
	}

	l.tail = p;
}

bool insertAfter(DoublyLinkedList& l, const int key, const int x) {
	Node* q = search(l, key);

	if (q == NULL)
		return false;

	if (q == l.tail) {
		insertLast(l, x);
		return true;
	}

	Node* p = createNode(x);

	p->next = q->next;
	q->next->prev = p;

	q->next = p;
	p->prev = q;

	return true;
}

//Xoa dau, cuoi, node q
void delFirst(DoublyLinkedList& l) {
	if (l.head == NULL)
		return;

	Node* p = l.head;

	l.head = l.head->next;
	if (l.head == NULL) {
		l.tail = NULL;
	}
	else {
		l.head->prev = NULL;
	}

	p->next = NULL;
	delete p;
}

void delLast(DoublyLinkedList& l) {
	if (l.head == NULL)
		return;

	Node* p = l.tail;

	l.tail = l.tail->prev;
	if (l.tail == NULL) {
		l.head = NULL;
	}
	else {
		l.tail->next = NULL;
	}

	p->prev = NULL;
	delete p;
}

bool delNode(DoublyLinkedList& l, int key) {
	Node* q = search(l, key);
	if (q == NULL)
		return false;

	if (q == l.head) {
		delFirst(l);
		return true;
	}

	if (q == l.tail) {
		delLast(l);
		return true;
	}

	Node* qPrev = q->prev;
	Node* qNext = q->next;

	qPrev->next = qNext;
	qNext->prev = qPrev;

	q->next = q->prev = nullptr;
	delete q;
	return true;
}

//Duyet
void printListFromHead(DoublyLinkedList l) {
	if (l.head == NULL) {
		cout << "DS rong!\n";
		return;
	}

	Node* p = l.head;
	while (p != NULL) {
		cout << p->info << " ";
		p = p->next;
	}
	cout << endl;
}

void printListFromTail(DoublyLinkedList l) {
	if (l.head == NULL) {
		cout << "DS rong!\n";
		return;
	}

	Node* p = l.tail;
	while (p != NULL) {
		cout << p->info << " ";
		p = p->prev;
	}
	cout << endl;
}

//Giai phong vung nho
void detroyList(DoublyLinkedList& l) {
	while (l.head != NULL) {
		delFirst(l);
	}
}

int main() {
	DoublyLinkedList l;
	init(l);

	insertLast(l, 1);
	insertLast(l, 6);
	insertLast(l, 4);
	insertLast(l, 2);
	insertLast(l, 3);

	delNode(l, 4);

	printListFromHead(l);
	printListFromTail(l);

	Node* res = findExtremum(l);
	if(res!=NULL)
		cout << res->info << endl;

	detroyList(l);
	printListFromHead(l);
	return 0;
}