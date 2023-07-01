#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */
typedef struct {
	int prior; // Item priority
	Item data; // Item d
}ItemType;

typedef struct heap {
	long maxHeapSize; // capacity
	long size; // number of elements
	ItemType *elem; // array of elements
} PriQueue, *APriQueue;


PriQueue* makeQueue(int maxHeapSize) {
	//TODO:
	PriQueue *new_heap = (PriQueue *) malloc(sizeof(PriQueue));
	new_heap -> elem = (ItemType *) calloc(maxHeapSize, sizeof(ItemType));
	new_heap -> maxHeapSize = maxHeapSize;
	new_heap -> size = 0;
	return new_heap;
}

int getLeftChild(int i) {
	//TODO:
	return (2*i+1);
}

int getRightChild(int i) {
	//TODO:
	return (2*i+2);
}

int getParent(int i) {
	//TODO:
	return (i-1)/2;
}

ItemType getMax(APriQueue h) {
	//TODO:

	/*
	ItemType elem_max_prior = h->elem[0];
	for (int i = 2; i < h->size; i++) {
		if ( h->elem[i].prior > elem_max_prior.prior) {
			// elementul i are o prioritate mai mare decat elementul retinut
			elem_max_prior = h->elem[i];
		}
	}
	return elem_max_prior;  // aparent, elem_max_prior = h->elem[0];
	*/

	return h->elem[0];
}

void siftUp(APriQueue h, int idx) {
	//TODO:
	int idx_parinte = getParent(idx);
	if (idx_parinte >= 0 && h->elem[idx_parinte].prior < h->elem[idx].prior) {
		ItemType aux= h->elem[idx];
		h->elem[idx] = h->elem[idx_parinte];
		h->elem[idx_parinte] = aux;
		siftUp(h, idx_parinte);
	}
	return ;
}


void insert(PriQueue *h, ItemType x) {
	//TODO:
	h->elem[h->size] = x;
	siftUp(h, h->size);
	h->size++;
	if (h->maxHeapSize == h->size) {
		// heap-ul are mai multe elemente decat ne-am asteptat
		// trebuie sa alocam memorie suplimentara pentru ele
		h->maxHeapSize = 2 * h->size;
		h->elem = (ItemType *) realloc(h->elem, h->maxHeapSize * sizeof(ItemType));
	}
}

void swap_it(ItemType *a,ItemType *b) {
	ItemType aux = *a;
	*a = *b;
	*b = aux;
	return ;
}


void siftDown(APriQueue h, int idx){
	//TODO:
	int idx_stanga = getLeftChild(idx);		// idx * 2 + 1
	int idx_dreapta = getRightChild(idx);	// idx * 2 + 2
	
	if (idx >= h->size) return ;

	ItemType parent = h->elem[idx];

	if (idx_stanga < h->size) {
		
		ItemType fiu_stanga = h->elem[idx_stanga];

		if (parent.prior < fiu_stanga.prior) {
			swap_it(&h->elem[idx_stanga], &h->elem[idx]);
			siftDown(h, idx_stanga);
		}

	} else if (idx_dreapta < h->size) {

		ItemType fiu_stanga = h->elem[idx_stanga];
		ItemType fiu_dreapta = h->elem[idx_dreapta];

		if (parent.prior < fiu_stanga.prior && parent.prior < fiu_dreapta.prior) {
			
			if (fiu_dreapta.prior < fiu_stanga.prior) {
				swap_it(&h->elem[idx_stanga], &h->elem[idx]);
				siftDown(h, idx_stanga);
			} else {
				swap_it(&h->elem[idx_dreapta] , &h->elem[idx]);
				siftDown(h, idx_dreapta);
			}

		} else if (parent.prior < fiu_dreapta.prior) {
			swap_it(&h->elem[idx_dreapta], &h->elem[idx]);
			siftDown(h, idx_dreapta);
		}
	}
	
}

// metoda 1 - complexitate O(n)
/*
void removeMax(APriQueue h) {
	//TODO:
	if (h->size == 1) {
		h->size = 0;
		return ;
	} else {
		for (int i = 0; i <= h->size - 2; i++) {
			h->elem[i] = h->elem[i+1];
		}
		h->size -= 1;
		return ;
	}
	return ;
}
*/

// metoda 2 - complexitate O(n * log(n))
void removeMax(APriQueue h) {
	//TODO:
	h->elem[0] = h->elem[h->size - 1];
	int idx_parinte = 0;
	int idx_stanga = getLeftChild(idx_parinte);		// 2 * 2 + 1
	int idx_dreapta = getRightChild(idx_parinte);	// 2 * 0 + 2
	h->size -= 1;
	siftDown(h, 0);
	return ;
}
void freeQueue(APriQueue h) {
	// TODO:
	
	// for (int i = 0; i < (*h).size; i++) {
	// 	free(h->elem[i]);
	// }
	free(h->elem);
	free(h);
	return;
}

#endif

