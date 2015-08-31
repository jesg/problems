#include <stdio.h>
#include <stdlib.h>
#include <bsd/sys/tree.h>


typedef struct my_entry {
	RB_ENTRY(my_entry) link;
	int key;
	int value;
} my_entry;

int my_cmp(my_entry *a, my_entry *b) {
	return a->key - b->key;
}

RB_HEAD(my_entry_s, my_entry) head = RB_INITIALIZER(head);
RB_PROTOTYPE(my_entry_s, my_entry, link, my_cmp);
RB_GENERATE(my_entry_s, my_entry, link, my_cmp);

int main(void){

	my_entry *data = malloc(sizeof(my_entry));
	data->key = 7;
	data->value = 9;

	RB_INSERT(my_entry_s, &head, data);

	my_entry find;
	find.key = 7;
	data = RB_FIND(my_entry_s, &head, &find);
	printf("%i\n", data->value);

	return EXIT_SUCCESS;
}
