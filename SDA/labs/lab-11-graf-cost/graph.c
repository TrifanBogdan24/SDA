#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

typedef int TCost;

typedef struct node
{
	int v;
	TCost c;
	struct node *next;
} TNode, *ATNode;

typedef struct
{
	int nn;
	ATNode *adl;
}	TGraphL;


void alloc_list(TGraphL * G, int n)
{
    int i;
    G->nn = n;
	G->adl = (ATNode*) malloc((n+1)*sizeof(ATNode));
	for(i = 0; i < n; i++)
		G->adl[i] = NULL;

}

void free_list(TGraphL *G)
{
    int i;
    ATNode it;
    for(i = 1; i < G->nn; i++){
		it = G->adl[i];
		while(it != NULL){
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->nn = 0;
}

void insert_edge_list(TGraphL *G, int v1, int v2, int c)
{
	TNode *t;
	t=(ATNode)malloc(sizeof(TNode));
	t->v = v2; t->c=c; t->next = G->adl[v1]; G->adl[v1]=t;
	t=(ATNode)malloc(sizeof(TNode));
	t->v = v1;  t->c=c; t->next = G->adl[v2]; G->adl[v2]=t;
}


void cost_muchii(TGraphL G)
{
	for (int i = 0; i < G.nn; i++) {
		ATNode nodul_adiacent_min = G.adl[i];
		while (nodul_adiacent_min) {
			printf("%d -> %d = %d\n", i, nodul_adiacent_min->v, nodul_adiacent_min->c);
			nodul_adiacent_min = nodul_adiacent_min->next;
		}
	} 
}

void dijkstra(TGraphL G, int s)
{
	int *distance = (int *) malloc(G.nn * sizeof(int));	// TCost
	int *visited = (int *) malloc(G.nn * sizeof(int));


	// initializare variabile
    for (int i = 0 ; i < G.nn ; i++) {
		visited[i] = 0;
		distance[i] = (int)99999;
	}

	// visited[s] = 1;

	int stop = 0;
	distance[s] = 0;
	while (!stop) {
		
		// iteram vectorul de distante si luam minumul care nu este visitat
		stop = 0;
		int idx_of_min = -1;
		int min_distance = (int)9999999;
		int there_is_a_good_node = 0;
		for (int i = 0; i < G.nn; i++) {
			if (!visited[i] && distance[i] <= min_distance) {
				idx_of_min = i;
				min_distance = distance[i];
				there_is_a_good_node = 1;
			}
		}

		if (!there_is_a_good_node) {
			// nodurile nu se mai pot relaxa
			stop = 1;
			break;
		} else {
			visited[idx_of_min] = 1;

			// incercam vizitarea vecinilor

			// afla distanta de la nodul idx_of_min la nodurile adiacente
			ATNode nodul_adiacent_min = G.adl[idx_of_min];
			while (nodul_adiacent_min) {
				int dist_to_i = distance[idx_of_min] + nodul_adiacent_min->c;
				if (!visited[nodul_adiacent_min->v] && distance[nodul_adiacent_min->v] > dist_to_i) {
					distance[nodul_adiacent_min->v] = dist_to_i;
				}
				nodul_adiacent_min = nodul_adiacent_min->next;
			}
		}
	}

	printf("\nDijsktra :\n");
	cost_muchii(G);
	printf("\n");
	printf("Varf     Drum minim\n");
	for (int i = 0; i < G.nn; i++) {
		printf(" %d      %d\n", i, distance[i]);
	}
	free(distance);
	free(visited);
}


void Prim(TGraphL G)
{
    int *visited = (int *)malloc(G.nn * sizeof(int));
	int *parinte = (int *)malloc(G.nn * sizeof(int));
	int *edges = (int *) malloc(G.nn * sizeof(int));
	int *vizitat = (int *)malloc(G.nn * sizeof(int));

	// initialization
	for (int i = 0; i < G.nn; i++) {
		vizitat[i] = 0;
		edges[i] = (int)99999;
	}
	edges[0] = 0;

	int stop = 0;
	while (!stop) {
		stop = 0;
		int idx_of_min = -1;
		int min_edge = (int)9999999;
		
		for (int i = 0; i < G.nn; i++) {
			if (!vizitat[i] && edges[i] <= min_edge) {
				idx_of_min = i;
				min_edge = edges[i];
			}
		}

		if (idx_of_min == -1) {
			stop = 1;
			break;
		}
		
		vizitat[idx_of_min] = 1;
		
		ATNode nodul_adiacent_min = G.adl[idx_of_min];
		while (nodul_adiacent_min) {
			int nod_adiacent = nodul_adiacent_min->v;
			int cost_muchie = nodul_adiacent_min->c;
			if (!vizitat[nod_adiacent] && cost_muchie < edges[nod_adiacent]) {
				edges[nod_adiacent] = cost_muchie;
				parinte[nod_adiacent] = idx_of_min;
			}
			nodul_adiacent_min = nodul_adiacent_min->next;
		}
	}

	printf("\nPrim :\n");
	cost_muchii(G);
	printf("\n");
	printf("Parinte     Varf\n");
	int sum_total = 0;
	for (int i = 0; i < G.nn; i++) {
		printf("   %d         %d\n", parinte[i], i);
		sum_total += edges[i];
	}
	printf("\nCostul drumului minim = %d\n", sum_total);
	free(edges);
	free(parinte);
	free(visited);
}

int main()
{
    int i,v1,v2,c;
	int V,E;
	TGraphL G;
	ATNode t;
	freopen ("graph.in", "r", stdin);
	scanf ("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i=1; i<=E; i++)
	{
		scanf("%d %d %d", &v1, &v2, &c);
	    insert_edge_list(&G, v1,v2, c);
	}

	for(i=0;i<G.nn;i++)
	{
    	printf("%d : ", i);
    	for(t = G.adl[i]; t != NULL; t = t->next)
   			 printf("%d ",t->v);
    		 printf("\n");
	}
	dijkstra(G,0);
	Prim(G);

	return 0;
}
