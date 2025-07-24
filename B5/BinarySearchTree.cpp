#include <iostream>
#include <stack>
using namespace std;

//Khai bao cau truc
struct Node
{
	//Vung thong tin
	int info;

	//Vung lien ket
	Node* left, * right;
};

//Khoi tao rong
void init(Node*& root) {
	root = NULL;
}

//Kiem tra rong
bool isEmpty(Node* root) {
	return root == NULL;
}

//Them phan tu vao cay
Node* createNode(int key) {
	Node* p = new Node;
	p->info = key;
	p->left = p->right = NULL;

	return p;
}

void insertNode(Node*& root, int key) {
	if (isEmpty(root)) {
		root = createNode(key);
		return;
	}

	Node* p = createNode(key);
	Node* q = root;
	Node* parent = NULL;

	while (q != NULL) {
		parent = q;
		if (key > q->info) {
			q = q->right;
		}
		else if (key < q->info) {
			q = q->left;
		}
		else {
			return;
		}
	}

	if (key > parent->info)
		parent->right = p;
	else
		parent->left = p;

}
//Thao tac xoa: khong de quy
void delNode(Node*& root, int key) {
	Node* q = root;
	Node* parent = NULL;

	while (q != NULL && q->info != key) {
		parent = q;
		if (key > q->info) {
			q = q->right;
		}
		else
			q = q->left;
	}

	if (q == NULL) {
		cout << "Khong tim thay!\n";
		return;
	}

	//Bac 1 va nut la
	if (q->left == NULL || q->right == NULL) {
		Node* temp = q->left != NULL ? q->left : q->right;

		if (q == root) {
			root = temp;
		}else if (key > parent->info)
			parent->right = temp;
		else
			parent->left = temp;

		delete q;
		return;
	}
	//Bac 2
	//Tim nut phai nhat cua cay con trai
	Node* temp = q->left;
	parent = NULL;
	while (temp->right != NULL) {
		parent = temp;
		temp = temp->right;
	}

	//Chep du lieu cua temp cho q
	q->info = temp->info;

	//Dieu chinh lien ket cho parent
	if (parent != NULL)
		parent->right = temp->left;
	else
		q->left = temp->left;
	//Xoa nut temp
	temp->left = NULL;
	delete temp;
}

//Thao tac xoa dung de quy: SV tu cai dat

//Duyet cay theo thu tu: LNR, LRN, NLR dung de quy
void duyetLNR(Node* root) {
	if (isEmpty(root)) {
		return;
	}
	duyetLNR(root->left);
	cout << root->info << " ";
	duyetLNR(root->right);
}

//Thao tac tim kiem
Node* search(Node* root, int key) {
	Node* q = root;
	while (q != NULL && q->info != key) {
		if (key > q->info)
			q = q->right;
		else
			q = q->left;
	}
	return q;
}
//Duyet LNR khong de quy: stack
void lnrNoRec(Node* root) {
	stack<Node*> s;
	Node* p = root;

	while (p!=NULL || !s.empty()) {
		while (p != NULL) {
			s.push(p);
			p = p->left;
		}

		p = s.top();
		s.pop();
		cout << p->info << " ";
		p = p->right;
	}
}

//Giai phong
void detroyTree(Node*& root) {
	while (!isEmpty(root)) {
		delNode(root, root->info);
	}
}

int main() {
	Node* root;
	init(root);

	insertNode(root, 40);
	insertNode(root, 60);
	insertNode(root, 20);
	insertNode(root, 45);
	insertNode(root, 65);
	lnrNoRec(root);
	/*cout << "\n================XOA NUT TRONG CAY=============\n";
	delNode(root, 40);*/

	cout << "\n================TIM KIEM=============\n";
	Node* res = search(root, 40);
	if (res != NULL)
		cout << res->info << endl;

	
	detroyTree(root);
	return 0;
}