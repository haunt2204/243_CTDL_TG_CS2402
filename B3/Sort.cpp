#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
using namespace std;

#define MAX 100000

void selectionSort(int a[], int n) {
	int pos;
	for (int i = 0; i < n - 1; i++) {
		pos = i;
		for (int j = i + 1; j < n; j++)
			if (a[j] < a[pos])
				pos = j;
		if(pos!=i)
			swap(a[pos], a[i]);
	}
}

void insertionSort(int a[], int n) {
	int x, j;
	for (int i = 1; i < n; i++) {
		x = a[i];
		j = i - 1;
		while (j >= 0 && a[j] > x) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = x;
	}
}

void printList(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int main() {
	int *a = new int[MAX];
	int n = MAX;

	for (int i = 0; i < n; i++) {
		a[i] = MAX - i;
	}

	time_t start = time(NULL);
	cout << ctime(&start) << endl;
	selectionSort(a, n);
	time_t end = time(NULL);
	cout << ctime(&end) << endl;

	cout << end - start << endl;

	//printList(a, n);

	delete[]a;
	return 0;
}