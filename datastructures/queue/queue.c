

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queue {
	int head;
	int tail;
	int last;
	int *data;
} queue;

queue *queue_new(int);
void queue_free(queue*);
bool queue_empty(queue*);
void queue_enqueue(queue*, int);
int queue_dequeue(queue*);

queue *queue_new(int length) {
	queue *my_queue = malloc(sizeof(queue));
	my_queue->head = 0;
	my_queue->tail = 0;
	my_queue->last = length - 1;
	my_queue->data = malloc(sizeof(int) * length);
	return my_queue;
}

void queue_free(queue *self) {
	free(self->data);
	free(self);
}

bool queue_empty(queue *self) {
	if(self->head == self->tail) {
		return true;
	} else {
		return false;
	}
}

void queue_enqueue(queue *self, int x) {
	self->data[self->tail] = x;
	if(self->last == self->tail) {
		self->tail = 0;
	} else {
		self->tail = self->tail + 1;
	}
}

int queue_dequeue(queue *self) {
	int x = self->data[self->head];
	if(self->head == self->last) {
		self->head = 0;
	} else {
		self->head++;
	}
	return x;
}

int main(void){

	int d[] = { 3, 1, 6, 9, 0, 2, 4};
	int length = sizeof(d) / sizeof(int);

	queue *my_queue = queue_new(length);
	for(int i = 0; i<length; i++)
		queue_enqueue(my_queue, d[i]);

	for(int i = 0; i<length; i++)
		printf("%i\n", queue_dequeue(my_queue));

	queue_free(my_queue);

	return EXIT_SUCCESS;
}
