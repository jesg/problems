

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

typedef struct entry {
	int value;
	SLIST_ENTRY(entry) entries;
} entry;

int main(void){

	SLIST_HEAD(slisthead, entry) head = SLIST_HEAD_INITIALIZER(head);
	SLIST_HEAD(slisthead2, entry) head2 = SLIST_HEAD_INITIALIZER(head2);
	SLIST_INIT(&head);
	SLIST_INIT(&head2);

	for(int i=0; i<10; i++) {
		entry *n1 = malloc(sizeof(struct entry));
		n1->value = i;
		SLIST_INSERT_HEAD(&head, n1, entries);
	}

	for(int i=10; i>0; i--) {
		entry *n1 = malloc(sizeof(struct entry));
		n1->value = i;
		SLIST_INSERT_HEAD(&head2, n1, entries);
	}

	printf("head\n");
	entry *var;
	SLIST_FOREACH(var, &head, entries) {
		printf("%i\n", var->value);
	}

	printf("head2\n");
	SLIST_FOREACH(var, &head2, entries) {
		printf("%i\n", var->value);
	}

	while (!SLIST_EMPTY(&head)) {           /* List Deletion. */
		entry *n1 = SLIST_FIRST(&head);
		SLIST_REMOVE_HEAD(&head, entries);
		free(n1);
	}

	while (!SLIST_EMPTY(&head2)) {           /* List Deletion. */
		entry *n1 = SLIST_FIRST(&head2);
		SLIST_REMOVE_HEAD(&head2, entries);
		free(n1);
	}
	return EXIT_SUCCESS;
}
