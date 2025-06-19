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

int main() {
	LinkedList l;
	init(l);

	nhapDsSvTuFile(l);

	printList(l);

	return 0;
}