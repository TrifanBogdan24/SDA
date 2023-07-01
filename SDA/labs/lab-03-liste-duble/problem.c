#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Maximum number of characters that can be read
 * in one go from the keyboard
 */
#define MAX_INPUT_LEN 255

/**
 *  Generic Item type definition
 */
typedef char Item;

/**
 * The Double linked list interface
 */
#include "DoubleLinkedList.h"

/**
 * Utility functions for character lists
 */
void printList(List *list){
	ListNode* iterator = list->first;
	printf("[");
	while(iterator != list->last){
		printf("%c, ", iterator->elem);
		iterator = iterator->next;
	}
	printf("%c]",list->last->elem);
}

void printListReverse(List* list){
	ListNode* iterator = list->last;
	printf("[");
	while(iterator != list->last){
		printf("%c ", iterator->elem);
		iterator = iterator->prev;
	}
	printf("%c]",list->last->elem);
}




/* Plaindrome computation function */
int isPalindrome(List* list){
	// TODO: Cerinta 2
	
	if (isEmpty(list) == 1) return 0;
	if (length(list) <= 3) return 1;
	int ok = 1;
	list -> last = list -> last -> prev ; // ca sa stergem mai usor, ne luam o referinta in stanga ultimului element
	while (ok == 1) {
		if (list -> first -> elem != list -> last -> next -> elem) return 0;
		if (list -> first -> next == list -> last -> next) return 1; // am ajuns cu brio la jumatate, lista avand nr par de elemente
		if (list -> first -> next == list -> last ) return 1;
		deleteOnce(list , list -> first->elem);
		free(list->last->next); 
		list->last->next = NULL;
		list-> last = list -> last -> prev;
	}
	return 1;
}

/* Main Program */
int main(void) {

	int len;
	int inputCount = 0;
	char inputCharacters[256];
	FILE* inputFile = fopen("input","r");



	while(fgets(inputCharacters, MAX_INPUT_LEN, inputFile) != NULL){
			// Remove trailing CR/LF (i.e. '\r', '\n')
			inputCharacters[strcspn(inputCharacters, "\r\n")] = 0;
			len = strlen(inputCharacters);
			if(len == 0) break;

			List *list = createList();
			for(int i = 0; i < len; i++) insertAt(list, inputCharacters[i],i);


			printf("Input%d: ", ++inputCount);
			printf("\"%s\" --- ", inputCharacters);
			printf("List: ");
			printList(list);

			if(isPalindrome(list)) printf(" is a palindrome.");
			else printf(" is NOT a palindorme.");
			printf("\n");

			list = destroyList(list);
	}

	fclose(inputFile);
	return 0;
}



