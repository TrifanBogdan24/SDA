// TRIFAN BOGDAN-CRISTIAN, 312 CD, SEMIGRUPA I
// TEMA 3 - S.D.A.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structuri.h"

lista creare(int nod, int cost)
{
    lista new_node = (lista)malloc(sizeof(element));
    new_node->elem.nod = nod;
    new_node->elem.cost = cost;
    new_node->elem.scor = NEG_UNU;  // se va folosi DOAR la task-ul 2
    new_node->urm = NULL;
    return new_node;
}

lista inserare_in_lista(lista lista_adiacenta, int inserare_nod,
                        int inserare_cost)
{
    // vom insera intotdeauna la finalul listei
	lista new_nod = creare(inserare_nod, inserare_cost);
    // printf("Avem de inserat spre nodul ");
    // printf("%d costul %d\n", inserare_nod, inserare_cost);
	if (!lista_adiacenta) {
        lista_adiacenta = new_nod; // lista vida
        return lista_adiacenta;
    }

    if (lista_adiacenta) {
        // pentru coding-style, caci e mai greu sa scriu frumos une else
        lista iterator = lista_adiacenta;
        while (iterator->urm)
            iterator = iterator->urm;

        iterator->urm = new_nod;
        return lista_adiacenta;
    }

	return lista_adiacenta;
}

graf initializare_graf(int N, int M)
{
	graf g = (graf)malloc(sizeof(struct graf));
	g->N = N;
    g->M = M;
    g->nr_comps = ZERO; // graful are initial 0 componente conexe
	
    g->adiacenta = (lista *)malloc(N * sizeof(lista));
    g->componenta = (int *)malloc(N * sizeof(int));
    g->nume = (char **)malloc(N * sizeof(char *));

	for (int i = ZERO; i < N; i++) {
        g->nume[i] = (char *)malloc(DOUA_ZECI * sizeof(char));
        strcpy(g->nume[i], "-");
		g->adiacenta[i] = NULL;
        g->componenta[i] = NEG_UNU;
	}
	return g;
}

graf muchie_noua(graf g, int nod_sursa, int nod_destinatie, int cost)
{
    // daca graful este neorientat (cerinta 1), apelam de doua ori
    // printf("Inseram muchia %d -> %d", node_one, node_two);
    g->adiacenta[nod_sursa] = inserare_in_lista(g->adiacenta[nod_sursa],
                                                nod_destinatie, cost);

    // printf("\n");
    return g;
}

void graph_destruction(graf g)
{
    free(g->componenta);
    for (int i = ZERO; i < g->N; i++) {
        free(g->nume[i]);

        lista iterator = g->adiacenta[i];
        while (iterator) {
            lista aux = iterator;
            iterator = iterator->urm;
            free(aux);
        }
    }

    free(g->nume);
    free(g->adiacenta);
    free(g);
}

void display_adiacenta(graf g)
{
    printf("\nlista de adiacenta :\n");
    for (int i = ZERO; i < g->N; i++) {
        printf("%d : ", i);
        int nr = ZERO;
        lista iterator = g->adiacenta[i];

        while (iterator) {
            nr++;
            printf("%d", iterator->elem.nod);
            if (iterator->urm)
                printf(", ");
            iterator = iterator->urm;
        }

        if (!nr)
            printf("-");
        printf("\n");
    }
}

void display_costuri_muchii(graf g)
{
    printf("\nCosturi :\n");
    for (int i = ZERO; i < g->N; i++) {
        lista iterator = g->adiacenta[i];
        while (iterator) {
            printf("%d -> %d = ", i, iterator->elem.nod);
            printf("%d\n", iterator->elem.cost);
            iterator = iterator->urm;
        }
    }
}

void display_graph_information(graf g)
{
    printf("graful are %d noduri.\n", g->N);
    display_adiacenta(g);
    display_costuri_muchii(g);
}

int is_digit(char c)
{
    // functia returneaza 1 daca caracterul primit este o cifra
    // si 0 altfel
    if (c < DIGIT_ZERO || c > DIGIT_NINE)
        return ZERO;
    return UNU;
}

int convert_char_to_int(char *sir_input)
{
    // functia returneaza numarul primit ca parametru
    // la primul caracter non-cifra gasit, vom returna numarul
    int nr = ZERO;
    for (int i = ZERO; i < strlen(sir_input); i++) {
        if (is_digit(sir_input[i]))
            nr = nr * ZECE + sir_input[i] - DIGIT_ZERO;
        else
            return nr;
    }
    return nr;
}
