// TRIFAN BOGDAN-CRISTIAN, 312 CD, SEMIGRUPA I
// TEMA 3 - S.D.A.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structuri.h"
#include "task1.h"

char **alocare_matrice_charuri(int nr_lin, int nr_col)
{
    char **char_matrix = (char **)malloc(nr_lin * sizeof(char *));
    for (int i = ZERO; i < nr_lin; i++)
        char_matrix[i] = (char *)malloc(nr_col * sizeof(char));
    return char_matrix;
}

int index_of_node_name(char *node_name, int nr_nodes, char **all_node_names)
{
    // functia returneaza al cateluia nod din graf ii este asociata o denumire
    // sau valoarea -1 daca aceasta nu se afla inca in graf
    for (int i = ZERO; i < nr_nodes; i++)
        if (strcmp(all_node_names[i], node_name) == ZERO)
            return i;

    return NEG_UNU;
}

void add_new_node_name(char *node_name, int *nr_nodes, char **all_node_names)
{
   strcpy(all_node_names[(*nr_nodes)], node_name);
   (*nr_nodes)++;
}

void prelucrare_linii(char *linie_citita, graf g, int *nr_noduri_indexate,
                      char **denumire_noduri)
{
    char *cuv_unu = (char *)malloc(TREI_ZECI * sizeof(char));  // primul nod
    char *cuv_doi = (char *)malloc(TREI_ZECI * sizeof(char));  // al doilea nod
    char *numar = (char *)malloc(ZECE * sizeof(char));     // costul drumului
    int index_node_one = NEG_UNU;
    int index_node_two = NEG_UNU;
    int cost_muchie = NEG_UNU;

    char *p = strtok(linie_citita, " ");
    strcpy(cuv_unu, p);
    if (index_of_node_name(cuv_unu, *nr_noduri_indexate, denumire_noduri)
        < ZERO)
        add_new_node_name(cuv_unu, nr_noduri_indexate, denumire_noduri);

    index_node_one = index_of_node_name(cuv_unu, *nr_noduri_indexate,
                                        denumire_noduri);

    p = strtok(NULL, " ");
    strcpy(cuv_doi, p);
    if (index_of_node_name(cuv_doi, *nr_noduri_indexate, denumire_noduri)
        < ZERO)
        add_new_node_name(cuv_doi, nr_noduri_indexate, denumire_noduri);

    index_node_two = index_of_node_name(cuv_doi, *nr_noduri_indexate,
                                        denumire_noduri);

    p = strtok(NULL, " ");
    strcpy(numar, p);
    cost_muchie = convert_char_to_int(p);

    // graful fiind neorientat, trebuie sa existe
    // atat muchia (i, j), cat si (j, i)
    // adica sa fie si vice-versa
    g = muchie_noua(g, index_node_one, index_node_two, cost_muchie);
    g = muchie_noua(g, index_node_two, index_node_one, cost_muchie);

    // printf("Ne costa '%d' sa reparam drumul de la ", cost_muchie);
    // printf("'%s' (nodul %d) la '%s' ", cuv_unu, index_node_one, cuv_doi);
    // printf("(nodul %d)\n", index_node_two);
    // printf("%d -> %d = ", index_node_one, index_node_two);
    // printf("%d -> %d = )", index_node_two, index_node_one);
    // printf("%d\n\n", cost_muchie);

    free(cuv_unu);
    free(cuv_doi);
    free(numar);
}

void DFS_pe_componente(graf g, int nod, int componenta)
{
    g->componenta[nod] = componenta;
    lista iterator_muchii = g->adiacenta[nod];
    while (iterator_muchii) {
        if (g->componenta[iterator_muchii->elem.nod] == NEG_UNU)
            DFS_pe_componente(g, iterator_muchii->elem.nod, componenta);

        iterator_muchii = iterator_muchii->urm;
    }
}

void impartire_componente_conexe(graf g)
{
    g->nr_comps = ZERO;
    for (int i = ZERO; i < g->N; i++) {
        if (g->componenta[i] == -1) {
            // nodul nu a fost vizitat, deci facem DFS din el,
            // iar toate nodurile la care putem ajunge fac parte
            // din aceeasi componenta conexa
            g->nr_comps++;
            DFS_pe_componente(g, i, g->nr_comps);
        }
    }
}

int prim_algorithm(graf g, int nod_inceput)
{
    // pointer-ul distanta = costul muchiile minime
    int *distanta = (int *)malloc(g->N * sizeof(int));
    int *vizitat = (int *)malloc(g->N * sizeof(int));

    // initializare variabile
    for (int i = ZERO; i < g->N; i++) {
        vizitat[i] = ZERO;
        distanta[i] = INFINIT;
        // initializam distanta ca fiind infinit, un numar mare
    }

    distanta[nod_inceput] = ZERO;
    int stop = ZERO;
    int indice_componenta = g->componenta[nod_inceput];
    while (!stop) {
        stop = ZERO;
        int min_dist = INFINIT;
        int idx_of_min = NEG_UNU;
		int there_is_a_good_node = ZERO;

        // cautam nodul cu cea mai mica distanta care nu a fost incă vizitat
        for (int i = ZERO; i < g->N; i++) {
            if (!vizitat[i] && g->componenta[i] == indice_componenta &&
                distanta[i] < min_dist) {
                min_dist = distanta[i];
                idx_of_min = i;
                there_is_a_good_node = 1;
            }
        }

        if (!there_is_a_good_node) {
            // nu mai exista noduri nevizitate, algoritmul a fost finalizat
            stop = NEG_UNU;
            break;
        }

        vizitat[idx_of_min] = UNU;

        // actualizam distantele vecinilor nodului selectat
        lista iterator_muchii = g->adiacenta[idx_of_min];
        while (iterator_muchii) {
            int nod_vecin = iterator_muchii->elem.nod;
            int cost_muchie = iterator_muchii->elem.cost;

            if (!vizitat[nod_vecin] &&
                g->componenta[nod_vecin] == indice_componenta &&
                cost_muchie < distanta[nod_vecin]) {
                distanta[nod_vecin] = cost_muchie;
            }

            iterator_muchii = iterator_muchii->urm;
        }
    }

    // calculam costul total al arborelui minim
    // adunam latura minima corespunzatoare fiecarui nod
    int cost_drum_total_comp = ZERO;
    for (int i = ZERO; i < g->N; i++)
        if (g->componenta[i] == indice_componenta)
            cost_drum_total_comp += distanta[i];

    free(distanta);
    free(vizitat);
    return cost_drum_total_comp;
}

void asc_order(int l, int *vect)
{
    for (int i = ZERO; i <= l - DOI; i++) {
        for (int j = i + UNU; j <= l - UNU; j++) {
            if (vect[i] > vect[j]) {
                int aux = vect[i];
                vect[i] = vect[j];
                vect[j] = aux;
            }
        }
    }
}

void rezolvare_task_1_2(FILE *fout, graf g)
{
    int *cost_drum_pe_componente = (int *)malloc(g->nr_comps * sizeof(int));
    for (int i = UNU; i <= g->nr_comps; i++) {
        int j = ZERO;
        while (j < g->N && g->componenta[j] != i)
            j++;

        cost_drum_pe_componente[i - UNU] = prim_algorithm(g, j);
        // fprintf(fout, "%d\n", Dijsktra(g, j));
    }
    asc_order(g->nr_comps, cost_drum_pe_componente);
    for (int i = ZERO; i < g->nr_comps; i++)
        fprintf(fout, "%d\n", cost_drum_pe_componente[i]);

    free(cost_drum_pe_componente);
}

void display_nodes(int nr_nodes, char **all_node_names)
{
    for (int i = ZERO; i < nr_nodes; i++)
        printf("%d = %s\n", i, all_node_names[i]);
}

void display_graph_components(graf g)
{
    printf("\ngraful are %d componente conexe.\n", g->nr_comps);
    for (int i = UNU; i <= g->nr_comps; i++) {
        printf("Componenta %d : ", i);
        for (int j = ZERO; j < g->N; j++)
            if (g->componenta[j] == i)
                printf("%d ", j);

        printf("\n");
    }
}

void solve_task_one(FILE *fin, FILE *fout)
{
    int N = ZERO, M = ZERO, nr_noduri_indexate = ZERO;
    fscanf(fin, "%d", &N);
    fscanf(fin, "%d\n", &M);
    // printf("N = %d\nM = %d\n", N, M);
    graf g = initializare_graf(N, M);
    char **denumire_noduri = alocare_matrice_charuri(M, TREI_ZECI);
    char *linie_citita = (char *)malloc(SUTA * sizeof(char));
    for (int i = ZERO; i < M; i++) {
        // fiecare linie va avea in aceasta ordine doua cuvinte si un numar
        fgets(linie_citita, SUTA, fin);
        // printf("%s\n", linie_citita);
        prelucrare_linii(linie_citita, g, &nr_noduri_indexate, denumire_noduri);
    }
    free(linie_citita);

    for (int i = ZERO; i < g->N; i++) {
        strcpy(g->nume[i], denumire_noduri[i]);
        // printf("%d : %s\n", i, denumire_noduri[i]);
    }
    
    impartire_componente_conexe(g);

    // display_nodes(N, denumire_noduri);
    // display_graph_information(graf);
    // display_graph_components(graf);

    // cerinta 1.1 : numarul de componente conexe
    fprintf(fout, "%d\n", g->nr_comps);

    // cerinta 1.2 : costul minim pe fiecare componenta conexa in parte
    rezolvare_task_1_2(fout, g);

    for (int i = ZERO; i < M; i++)
        free(denumire_noduri[i]);

    free(denumire_noduri);
    graph_destruction(g);
}
