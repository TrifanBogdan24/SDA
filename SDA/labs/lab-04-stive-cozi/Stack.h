#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode{
	Item elem;
	struct StackNode *next;
} StackNode;

typedef struct Stack{
	StackNode* head;  // Varful stivei
	long size; // Numarul de elemente din stiva
} Stack;

Stack* createStack(void) {
	// TODO: Cerinta 1
	Stack * stiva = malloc(sizeof(Stack));
	stiva->head = NULL;
	return stiva;
}

int isStackEmpty(Stack* stack) {
	return ! (stack!=NULL && stack->head!=NULL);
	// TODO: Cerinta 1
}

void push(Stack *stack, Item elem) {
	StackNode * nou = malloc(sizeof(StackNode));
	nou->elem = elem;
	if (stack == NULL) {
		// lista vida
		// stack = createStack();
		stack->head = nou;
		stack->size = 1;
		
		return;
	} else if (stack->head == NULL) {
		// lista vida
		stack->head = nou;
		stack->size = 1;
		
		return;
	} else {
		// stiva are cel putin un element
		// noi vom insera la capatul din stanga al stivei, adica la inceput de tot
		nou->next = stack->head;
		stack->head = nou;
		stack->size++;
		return ;
		
	}
	
}

Item top(Stack *stack){	
	if (stack != NULL && stack->head != NULL) {
		return stack->head->elem;
	}
	
	// TODO: Cerinta 1
} 

void pop(Stack *stack) {
	// TODO: Cerinta 1

	if (stack->size == 0) {
		// stiva este vida
		return;
	}

	// stiva are cel putin un element
	// vom sterge primul element de la capatul din stanga al listei, adica de la inceputul ei
	StackNode * stergator = stack->head;
	stack->head = stack->head->next;
	free(stergator);
	stack->size--;
	return;
	
	// TODO: Cerinta 1
}

void destroyStack(Stack *stack){
	// TODO: Cerinta 1
	while (stack -> head != NULL) {
		pop(stack);
	}
	free(stack);
	return ;
}

#endif 
