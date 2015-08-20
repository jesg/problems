
#include <stdio.h>
#include <stdlib.h>

void merge(int[], int, int, int);
void merge_sort(int[], int, int);

int main(void){

	int d[] = { 3, 1, 6, 9, 0, 2, 4};
	int length = sizeof(d) / sizeof(int);

	merge_sort(d, 0, length - 1);
	print_arr(d, length);

	return EXIT_SUCCESS;
}

void print_arr(int arr[], int length) {
	for(int i = 0; i < length; i++){
		printf("%i, ", arr[i]);
	}
	printf("\n");
}

void merge_sort(int arr[], int p, int r) {
	if(p < r) {
		int q = (p + r) / 2;
		/* printf("stack p %i q %i r %i\n", p, q, r); */
		merge_sort(arr, p, q);
		merge_sort(arr, (q+1), r);
		merge(arr, p, (q+1), r);
	}
}

void merge(int arr[], int p, int q, int r) {
	int scratch_length = r - p +1;
	int scratch[scratch_length];
	int i = 0;
	int left_end = q - 1;
	int left = p;
	int right = q;
	while((left <= left_end) && (right <= r)) {
		if( arr[left] <= arr[right]) {
			scratch[i++] = arr[left++];
		} else {
			scratch[i++] = arr[right++];
		}
	}

	while(left <= left_end)
			scratch[i++] = arr[left++];

	while(right <= r)
		scratch[i++] = arr[right++];

	int k = 0;
	for(int j = p; k < scratch_length; k++, j++)
		arr[j] = scratch[k];
}
