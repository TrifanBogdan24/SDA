// TRIFAN BOGDAN-CRISTIAN, 312 CD, SEMIGRUPA I
// TEMA 3 - S.D.A.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structuri.h"
#include "task2.h"

int denumire_nod_to_indice(char *nume, int nr_noduri)
{
    if (strcmp(nume, STRING_INSULA) == ZERO)
        return ZERO;

    if (strcmp(nume, STRING_CORABIE) == ZERO)
        return (nr_noduri - UNU);

    // de la sirul 'Nod_i', va returna i
    int i = ZERO;
    while (!is_digit(nume[i]) && i < strlen(nume))
        i++;

    int indice_nod = convert_char_to_int(nume + i) - UNU;
    // printf("\n\n%s = %d\n\n", nume + i, indice_nod);
    return indice_nod;
}


void indice_nod_to_denumire(FILE *fout, int nod, int N)
{
    if (nod == ZERO) {
        fprintf(fout, STRING_INSULA);
        fprintf(fout, " ");
        return;
    }

    if (nod == N - UNU) {
        fprintf(fout, STRING_CORABIE);
        return;
    }

    nod++;
    fprintf(fout, "Nod_");
    int *inv_number = (int *)malloc(ZECE * sizeof(int));
    int lungime = ZERO;
    do {
        inv_number[lungime++] = nod % ZECE;
        nod = nod / ZECE;
    } while (nod);

    for (int i = lungime - UNU; i >= ZERO; i--)
        fprintf(fout, "%d ", inv_number[i]);

    free(inv_number);
}

void name_of_idx(char *name, int nod, int N)
{
    if (nod == ZERO) {
        strcpy(name, STRING_INSULA);
        return;
    }

    if (nod == N - UNU) {
        strcpy(name, STRING_CORABIE);
        return;
    }

    nod++;
    strcpy(name, "Nod_");
    int *inv_number = (int *)malloc(ZECE * sizeof(int));
    int lungime = ZERO;
    do {
        inv_number[lungime++] = nod % ZECE;
        nod = nod / ZECE;
    } while (nod);

    for (int i = ZERO; i < lungime; i++)
        name[4 + i] = inv_number[i] + DIGIT_ZERO;

    free(inv_number);
}

void prelucrare_linie_muchii(char *linie_muchie, graf g)
{
    char *p = strtok(linie_muchie, " ");
    // printf("%s -> ", p);
    int sursa = denumire_nod_to_indice(p, g->N);

    p = strtok(NULL, " ");
    // printf("%s = ", p);
    int destinatie = denumire_nod_to_indice(p, g->N);

    p = strtok(NULL, " ");
    // printf("%s", p);
    int cost_muchie = convert_char_to_int(p);
    // printf("%d -> %d = %d\n\n", sursa, destinatie, cost_muchie);

    g = muchie_noua(g, sursa, destinatie, cost_muchie);
}

void reverse_search(FILE *fout, int nod, graf g, int *precedent)
{
    if (nod == ZERO) {
        indice_nod_to_denumire(fout, nod, g->N);
        return;
    }

    reverse_search(fout, precedent[nod], g, precedent);
    indice_nod_to_denumire(fout, nod, g->N);
}

float adancime_minima(graf g, int *precedent, int *adancime)
{
    int nod = g->N - UNU;
    float raspuns = adancime[precedent[nod]];
    while (precedent[nod]) {
        if (adancime[precedent[nod]] < raspuns)
            raspuns = adancime[precedent[nod]];

        nod = precedent[nod];
    }
    return (int)raspuns;
}

void dijsktra_algorithm(FILE *fout, graf g, int *adancime, int greutate)
{
    float *scoruri = (float *)malloc(g->N * sizeof(float));
    int *distanta = (int *)malloc(g->N * sizeof(int));
	int *vizitat = (int *)malloc(g->N * sizeof(int));
    int *precedent = (int *)malloc(g->N * sizeof(int));

	// initializare variabile
    for (int i = ZERO ; i < g->N ; i++) {
		vizitat[i] = ZERO;
        distanta[i] = INFINIT;
		scoruri[i] = INFINIT;
        precedent[i] = NEG_UNU;
	}

	int stop = ZERO;
	distanta[ZERO] = ZERO;
    scoruri[ZERO] = ZERO;

	while (!stop) {
		// iteram vectorul de scoruri si luam minumul care nu este vizitat
        // luam scorul minim
		stop = ZERO;
		int idx_of_min = NEG_UNU;
        int min_scor = INFINIT;
		int there_is_a_good_node = ZERO;
		for (int i = ZERO; i < g->N; i++) {
			if (!vizitat[i] && scoruri[i] < min_scor) {
				idx_of_min = i;
				min_scor = scoruri[i];
				there_is_a_good_node = UNU;
			}
		}

		if (!there_is_a_good_node) {
			// nodurile nu se mai pot relaxa
			stop = UNU;
			break;
		}

        vizitat[idx_of_min] = UNU;

        // incercam vizitarea vecinilor
        // aflam distanta de la nodul idx_of_min la nodurile adiacente
        lista iterator_muchii = g->adiacenta[idx_of_min];
        while (iterator_muchii) {
            int nod_vecin = iterator_muchii->elem.nod;

            int dist_to_i = distanta[idx_of_min];
            dist_to_i += iterator_muchii->elem.cost;

            float scor_to_i = scoruri[idx_of_min];
            scor_to_i += (float)(iterator_muchii->elem.cost) /
                         adancime[nod_vecin];

            if (!vizitat[nod_vecin] && scoruri[nod_vecin] > scor_to_i) {
                distanta[nod_vecin] = dist_to_i;
                scoruri[nod_vecin] = scor_to_i;
                precedent[nod_vecin] = idx_of_min;
            }
            iterator_muchii = iterator_muchii->urm;
        }
	}

    // suma muchiilor :
    reverse_search(fout, g->N - UNU, g, precedent);
    fprintf(fout, "\n%d\n", distanta[g->N - UNU]);

    // adancimea minima a nodurilor care nu sunt insula / corabie
    int greutate_maxima = adancime_minima(g, precedent, adancime);
    fprintf(fout, "%d\n", greutate_maxima);

    // nuamrul de drumuri = grautate / adancimea_minima
    fprintf(fout, "%d\n", greutate / greutate_maxima);

    free(precedent);
    free(distanta);
	free(vizitat);
    free(scoruri);
}

void DFS(graf g, int nod_inceput, int *vizitat)
{
    vizitat[nod_inceput] = UNU;
    lista iterator_muchii = g->adiacenta[nod_inceput];
    while (iterator_muchii) {
        int nod_vecin = iterator_muchii->elem.nod;
        if (!vizitat[nod_vecin])
            DFS(g, nod_vecin, vizitat);

        iterator_muchii = iterator_muchii->urm;
    }
}

int exista_drum_intre_noduri(graf g, int nod_initial, int nod_final)
{
    int *vizitat = (int *)malloc(g->N * sizeof(int));
    for (int i = ZERO; i < g->N; i++)
        vizitat[i] = ZERO;

    // vom face DFS pornind de la nodul initial
    // daca nodul final a fost parcurs,
    // atunci inseamna ca exista drum intre cele doua noduri
    DFS(g, nod_initial, vizitat);
    int stare_nod_final = vizitat[nod_final];
    free(vizitat);  // 1 daca a fost parcurs si 0 altfel
    return stare_nod_final;
}

void calculare_scor(graf g, int *adancime)
{
    for (int i = ZERO; i < g->N; i++) {
        lista iterator_muchii = g->adiacenta[i];
        while (iterator_muchii) {
            int nod_vecin = iterator_muchii->elem.nod;
            int cost_muchie = iterator_muchii->elem.cost;

            iterator_muchii->elem.scor = (float)(cost_muchie) /
                                         adancime[nod_vecin];
            iterator_muchii = iterator_muchii->urm;
        }
    }
}

void solve_task_two(FILE *fin, FILE *fout)
{
    int N = ZERO, M = ZERO;
    fscanf(fin, "%d", &N);
    fscanf(fin, "%d\n", &M);
    // printf("N = %d\nM = %d\n", N, M);
    graf g = initializare_graf(N, M);
    /*
    Insula -> de fapt nodul 0 in graf
    Nod_2  -> de fapt nodul 1 in graf
    ...
    Nodul_(N-1) -> de fapt nodul (N-2) in graf
    Corabie -> de fapt nodul (N-1) in graf
    */
   for (int i = ZERO; i < N; i++) {
        name_of_idx(g->nume[i], i, N);
        // printf("%d : %s\n", i, g->nume[i]);
   }

    int nod_insula = ZERO;
    int nod_corabie = N - UNU;
    char *linie_citita = (char *)malloc(SUTA * sizeof(char));
    for (int i = ZERO; i < M; i++) {
        fgets(linie_citita, SUTA, fin); // liniile contin si caracterul '\n'
        // printf("%s", linie_citita);
        prelucrare_linie_muchii(linie_citita, g);
    }

    int *adancime = (int *)malloc(N * sizeof(int));
    for (int i = ZERO; i < N; i++) {
        fgets(linie_citita, SUTA, fin); // liniile contin si caracterul '\n'
        // printf("%s", linie_citita);
        char *p = strtok(linie_citita, " ");
        int indice_nod = denumire_nod_to_indice(p, N);
        // printf("%d -> ", indice_nod);
        p = strtok(NULL, " ");
        int adanc = convert_char_to_int(p);
        // printf("%d\n", adanc);
        adancime[indice_nod] = adanc;
    }

    // display_adiacenta(g);
    // printf("\n\n");
    // display_costuri_muchii(g);

    int greutate_comoara = ZERO;
    fscanf(fin, "%d", &greutate_comoara);

    if (exista_drum_intre_noduri(g, nod_corabie, nod_insula) == ZERO) {
        fprintf(fout, "Echipajul nu poate ajunge la insula\n");
        free(linie_citita);
        free(adancime);
        graph_destruction(g);
        return;
    }

    if (exista_drum_intre_noduri(g, nod_insula, nod_corabie) == ZERO) {
        fprintf(fout, "Echipajul nu poate transporta ");
        fprintf(fout, "comoara inapoi la corabie\n");
        free(linie_citita);
        free(adancime);
        graph_destruction(g);
        return;
    }

    // daca am ajuns aici, insemna ca exista ambele drumuri
    // corabie -> insula -> corabie, deci trebuie sa facem Dijkstra
    calculare_scor(g, adancime);
    dijsktra_algorithm(fout, g, adancime, greutate_comoara);

    free(linie_citita);
    free(adancime);
    graph_destruction(g);
}
