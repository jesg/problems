

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

SLIST_HEAD(slisthead, entry) head = SLIST_HEAD_INITIALIZER(head);

typedef struct entry {
	int value;
	SLIST_ENTRY(entry) entries;     /* Singly-linked List. */
} entry;

int main(void){

	SLIST_INIT(&head);                      /* Initialize the list. */

	for(int i=0; i<10; i++) {
		entry *n1 = malloc(sizeof(struct entry));      /* Insert at the head. */
		n1->value = i;
		SLIST_INSERT_HEAD(&head, n1, entries);
	}

	entry *var;
	SLIST_FOREACH(var, &head, entries) {
		printf("%i\n", var->value);
	}

	while (!SLIST_EMPTY(&head)) {           /* List Deletion. */
		entry *n1 = SLIST_FIRST(&head);
		SLIST_REMOVE_HEAD(&head, entries);
		free(n1);
	}

	return EXIT_SUCCESS;
}
