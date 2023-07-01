#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>
#include <assert.h>

/*
    IMPORTANT!

    As we stick to pure C, we cannot use templates. We will just asume
    some type T was previously defined.
*/

// -----------------------------------------------------------------------------

typedef struct node {
    T value;
    struct node* next;
} TNode, *TSortedList;


TSortedList create(T value) {
    TSortedList new_node = (TSortedList) malloc(sizeof(TNode));
    new_node->value = value;
    new_node->next = NULL; 
    return new_node;
}

// TODO : Cerința 1 & Cerința 2

int isEmpty(struct node *TLista) {
	return (TLista==NULL) ;
}


int contains(struct node *TLista, int x) {
	while(TLista != NULL) {
	if(TLista->value == x) return 1;
	TLista = TLista->next;
	}
	return 0;
}


TSortedList insert(TSortedList TLista, int x) {
	TSortedList prim = create(0); // prim va memora intotdeauna adresa primului element din lista
	prim = TLista;
	
	TSortedList new_nod = create(x);
	
	if( TLista== NULL) prim = new_nod; // lista vida
	else if (x < TLista->value) { // inserare la inceput de lista
		new_nod -> next = TLista;
		// N = new_nod;
		prim = new_nod;
	} else {
		while(TLista->next != NULL && TLista->next->value < x ) TLista = TLista->next;  // vom insera intre N si N->next
		if(TLista->next == NULL ) TLista->next = new_nod; // inseram la finalul listei
		else {   // inseram undeva in interior, nici la final, nici la inceput
			new_nod->next = TLista->next;
			TLista->next = new_nod;		}
			
	}
	return prim;
}



TSortedList deleteOnce(TSortedList TLista, int x) {
	TSortedList prim = create(0); // prim va memora intotdeauna adresa primului element din lista
	prim = TLista;
	
	TSortedList aux = create(0);
	if(TLista != NULL) {
		if(TLista->value == x) {
			// stergere la inceput de lista
			TSortedList aux = create(0);
			aux = TLista;
			TLista = TLista->next; 
			free(aux);
			return TLista;
		} else {
			TSortedList prev = create(0);
			prev->next = TLista;
			while(TLista!=NULL && TLista->value != x) {
				prev = prev->next;
				TLista = TLista->next;
			}

			if(TLista!=NULL) {
				if(TLista->next == NULL) {
					// stergere de la final
					TLista = NULL;
					prev -> next = NULL;
					free(TLista);
				} else {
					// il vom sterge pe TLista, care este situat intre doua elemente
					TSortedList aux = create(0);
					aux = TLista;
					prev->next = TLista->next;
					free(aux);
				}
			}
		}
	}
	return prim;
}


long length(TSortedList TLista)
{
	
	TSortedList it = TLista;
	long nr = 0; 
	while(it != NULL) {
		it = it->next;
		nr++;
	}
	return nr;

}

int getNth(TSortedList TLista, int N) {
	while(TLista != NULL && N!=1) {
		N = N -1;
		TLista = TLista->next;
	}
	if(N==1) return TLista->value;
	
}

TSortedList freeTSortedList(TSortedList TLista) 
{
	while(TLista != NULL) {
		TSortedList aux = create(0); 
		aux = TLista;
		TLista = TLista->next;
		free(aux); 
	}
	return TLista; // va returna NULL
}







#endif
