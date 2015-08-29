

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

typedef struct hash {
	int length;
	GList* *buckets;
} hash;

typedef struct element {
	int key;
	int value;
} element;

hash *hash_new(int);
void hash_free(hash*);
void hash_insert(hash*, int, int);
int hash_search(hash*, int);

int int_hash(hash *self, int key) {
	return (31*key)%self->length;
}

hash *hash_new(int length) {
	hash *my_hash = malloc(sizeof(hash));
	my_hash->length = length;
	my_hash->buckets = malloc(sizeof(GList)*length);
	for(int i=0; i<length; i++) my_hash->buckets[i] = NULL;
	return my_hash;
}

void hash_insert(hash *self, int key, int value) {
	GList *bucket = self->buckets[int_hash(self, key)];
	element *e = g_new(element, 1);
	e->key = key;
	e->value = value;
	bucket = g_list_prepend(bucket, e);
	self->buckets[int_hash(self, key)] = bucket;
}

int hash_search(hash *self, int key) {
	GList *bucket = self->buckets[int_hash(self, key)];
	GList *l = bucket;
	while(l != NULL) {
		GList *next = l;
		if(((element*)next->data)->key == key) {
			return ((element*)next->data)->value;
		}
		l = l->next;
	}
	return 0;
}

void hash_free(hash *self) {
	for(int i=0; i< self->length; i++) {
		g_list_free_full(self->buckets[i], g_free);
	}
	free(self->buckets);
	free(self);
}


int main(void){

	hash *my_hash = hash_new(20);
	for(int i=0; i<10; i++) {
		hash_insert(my_hash, i, (i*2));
	}

	for(int i=0; i<10; i++) {
		printf("%i => %i\n", i, hash_search(my_hash, i));
	}
	hash_free(my_hash);

	return EXIT_SUCCESS;
}
