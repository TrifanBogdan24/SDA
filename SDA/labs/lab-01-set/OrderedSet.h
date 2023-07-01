#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include <stdio.h>                                          // needed for printf
#include <stdlib.h>                           // needed for alloc, realloc, free

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

/*
  OrderedSet represents a set with elements of type T stored in memory
  in an ordered fashion.
*/

typedef struct OrderedSet {
  T* elements;                    // pointer to where the elements are in memory
  long size;                                // the number of elements in the set
  long capacity;                      // the current capacity (allocated memory)
} OrderedSet;

// -----------------------------------------------------------------------------

/*
  Function that creates an OrderedSet with elements of type T with a given
  initial capacity.
*/

OrderedSet* createOrderedSet(long initialCapacity) {

  OrderedSet* newSet = (OrderedSet*) malloc(sizeof(OrderedSet));

  newSet->size = 0;                        // initially, the set is empty
  newSet->capacity = initialCapacity;
  newSet->elements = (T*) malloc(initialCapacity * sizeof(T));

  return newSet;
}

// -----------------------------------------------------------------------------

/*
  Function that checks if an element exists in a given set. As the
  elements of the set are ordered in memory, this function uses binary
  search.

  Function returns 1 if the given element exists in the set, and 0
  otherwise.
*/

int contains(OrderedSet* set, const T element) {
  int st = 0, dr = 0, mij = 0;
  st = 0;
  dr = set->size-1;
  while(st<=dr) {
   	mij = dr - (dr-st)/2 ; // = (st+dr)/2
   	if(element < set->elements[mij]) dr = mij - 1;
   	else if(element > set->elements[mij]) st = mij + 1;
   	else return 1; // element == set->elements[mij]   am gasit elementul 
  }
  
  return 0;
}

// -----------------------------------------------------------------------------

/*
  Function that adds a new element to a set. If the element was
  already in the set, nothing changes. Otherwise, the element is added
  to the set. In the end, the elements must be in ascending order.
*/

void add(OrderedSet* set, const T newElement) {
  if(contains(set, newElement) == 0) {
  
	  set->size ++;
	  set->elements[set->size - 1] = newElement;
	  int poz = set->size - 1;
	  while(poz >0 && set->elements[poz-1] > set->elements[poz]) {
	  	int aux = set->elements[poz-1];
	  	set->elements[poz-1] = set->elements[poz];
	  	set->elements[poz] = aux;
	  	poz--;
	  }
  }
  
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the union of
  the two
*/

OrderedSet* unionOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  
	OrderedSet* reuniune = createOrderedSet(s1->size + s2->size);

	for ( int i = 0 ; i < s1->size ; i++) {
			add(reuniune , s1->elements[i]);
	}


	for ( int i = 0 ; i < s2->size ; i++) {
			add(reuniune , s2->elements[i]);
	}
  return reuniune;
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the
  intersection of the two
*/

OrderedSet* intersectOrderedSets(OrderedSet* s1, OrderedSet* s2) {

  OrderedSet* intersectie= createOrderedSet(s1->size + s2->size);
  for ( int i = 0 ; i < s1->size ; i++) {
		if ( contains(s2, s1->elements[i]) == 1) {
			add(intersectie , s1->elements[i]);
		}
	}
 
  return intersectie;
}


// -----------------------------------------------------------------------------

#endif
