#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode{
	Item elem; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List{
	ListNode* first; // link to the first node
	ListNode* last; // link to the last node
}List;
// -----------------------------------------------------------------------------

/**
 * Create a new node
 *  [input]: Item
 *  [output]: List*
 */
ListNode *createNode(Item elem) {
	// TODO: Cerinta 1a
   ListNode* new_node = malloc(sizeof(ListNode));
   new_node -> next = new_node -> prev = NULL;
   new_node -> elem = elem;
   
   return new_node;
}

/**
 * Create a new (empty)  list  -- Silde-urile 13/14 Curs 2
 *  [input]: None
 *  [output]: List*
 */
List* createList(void){
	// TODO: Cerinta 1a
	List* new_list = malloc(sizeof(List));
	new_list -> first = NULL;
	new_list -> last = NULL;
	return new_list;
}
// -----------------------------------------------------------------------------


/**
 * Determines if the list is empty
 *  [input]: List*
 *  [output]: 1 - empty/ 0 - not empty
 */
int isEmpty(List *list){
	// TODO: Cerinta 1b
	return ( list -> first == NULL && list -> last == NULL);
}
// -----------------------------------------------------------------------------


/**
 * Determines if a list contains a specified element
 *  [input]: List*, Item
 *  [output]: int (1 - contains/ 0 - not contains)
 */
int contains(List *list, Item elem){
	// TDOO: Cerinta 1c
	ListNode* santinela = list->first;
	while( santinela != NULL ) {
		if( santinela -> elem == elem ) return 1;
		santinela = santinela -> next;
	}
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Insert a new element in the list at the specified position.
 * Note: Position numbering starts with the position at index zero
 *  [input]: List*, Item, int
 *  [output]: void
 */
void insertAt(List* list, Item elem, int pos){

	// Guard against young player errors
	if ( list == NULL || pos < 0 ) return;
	ListNode *new_node = createNode(elem);
	
	if( isEmpty(list) && pos == 0) {
		list -> first = list -> last = new_node;
		return;
	}

	ListNode *santinela = list->first;
	while( pos != 0 && santinela != NULL) {
		santinela = santinela -> next;
		pos--;
	}

	if (pos != 0) return;
	if (santinela == NULL) {
		list -> last -> next = new_node;
		new_node -> prev = list -> last;
		list -> last = new_node;
		return ;
	}
	if (santinela == list -> first) {
		new_node -> next = list -> first;
		list -> first -> prev = new_node;
		list -> first = new_node;
		return ;
	}
	new_node -> next = santinela;
	new_node -> prev = santinela -> prev;
	santinela -> prev -> next = new_node;
	santinela -> prev = new_node;
	return ;

	// TODO: Cerinta 1d
}
// -----------------------------------------------------------------------------


/**
 * Delete the first element instance form a list.
 *  [input]: List*, Item
 *  [output]: void
 */
void deleteOnce(List *list, Item elem){
	// Guard against young player errors
	
	if (list == NULL) return;
	if (contains(list ,elem) == 0) return;

	if (list -> first -> elem == elem) {
		// stergere de la inceput
		
		if (list -> first == list -> last) {
			// lista are un singur element
			list -> first = list -> last = NULL;
			free(list->first);
			return;
		} else {
			// lista are mai multe elemente
			ListNode* stergator = list -> first;
			list -> first = list -> first -> next;
			list -> first -> prev = NULL;
			free(stergator);
			return ;
		}
	}
	
	
	if (list -> last -> elem == elem) {
		// stergere de la final
		ListNode* stergator = list -> last;
		list -> last = list -> last -> prev;
		list -> last -> next = NULL;
		free(stergator);
		return ;
	}

	ListNode* santinela = list -> first;
	// daca am ajunsa pana aici, valoarea se afla deja in interiorul listei
	while (santinela -> elem != elem) {
		santinela = santinela -> next;
	} 

	// stergere din interiorul listei

	santinela -> next -> prev = santinela -> prev;
	santinela -> prev -> next = santinela -> next;

	free(santinela);
	return ;

	//TODO: Cerinta 1e
}
// -----------------------------------------------------------------------------


/**
 * Compute list length
 *  [input]: List*
 *  [output]: int
 */
int length(List *list){
	// Guard against young player errors
	if(list == NULL) return 0;
	ListNode* santinela = list -> first;
	int nr = 0;
	while (santinela != NULL) {
		nr++;
		santinela = santinela -> next;
	}
	free(santinela);
	return nr;

	// TODO: Cerinta 1f
	return 0;
}
// -----------------------------------------------------------------------------



/**
 * Destroy a list.
 *  [input]: List*
 *  [output]: void
 */
List* destroyList(List* list){
	// Guard against young player errors
	if(list == NULL) return NULL;
	while ( list -> first != NULL) {
		// stergem succeiv primul element al listei
		// o privim practic asemenea unei cozi
		deleteOnce(list , list->first->elem);
	}
	free(list);
	//TODO: Cerinta 1g
	return NULL;
}
// -----------------------------------------------------------------------------


#endif //_DOUBLE_LINKED_LIST_H_
