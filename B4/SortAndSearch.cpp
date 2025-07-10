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
		if (pos != i)
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

//Interchange sort
void interchangeSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++)
			if (a[j] < a[i])
				swap(a[i], a[j]);
	}
}

//Bubble sort
void bubbleSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = n - 1; j > i; j--) {
			if (a[j] < a[j - 1])
				swap(a[i], a[j]);
		}
	}
}
//Quick Sort
void quickSort(int a[], int left, int right) {
	int l = left, r = right;

	int pivot = a[(left + right) / 2];

	while (l <= r) {
		while (a[l] < pivot)
			l++;
		while (a[r] > pivot)
			r--;

		if (l <= r) {
			swap(a[l++], a[r--]);
		}
	}

	if (left < r) {
		quickSort(a, left, r);
	}
		
	if (l < right) {
		quickSort(a, l, right);
	}
}
//Heap Sort
////Tao heap max
void heapify(int a[], int n, int i) {
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int jMax = i;

	if (l<n && a[l]>a[jMax])
		jMax = l;
	if (r<n && a[r]>a[jMax])
		jMax = r;

	if (jMax != i) {
		swap(a[i], a[jMax]);
		heapify(a, n, jMax);
	}
}

void heapSort(int a[], int n) {
	int i = n / 2 - 1;
	while (i >= 0) {
		heapify(a, n, i);
		i--;
	}

	for (int right = n - 1; right > 0; right--) {
		swap(a[0], a[right]);
		heapify(a, right, 0);
	}
}

void printList(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

//Tim kiem
//O(n)
int sequentialSearch(long a[], long n, long key) {
	for (long i = 0; i < n; i++) {
		if (a[i] == key)
			return i;
	}
	return -1;
}

//O(logn)
int binarySearch(long a[], long n, long key) {
	int left = 0, right = n - 1, mid;
	while (left <= right) {
		mid = (left + right) / 2;

		if (a[mid] == key)
			return mid;
		
		if (a[mid] > key)
			left = mid + 1;
		else
			right = mid - 1;
	}
}

int main() {
	//int* a = new int[MAX];
	//int n = MAX;
	//for (int i = 0; i < n; i++) {
	//	a[i] = MAX - i;
	//	/*a[i] = i;*/
	//}
	int a[] = { 40,20,15,50,90,60,10 };
	int n = sizeof(a) / sizeof(a[0]);

	

	time_t start = time(NULL);
	cout << ctime(&start) << endl;
	heapSort(a, n);
	time_t end = time(NULL);
	cout << ctime(&end) << endl;

	cout << end - start << endl;

	printList(a, n);

	//delete[]a;
	return 0;
}