#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define MAX 20

//Sinh vien
struct SinhVien {
	int mssv;
	string hoTen;
	char ngaySinh[11];
	string queQuan;
	double diemTb;
};

//Nhap 1 sinh vien
void nhap1Sv(SinhVien& sv) {
	cout << "Nhap MSSV: ";
	cin >> sv.mssv;

	cin.ignore();
	cout << "Nhap ho ten: ";
	getline(cin, sv.hoTen, '\n');

	cout << "Nhap ngay sinh: ";
	cin >> sv.ngaySinh;

	cin.ignore();
	cout << "Nhap que quan: ";
	getline(cin, sv.queQuan);

	cout << "Nhap diem TB: ";
	cin >> sv.diemTb;
}

void xuat1Sv(SinhVien sv) {
	cout << "===============================\n";
	cout << "ID: ";
	cout << sv.mssv << endl;
	cout << "Ho va ten: ";
	cout << sv.hoTen << endl;
	cout << "Ngay sinh: ";
	cout << sv.ngaySinh << endl;
	cout << "Que quan: ";
	cout << sv.queQuan << endl;
	cout << "Diem trung binh: ";
	cout << sv.diemTb << endl;
	cout << "===============================\n";
}

//Khai bao cau truc
struct Node {
	//Vung thong tin
	SinhVien info;

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
Node* createNode(SinhVien sv) {
	Node* p = new Node;
	p->info = sv;
	p->next = NULL;
	return p;
}

void insertFirst(LinkedList& l, SinhVien sv) {
	Node* p = createNode(sv);
	
	if (l.head == NULL) {
		l.head = l.tail = p;
		return;
	}

	p->next = l.head;
	l.head = p;
}

//Them vao cuoi
void insertLast(LinkedList& l, SinhVien sv) {
	Node* p = createNode(sv);

	if (l.head == NULL) {
		l.head = l.tail = p;
		return;
	}

	l.tail->next = p;
	l.tail = p;
}

//Tim kiem
Node* search(LinkedList l, int id) {
	Node* p = l.head;

	while (p != NULL && p->info.mssv != id) {
		p = p->next;
	}

	return p;
}

//Them sau node q
bool insertAfter(LinkedList& l, int id, SinhVien sv) {
	Node* q = search(l, id);
	if (q == NULL)
		return false;

	Node* p = createNode(sv);
	p->next = q->next;
	
	if (q->next == NULL)
		l.tail = p;
	
	q->next = p;
}

void insertOrdered(LinkedList& l, SinhVien sv) {
	if (l.head == NULL || l.head->info.mssv > sv.mssv) {
		insertFirst(l, sv);
		return;
	}

	Node* p = createNode(sv);
	Node* q = l.head;

	while (q->next != NULL && q->next->info.mssv < sv.mssv) {
		q = q->next;
	}

	if (q == l.tail) {
		insertLast(l, sv);
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
	while (p != NULL) {
		//cout << p->info;
		xuat1Sv(p->info);
		p = p->next;
	}
}

void nhapDsSvTuFile(LinkedList& l) {
	ifstream fin("SinhVien.txt");
	if (fin.is_open()) {

		while (!fin.eof()) {
			SinhVien sv;

			fin >> sv.mssv;
			fin.ignore();
			getline(fin, sv.hoTen, '#');
			fin.getline(sv.ngaySinh, 11, '#');
			getline(fin, sv.queQuan, '#');
			fin >> sv.diemTb;

			insertFirst(l, sv);
		}

		fin.close();
	}
}

//Thao tac truy xuat phan tu thu i trong DSLKD: i = 0

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
	while (prevLast->next!=l.tail) {
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
	for (Node* i = l.head; i->next != NULL; i=i->next) {
		for (Node* j = i->next; j != NULL; j=j->next) {
			if (j->info.mssv < i->info.mssv) {
				swap(i->info, j->info);
			}
		}
	}
}

int main() {
	LinkedList l;
	init(l);

	nhapDsSvTuFile(l);
	printList(l);

	/*cout << "=================THEM PHAN TU===================\n";*/
	/*SinhVien sv;
	sv.mssv = 999;

	int id;
	cin >> id;

	insertAfter(l, id, sv);*/

	/*cout << "=================XOA PHAN TU===================\n";
	int id;
	cin >> id;
	delNode(l, id);
	printList(l);*/
	
	cout << "=================SAP XEP===================\n";
	sort(l);
	printList(l);

	cout << "=================THEM VAO DS CO THU TU===================\n";
	SinhVien sv;
	sv.mssv = 201;
	insertOrdered(l, sv);
	printList(l);

	detroyList(l);
	return 0;
}