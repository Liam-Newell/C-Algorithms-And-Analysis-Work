#include <cstdlib>
#include <iostream>
#include <fstream>
#include "timer.h"

using namespace std;

void insertionSort(int arr[], int left, int right) {
	int curr;
	int i, j;
	for (i = left + 1;i <= right;i++) {
		curr = arr[i];
		for (j = i;j>0 && arr[j - 1] > curr;j--) {
			arr[j] = arr[j - 1];
		}
		arr[j] = curr;
	}
}

void quickSort(int arr[], int left, int right, int threshold) {
	if (right - left <= threshold) {
		insertionSort(arr, left, right);
	}
	else {
		int pivotpt = right;   //index of the pivot
		int i = left;
		int j = right - 1;
		int pivot = arr[pivotpt];
		while (i<j) {
			while (i< right - 1 && arr[i]<pivot) i++;
			while (j > 0 && arr[j]>pivot) j--;
			if (i<j)
				swap(arr[i++], arr[j--]);
		}
		if (i == j && arr[i] < arr[pivotpt])
			i++;
		swap(arr[i], arr[pivotpt]);
		quickSort(arr, left, i - 1, threshold);
		quickSort(arr, i + 1, right, threshold);
	}
}

void quickSort(int arr[], int size, int threshold) {
	quickSort(arr, 0, size - 1, 3);
}
void generateRandom(int array[], int size) {

}
void generateReverse(int array[], int size) {

}
void generateManyDuplicates(int array[], int size) {

}
void generateNearlySorted(int array[], int size) {

}

int main(int argc, char* argv[]) {
	int size = atoi(argv[1]);
	int* myarr = new int[size];
	Timer stopwatch;
	ofstream log("quick.log");
	generateRandom(myarr, size);
	stopwatch.start();
	quickSort(myarr, size, 3);
	stopwatch.stop();
	cout << stopwatch.currtime() << endl;
	for (int i = 0;i<size;i++) {
		log << myarr[i] << endl;
	}
	return 0;
}
