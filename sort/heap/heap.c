
#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
	int size;
	int length;
	int *data;
} heap;

heap *heap_new(int);
void heap_free(heap*);
void heap_sort(heap*);
void heap_max_heapify(heap*, int);
void heap_build_max_heap(heap*);

heap *heap_new(int length) {
	heap *my_heap = malloc(sizeof(heap));
	my_heap->size = 0;
	my_heap->length = length;
	my_heap->data = NULL;
	return my_heap;
}

void heap_free(heap *self) {
	free(self);
}

inline int left(int i) {
	return i << 1;
}

inline int right(int i) {
	return (i << 1) + 1;
}

inline void swap(int *arr, int i, int j) {
		int a = arr[i];
		arr[i] = arr[j];
		arr[j] = a;
}

void heap_max_heapify(heap *self, int i) {
	int l = left(i);
	int r = right(i);
	int *arr = self->data;
	int largest = i;
	if( l < self->size && arr[l] > arr[i] ) {
		largest = l;
	}
	if( r < self->size && arr[r] > arr[largest] ) {
		largest = r;
	}
	if( largest != i ) {
		swap(arr, largest, i);
		heap_max_heapify(self, largest);
	}
}

void heap_build_max_heap(heap *self) {
	self->size = self->length;
	for(int i = self->length/2; i >= 0; i--) {
		heap_max_heapify(self, i);
	}
}

void heap_sort(heap *self) {
	heap_build_max_heap(self);
	for(int i=self->length - 1; i > 0; i--) {
		swap(self->data, 0, i);
		self->size--;
		heap_max_heapify(self, 0);
	}
}

void heap_print(heap *self) {
	for(int i = 0; i < self->length; i++)
		printf("%i, ", self->data[i]);
	printf("\n");
}

int main(void){

	int d[] = { 3, 1, 6, 9, 0, 2, 4};
	int length = sizeof(d) / sizeof(int);

	heap *my_heap = heap_new(length);
	my_heap->data = d;
	heap_sort(my_heap);
	heap_print(my_heap);
	heap_free(my_heap);

	return EXIT_SUCCESS;
}
