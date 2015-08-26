
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stack {
	int top;
	int length;
	int *data;
} stack;

stack *stack_new(int);
void stack_free(stack*);
int stack_pop(stack*);
bool stack_empty(stack*);
void stack_push(stack*, int);

stack *stack_new(int length) {
	stack *my_stack = malloc(sizeof(stack));
	my_stack->top = -1;
	my_stack->length = length;
	my_stack->data = malloc(sizeof(int) * length);
	return my_stack;
}

void stack_free(stack *self) {
	free(self->data);
	free(self);
}

bool stack_empty(stack *self) {
	if(self->top == -1) {
		return true;
	} else {
		return false;
	}
}

void stack_push(stack *self, int value) {
	if(self->top == self->length - 1) {
		return NULL;
	} else {
		self->top = self->top + 1;
		self->data[self->top] = value;
	}
}

int stack_pop(stack *self) {
	if(stack_empty(self)) {
		return NULL;
	} else {
		self->top = self->top - 1;
		return self->data[self->top + 1];
	}
}

int main(void){

	int d[] = { 3, 1, 6, 9, 0, 2, 4};
	int length = sizeof(d) / sizeof(int);

	stack *my_stack = stack_new(length);
	for(int i = 0; i<length; i++)
		stack_push(my_stack, d[i]);

	for(int i = 0; i<length; i++)
		printf("%i\n", stack_pop(my_stack));

	stack_free(my_stack);

	return EXIT_SUCCESS;
}
