

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct element {
	struct element *next;
	struct element *prev;
	int data;
} element;

typedef struct list {
	element *first;
} list;


list *list_new(void);
void list_free(list*);
bool list_empty(list*);
int list_search(list*, int);
void list_push(list*, int);

list *list_new(void) {
	list *my_list = malloc(sizeof(list));
	my_list->first = NULL;
	return my_list;
}

void list_free(list *self) {
	element *x = self->first;
	while(x->next != NULL) {
		x = x->next;
		free(x->prev);
	}
	free(self);
}

bool list_empty(list *self) {
	if(self->first == NULL) {
		return true;
	} else {
		return false;
	}
}

int list_search(list *self, int k) {
	element *x = self->first;
	while(&x->data != NULL && x->data != k)
		x = x->next;
	return x->data;
}

void list_push(list *self, int k) {
	element *e = malloc(sizeof(element));
	e->data = k;
	e->next = self->first;
	if(self->first != NULL) {
		self->first->prev = e;
	}
	self->first = e;
	e->prev = NULL;
}

int main(void){

	int d[] = { 3, 1, 6, 9, 0, 2, 4};
	int length = sizeof(d) / sizeof(int);

	list *my_list = list_new();
	for(int i = 0; i<length; i++)
		list_push(my_list, d[i]);

	for(int i = 0; i<length; i++)
		printf("%i\n", list_search(my_list, d[i]));

	list_free(my_list);

	return EXIT_SUCCESS;
}
