/*
*	Created by Nan Mihai on 16.05.2022
*	Copyright (c) 2022 Nan Mihai. All rights reserved.
*	Laborator - Structuri de date și Algoritmi (Grafuri)
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2021-2022, Seria CD
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "graph.h"
#include "stack.h"

int check(int *v1, int *v2, int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (v1[i] != v2[i])
			return 0;
	}
	return 1;
}

/*
* Funcție care determină sortarea topologică pentru un graf orientat aciclic
* Obs: Rezultatul este reținut în vectorul result care a fost deja alocat!
*/

void dfsRecHelper(Graph graph, int* visited, Stack* path, int s) {
	visited[s] = 1;
	List vecin = graph->adjLists[s];
	while (vecin) {
		if (!visited[vecin->data.v]) {
			dfsRecHelper(graph,visited,path, vecin->data.v);
		}
		vecin = vecin->next;
	}
	*path = push(*path,s);
}

void dfsRecursive(Graph graph, int s, Stack* topS) {
	dfsRecHelper(graph, graph->visited, topS, s);
	return ;
}

void topologicalSort(Graph graph, int *result) {
	// TODO 1
	Stack stiva = NULL;
	
	for (int i = 0 ; i < graph->V ; i++) {
		graph->visited[i] = 0;
	}
	
	for (int i = 0 ; i < graph->V ; i++) {
		if (!graph->visited[i]) {
			dfsRecursive(graph, i, &stiva);
		}
	}
	
	int k = 0, varf = 0;
	while (!isEmptyStack(stiva)) {
		varf = top(stiva);
		stiva = pop(stiva);
		result[k] = varf;
		k += 1;
	}
	return;
}

/*
* Funcție care determină costurile drumurilor minime care pornesc din start
* Obs: Rezultatul este reținut în vectorul distances care a fost deja alocată!
*/
void BellmanFord(Graph graph, int start, int *distances) {
	// TODO 2
	for (int i = 0 ;i < graph->V ; i++)
		distances[i] = INFINITY;
	
	distances[start] = 0;
	
	for (int i = 1; i < graph->V - 1 ; i++) {
		for (int j = 0 ; j < graph->V ; j++) {
			List vecin = graph->adjLists[j];
			while (vecin) {
				if (distances[vecin->data.v] > distances[j] + vecin->data.cost ) {
					distances[vecin->data.v] = distances[j] + vecin->data.cost;
				}
				vecin = vecin->next;
			}
		}
	}
	return;
}

/*
* Funcție care determină costurile drumurilor minime de la orice nod la orice nod
* Obs: Rezultatul este reținut în matricea distances care a fost deja alocată!
*/
void FloydWarshall(Graph graph, int **distances) {
	// TODO 3
	int n = graph->V;

	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < n ; j++) {
			distances[i][j] = INFINITY;
		}
	}

	for (int j = 0 ; j < n ; j++) {
			List vecin = graph->adjLists[j];
			while (vecin) {
				distances[j][vecin->data.v] = vecin->data.cost;
				vecin = vecin->next;
			}
	}

	for (int k = 0 ; k < n ; k++) {
		for (int i = 0 ;i < n ; i++) {
			for (int j = 0 ; j < n ; j++) {
				if (distances[i][j] > distances[i][k] + distances[k][j] &&
					(distances[i][k] != INFINITY && distances[k][j] != INFINITY)) {
					distances[i][j] = distances[i][k] + distances[k][j];
				}
			}
		}
	}
	return;
}

int main() {
	freopen("test0.in", "r", stdin);
	int V, type, i, x, y, M, cost, j, ok;
	double punctaj = 0;
	int res1[] = {0, 1, 3, 5, 0, 3};
	int top1[] = {0, 3, 2, 1, 4, 5};
	scanf("%d %d", &V, &type);
	Graph graph = initGraph(V, type);
	scanf("%d", &M);
	for (i = 0; i < M; i++) {
		scanf("%d %d %d", &x, &y, &cost);
		graph = insertEdge(graph, x, y, cost);
	}
	printGraph(graph);
	drawGraph(graph, "graph0.dot");
	int *result;
	result = calloc(graph->V, sizeof(int));
	topologicalSort(graph, result);
	printf("\nRezultat sortarea topologica: ");
	for (i = 0; i < graph->V; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");
	if (check(result, top1, graph->V)) {
		printf("Corect\n");
		punctaj += 1.5;
	} else {
		printf("Incorect\n");
	}
	printf("\nRezultat Bellman Ford: ");
	BellmanFord(graph, 0, result);
	for (i = 0; i < graph->V; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");
	if (check(result, res1, graph->V)) {
		printf("Corect\n");
		punctaj += 1.5;
	} else {
		printf("Incorect\n");
	}
	
	printf("\nRezultat Floyd Warshall\n");
	int **distances;
	distances = malloc(graph->V * sizeof(int*));
	for (i = 0; i < graph->V; i++) {
		distances[i] = calloc(graph->V, sizeof(int));
	}
	FloydWarshall(graph, distances);
	FILE *fin = fopen("test0.ref", "r");
	ok = 1;
	for (i = 0; i < graph->V; i++) {
		for (j = 0; j < graph->V; j++) {
			printf("%6d ", distances[i][j]);
			fscanf(fin, "%d", &cost);
			if (cost != distances[i][j]) {
				ok = 0;
			}
		}
		free(distances[i]);
		printf("\n");
	}
	if (!ok) {
		printf("Incorect\n");
	} else {
		printf("Corect\n");
		punctaj += 1.5;
	}
	graph = freeGraph(graph);
	free(distances);
	free(result);
	fclose(fin);
	printf("=============================================\n");

	freopen("test1.in", "r", stdin);
	int top2[][7] = {{0, 3, 5, 2, 1, 4, 6}, {0, 3, 2, 1, 4, 5, 6},
					{0, 3, 2, 1, 5, 4, 6}, {0, 3, 2, 5, 1, 4, 6}};
	int res2[] = {0, 1, 3, 5, 0, 4, 3};
	scanf("%d %d", &V, &type);
	graph = initGraph(V, type);
	scanf("%d", &M);
	for (i = 0; i < M; i++) {
		scanf("%d %d %d", &x, &y, &cost);
		graph = insertEdge(graph, x, y, cost);
	}
	printGraph(graph);
	drawGraph(graph, "graph1.dot");
	result = calloc(graph->V, sizeof(int));
	topologicalSort(graph, result);
	printf("\nRezultat sortarea topologica: ");
	for (i = 0; i < graph->V; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");
	if (check(result, top2[0], graph->V) || check(result, top2[1], graph->V) ||
		check(result, top2[2], graph->V) || check(result, top2[3], graph->V)) {
		printf("Corect\n");
		punctaj += 1.5;
	} else {
		printf("Incorect\n");
	}
	printf("\nRezultat Bellman Ford: ");
	BellmanFord(graph, 0, result);
	for (i = 0; i < graph->V; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");
	if (check(result, res2, graph->V)) {
		printf("Corect\n");
		punctaj += 1.5;
	} else {
		printf("Incorect\n");
	}
	
	printf("\nRezultat Floyd Warshall\n");
	distances = malloc(graph->V * sizeof(int*));
	for (i = 0; i < graph->V; i++) {
		distances[i] = calloc(graph->V, sizeof(int));
	}
	FloydWarshall(graph, distances);
	fin = fopen("test1.ref", "r");
	ok = 1;
	for (i = 0; i < graph->V; i++) {
		for (j = 0; j < graph->V; j++) {
			printf("%6d ", distances[i][j]);
			fscanf(fin, "%d", &cost);
			if (cost != distances[i][j]) {
				ok = 0;
			}
		}
		free(distances[i]);
		printf("\n");
	}
	if (!ok) {
		printf("Incorect\n");
	} else {
		printf("Corect\n");
		punctaj += 1.5;
	}
	graph = freeGraph(graph);
	free(distances);
	free(result);
	fclose(fin);


	printf("=============================================\n");
	printf("Punctaj total: %.2lf\n", punctaj);
	printf("Observație: Se acordă 1p de către asistent dacă nu există erori / pierderi de memorie\n");
	return 0;
}
