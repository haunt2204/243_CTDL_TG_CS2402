#include "AbstractLinkedList.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

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

ostream& operator<<(ostream& out, const SinhVien& sv) {
	out << "===============================\n";
	out << "ID: ";
	out << sv.mssv << endl;
	out << "Ho va ten: ";
	out << sv.hoTen << endl;
	out << "Ngay sinh: ";
	out << sv.ngaySinh << endl;
	out << "Que quan: ";
	out << sv.queQuan << endl;
	out << "Diem trung binh: ";
	out << sv.diemTb << endl;
	out << "===============================\n";

	return out;
}

template <typename T>
void nhapDsSvTuFile(LinkedList<T>& l) {
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

int main() {
	LinkedList<SinhVien> l;
	init(l);

	nhapDsSvTuFile(l);
	printList(l);

	detroyList(l);
	return 0;
}