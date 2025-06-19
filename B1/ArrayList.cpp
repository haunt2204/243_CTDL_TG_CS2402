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
struct ArrayList {
	SinhVien ds[MAX];
	int soLuong;
};

//Khoi tao rong
void init(ArrayList& l) {
	l.soLuong = 0;
}

//Cac thao tac co ban
////Duyet, Tim kiem, xoa tai vi tri vt, them tai vi tri vt
bool themSv(ArrayList& l, SinhVien sv, int vt = 0) {
	if (vt<0 || vt>l.soLuong)
		return false;
	for (int i = l.soLuong; i > vt; i--) {
		l.ds[i] = l.ds[i - 1];
	}

	l.ds[vt] = sv;
	l.soLuong++;
	return true;
}


////Nhap/Xuat
void nhapDsSv(ArrayList &l) {
	do {
		cout << "Nhap so luong SV: ";
		cin >> l.soLuong;
	} while (l.soLuong<=0||l.soLuong>MAX);
	for (int i = 0; i < l.soLuong; i++) {
		nhap1Sv(l.ds[i]);
	}
}

void nhapDsSvTuFile(ArrayList& l) {
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

			themSv(l, sv, l.soLuong);
		}

		fin.close();
	}
}

void xuatDsSv(ArrayList l) {
	if (l.soLuong == 0) {
		cout << "Danh sach rong!\n";
		return;
	}
	for (int i = 0; i < l.soLuong; i++) {
		xuat1Sv(l.ds[i]);
	}
}

//Thao tac xoa tai vi tri vt
bool delSv(ArrayList& l, const int vt=0) {
	if (vt < 0 || vt >= l.soLuong)
		return false;
	for (int i = vt; i < l.soLuong - 1; i++) {
		l.ds[i] = l.ds[i + 1];
	}
	l.soLuong--;
	return true;
}
//Thao tac tim sinh vien theo id
int timKiem(ArrayList& l, const int id) {
	int res = -1;
	for (int i = 0; i < l.soLuong; i++) {
		if (l.ds[i].mssv == id) {
			res = i;
			break;
		}
	}
	return res;
}

//Thao tac sap xep danh sach: giam dan theo id cho phep nguoi dung linh hoat thay doi DK
int cmpWithIdAsc(SinhVien sv1, SinhVien sv2) {
	return sv1.mssv - sv2.mssv;
}

int cmpWithIdDesc(SinhVien sv1, SinhVien sv2) {
	return -(sv1.mssv - sv2.mssv);
}

int cmpWithNameAsc(SinhVien sv1, SinhVien sv2) {
	return sv1.hoTen.compare(sv2.hoTen);
}

void sort(ArrayList& l, int comparator(SinhVien, SinhVien)) {
	for (int i = 0; i < l.soLuong - 1; i++) {
		for (int j = i + 1; j < l.soLuong; j++) {
			if (comparator(l.ds[j], l.ds[i])<0) {
				swap(l.ds[i], l.ds[j]);
			}
		}
	}
}


int main() {
	ArrayList l;
	init(l);

	nhapDsSvTuFile(l);
	

	cout << "-------------SAP XEP DANH SACH------------------\n";
	sort(l, cmpWithNameAsc);
	xuatDsSv(l);
	/*cout << "-------------TIM VA XOA SINH VIEN------------------\n";
	int res = timKiem(l, 2018006);
	if (res != -1) {
		delSv(l, res);
		xuatDsSv(l);
	}
	else
		cout << "KHONG TIM THAY!\n";*/
	

	/*nhapDsSv(l);
	xuatDsSv(l);*/

	/*SinhVien sv;
	sv.mssv = 2;

	themSv(l, sv,l.soLuong);
	cout << "-------------THEM SINH VIEN------------------\n";
	xuatDsSv(l);*/

	return 0;
}