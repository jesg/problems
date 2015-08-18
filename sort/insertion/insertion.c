
#include <stdio.h>
#include <stdlib.h>

void insertion(int, int*);

int main(void){

	int d[] = { 3, 1, 6, 9, 0, 2 };
	int length = sizeof(d) / sizeof(int);

	insertion(length, d);

	for(int k = 0; k < length; k++) {
		printf("%i\n", d[k]);
	}

	return EXIT_SUCCESS;
}

void insertion(int length, int *d) {
	for(int j = 1; j < length; j++){
		int key = d[j];
		int i = j - 1;
		while( i >= 0 && d[i] > key){
			d[i + 1] = d[i];
			i = i - 1;
		}
		d[i + 1] = key;
	}
}
