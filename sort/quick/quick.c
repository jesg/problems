
#include <stdio.h>
#include <stdlib.h>

int main(void){

	int d[] = { 3, 1, 6, 9, 0, 2, 4};
	int length = sizeof(d) / sizeof(int);

	quick_sort(d, 0, length-1);
	print_arr(d, length);

	return EXIT_SUCCESS;
}

void quick_sort(int arr[], int p, int r) {
	if(p < r) {
		const int q = partition(arr, p, r);
		quick_sort(arr, p, q - 1);
		quick_sort(arr, q + 1, r);
	}
}

inline void swap(int arr[], int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int partition(int arr[], int p, int r) {
	int x = arr[r];
	int i = p - 1;
	for(int j = p; j <= r - 1; j++) {
		if(arr[j] <= x) {
			i = i + 1;
			swap(arr, i, j);
		}
	}
	swap(arr, i + 1, r);
	return i + 1;
}

void print_arr(int arr[], int length) {
	for(int i = 0; i < length; i++){
		printf("%i, ", arr[i]);
	}
	printf("\n");
}
