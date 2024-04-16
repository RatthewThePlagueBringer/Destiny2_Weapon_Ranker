/*#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void swap(vector<int>& v, int a, int b) {
	int temp = v[a];
	v[a] = v[b];
	v[b] = temp;
}

int partition(vector<int>& vec, int low, int high) {
	
	int pivot = vec[low];
	int up = low, down = high;

	while (up < down) {
		for (int j = up; j < high; j++) {
			if (vec[up] > pivot) {
				break;
			}
			up++;
		}
		for (int j = high; j > low; j--) {
			if (vec[down] < pivot) {
				break;
			}
			down--;
		}
		if (up < down) {
			swap(vec, up, down);
		}
	}
	swap(vec, low, down);
	return down;
}

void quickSort(vector<int>& vec, int low, int high) {
	if (low < high) {
		int pivot = partition(vec, low, high);
		quickSort(vec, low, pivot - 1);
		quickSort(vec, pivot + 1, high);
	}
}

void insertionSort(vector<int>& vec, int gap, int n) {
	for (int i = gap; i < n; i++) {
		int key = vec[i];
		int j = i;
		while (j >= gap && key < vec[j - gap]) {
			vec[j] = vec[j - gap];
			j -= gap;
		}
		vec[j] = key;
	}	
}

void shellSort(vector<int>& vec) {

	int n = vec.size();
	int gap = n / 2;

	while (gap > 0) {
		insertionSort(vec, gap, n);
		if (gap == 2) {
			gap = 1;
		}
		else {
			gap /= 2;
		}
	}
}

/
int main() {
	vector<int> input1 = {7, 4, 9, 3, 2, 8, 6, 5};
	int n = sizeof(input1) / sizeof(input1[0]);
	quickSort(input1, 0, n - 1);
	cout << "Quick sort: ";
	for (int i = 0; i < n; i++) {
		cout << input1[i] << " ";
	}
	cout << endl;

	vector<int> input2 = { 7, 4, 9, 3, 2, 8, 6, 5 };
	shellSort(input2);
	cout << "Shell sort: ";
	for (int j = 0; j < input2.size(); j++) {
		cout << input2[j] << " ";
	}
}*/
