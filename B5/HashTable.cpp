#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Noi ket truc tiep

//Khai bao cau truc
#define M 11

//Ham bam
int hashFunc(string w) {
	int key = 0;

	for (int i = 0; i < w.length(); i++) {
		key += (int)w[i]*(i+1);
	}

	return key % M;
}

struct Word {
	string word;
	string type;
	string mean;
};

//Bang bam
struct Node
{
	Word data;
	Node* next;
};

struct HashTable
{
	Node* h[M];
};

//Thao tac khoi tao rong
void init(HashTable& ht) {
	for (int i = 0; i < M; i++) {
		ht.h[i] = NULL;
	}
}
//Them phan tu vao bang bam
Node* createNode(Word key) {
	Node* p = new Node;
	p->data = key;
	p->next = NULL;
	return p;
}

void insertNode(HashTable& ht, Word key) {
	int k = hashFunc(key.word);

	if (ht.h[k] == NULL) {
		ht.h[k] = createNode(key);
		return;
	}
	Node *p = createNode(key);
	Node* q = ht.h[k];

	while (q->next != NULL && q->next->data.word < key.word) {
		q = q->next;
	}

	if (q == ht.h[k] && key.word < q->data.word) {
		p->next = q;
		ht.h[k] = p;
	}
	else {
		p->next = q->next;
		q->next = p;
	}
}

//Thao tac tim kiem
Node* search(HashTable ht, string key) {
	int k = hashFunc(key);
	Node* q = ht.h[k];
	while (q != NULL && q->data.word != key) {
		q = q->next;
	}
	return q;
}

//Thao in bang bam
void printHashTable(HashTable ht) {
	for (int i = 0; i < M; i++) {
		if (ht.h[i] != NULL) {
			cout << "BUCKET " << i << ": ";
			Node* p = ht.h[i];
			while (p != NULL) {
				cout << p->data.word;
				//<< "-" << p->data.type << "-" << p->data.mean;
				p = p->next;
				if(p!=NULL)
					cout << "-->";
			}
			cout << endl;
		}
	}
}

void readData(HashTable &ht) {
	ifstream inFile("dictionary.txt");
	if (inFile.is_open()) {

		while (!inFile.eof()) {
			Word w;
			getline(inFile, w.word, '#');
			getline(inFile, w.type, '#');
			getline(inFile, w.mean, '\n');

			insertNode(ht, w);
		}

		inFile.close();
	}
}


int main() {
	HashTable ht;
	init(ht);

	readData(ht);

	//printHashTable(ht);

	Node* res = search(ht, "sister");
	cout << res->data.type << "-" << res->data.mean << endl;
	return 0;
}