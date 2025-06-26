#include <iostream>
#include <string>
#include <fstream>
using namespace std;


//Sinh vien
struct Term {
	float coef;//he so
	float exp;//Bac
};

//Nhap 1 sinh vien
void nhap1Term(Term& t) {
	cout << "Nhap he so: ";
	cin >> t.coef;

	cout << "Nhap bac: ";
	cin >> t.exp;
}

void xuat1Term(Term t) {
	cout << t.coef << "x^" << t.exp;
}

//Khai bao cau truc
struct Node {
	//Vung thong tin
	Term info;

	//Vung lien ket
	Node* next;
};

struct LinkedList {
	Node* head, * tail;
};

//Thao tac khoi tao rong
void init(LinkedList& l) {
	l.head = l.tail = NULL;
}
//Them phan tu vao dau danh sach
Node* createNode(Term sv) {
	Node* p = new Node;
	p->info = sv;
	p->next = NULL;
	return p;
}

void insertFirst(LinkedList& l, Term t) {
	Node* p = createNode(t);

	if (l.head == NULL) {
		l.head = l.tail = p;
		return;
	}

	p->next = l.head;
	l.head = p;
}

//Them vao cuoi
void insertLast(LinkedList& l, Term t) {
	Node* p = createNode(t);

	if (l.head == NULL) {
		l.head = l.tail = p;
		return;
	}

	l.tail->next = p;
	l.tail = p;
}

//Tim kiem
Node* search(LinkedList l, float key) {
	Node* p = l.head;

	while (p != NULL && p->info.exp != key) {
		p = p->next;
	}

	return p;
}

//Them sau node q
bool insertAfter(LinkedList& l, int id, Term t) {
	Node* q = search(l, id);
	if (q == NULL)
		return false;

	Node* p = createNode(t);
	p->next = q->next;

	if (q->next == NULL)
		l.tail = p;

	q->next = p;
}

void insertOrdered(LinkedList& l, Term t) {
	if (l.head == NULL || l.head->info.exp < t.exp) {
		insertFirst(l, t);
		return;
	}

	Node* p = createNode(t);
	Node* q = l.head;

	while (q->next != NULL && q->next->info.exp >= t.exp) {
		q = q->next;
	}

	if (q->info.exp == t.exp) {
		q->info.coef = t.coef;
		return;
	}

	if (q == l.tail) {
		insertLast(l, t);
		return;
	}

	p->next = q->next;
	q->next = p;
}
//Duyet danh danh sach
void printList(LinkedList l) {
	if (l.head == NULL) {
		cout << "DS rong!\n";
		return;
	}
	Node* p = l.head;
	cout << "f(x) = ";
	while (p != NULL) {
		//cout << p->info;
		xuat1Term(p->info);
		if(p->next!=NULL)
			cout << " + ";
		p = p->next;
	}
}


//Thao tac xoa: dau, cuoi, node q
void delFirst(LinkedList& l) {
	if (l.head == NULL) {
		cout << "Danh sach rong!\n";
		return;
	}

	Node* p = l.head;

	if (l.head == l.tail)
		l.tail = NULL;

	l.head = l.head->next;

	p->next = NULL;
	delete p;
}

void delLast(LinkedList& l) {
	if (l.head == NULL) {
		cout << "Danh sach rong!\n";
		return;
	}

	Node* pLast = l.tail;

	if (l.head == l.tail) {
		l.head = l.tail = NULL;
		delete pLast;
		return;
	}

	Node* prevLast = l.head;
	while (prevLast->next != l.tail) {
		prevLast = prevLast->next;
	}

	prevLast->next = NULL;
	l.tail = prevLast;

	delete pLast;
}

void delNode(LinkedList& l, int key) {
	Node* q = search(l, key);

	if (q == NULL) {
		cout << "Khong tim thay!\n";
		return;
	}

	if (q == l.head) {
		delFirst(l);
		return;
	}

	if (q == l.tail) {
		delLast(l);
		return;
	}

	Node* qPrev = l.head;
	while (qPrev->next != q) {
		qPrev = qPrev->next;
	}

	qPrev->next = q->next;

	q->next = NULL;
	delete q;
}

//Giai phong vung nho
void detroyList(LinkedList& l) {
	while (l.head != NULL) {
		delLast(l);
	}
}
//Sap xep
void sort(LinkedList l) {
	if (l.head == NULL)
		return;
	for (Node* i = l.head; i->next != NULL; i = i->next) {
		for (Node* j = i->next; j != NULL; j = j->next) {
			if (j->info.exp < i->info.exp) {
				swap(i->info, j->info);
			}
		}
	}
}

//Tinh gia tri cua f(x)

int main() {
	LinkedList l;
	init(l);

	Term t1, t2, t3, t4;

	t1.coef = 2;
	t1.exp = 3;
	insertOrdered(l, t1);

	t2.coef = 3;
	t2.exp = 2;
	insertOrdered(l, t2);

	t3.coef = 2;
	t3.exp = 1;
	insertOrdered(l, t3);

	t4.coef = 9;
	t4.exp = 2;
	insertOrdered(l, t4);


	printList(l);
	detroyList(l);
	return 0;
}