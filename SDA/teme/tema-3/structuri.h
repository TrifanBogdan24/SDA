// TRIFAN BOGDAN-CRISTIAN, 312 CD, SIMIGRUPA I
// TEMA 3 - S.D.A
#ifndef __STRUCTURI_H__
#define __STRUCTURI_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIGIT_ZERO '0'
#define DIGIT_NINE '9'
#define ONE_STRING "1"
#define TWO_STRING "2"
#define STRING_INSULA "Insula"
#define STRING_CORABIE "Corabie"
#define NEG_UNU -1
#define ZERO 0
#define UNU 1
#define DOI 2
#define ZECE 10
#define DOUA_ZECI 20
#define TREI_ZECI 30
#define SUTA 100
#define INFINIT 999999

typedef struct muchie {
    int nod;    // unul dintre vecinii nodului
    int cost;   // costul de la nod la vecin
    float scor; // se va folosi DOAR pentru task-ul 2
} muchie;

typedef struct lista_inlantuita {
    muchie elem;
    struct lista_inlantuita *urm;
} element, *lista;

typedef struct graf {
	int N;              // nr de noduri din graf
    int M;              // nr de muchii din graf
    int nr_comps;       // numarul de componente conexe
    char **nume;        // denumirile nodurilor
	lista *adiacenta;   // vectorul cu listele de adiacenta
    int *componenta;    // in a cata componenta conexa face nodul parte
} *graf;

lista creare(int nod, int cost);

lista inserare_in_lista(lista lista_adiacenta, int inserare_nod,
                        int inserare_cost);

graf initializare_graf(int N, int M);

graf muchie_noua(graf g, int node_one, int node_two, int cost);

void graph_destruction(graf g);

void display_adiacenta(graf g);

void display_costuri_muchii(graf g);

void display_graph_information(graf g);

int is_digit(char c);

int convert_char_to_int(char *sir_input);

#endif
