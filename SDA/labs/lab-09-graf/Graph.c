#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"

TGraphL* createGraphAdjList(int numberOfNodes) {
	//TODO: 1
	TGraphL *graf = (TGraphL *) malloc(sizeof(TGraphL));
	graf->nn = numberOfNodes;
	graf->adl = (ATNode *) malloc(numberOfNodes * sizeof(ATNode));
	for (int i = 0; i < numberOfNodes; i++) {
		graf->adl[i] = NULL;
	}
	return graf;
}

void addEdgeList(TGraphL* graph, int v1, int v2) {
	//TODO: 1
	ATNode nod_one = (ATNode) malloc(sizeof(TNode));
	nod_one->v = v2;
	nod_one->next = NULL;
	
	if (graph->adl[v1] == NULL) {
		graph->adl[v1] = nod_one;
	} else {
		nod_one->next = graph->adl[v1];
		graph->adl[v1] = nod_one;
	}


	ATNode nod_two = (ATNode) malloc(sizeof(TNode));
	nod_two->v = v1;
	nod_two->next = NULL;
	
	if (graph->adl[v2] == NULL) {
		graph->adl[v2] = nod_two;
	} else {
		nod_two->next = graph->adl[v2];
		graph->adl[v2] = nod_two;
	}
	return ;
}

void dfsRecHelper(TGraphL* graph, int* visited, List* path, int s) {
	//TODO: 2
	// DFS -> stiva
	enqueue(path, s);
	visited[s] = 1;
	ATNode vecin = graph->adl[s];
	while (vecin != NULL) {
		// facem dfs pentru fiecare vecin in parte al nodului
		// accesam vecin 1 facem dfs
		// accesam vecin 2 facem dfs
		// etc
		if (visited[vecin->v] == 0) {
			dfsRecHelper(graph, visited, path, vecin->v);
		}
		vecin = vecin->next;
	}

}

List* dfsRecursive(TGraphL* graph, int s) {
	// TODO 2
	// DFS -> stiva
	int *visited = (int *) malloc(graph->nn * sizeof(int));
	for (int i = 0; i < graph->nn; i++) {
		visited[i] = 0;
	}
	List *path = createList();
	dfsRecHelper(graph, visited, path, s);
	
	// eliberam memoria folosita
	free(visited);
	return path;
}

List* bfs(TGraphL* graph, int s){
	// TODO: 3
	// BFS -> coada
	Queue *coada = createQueue();
	List *path = createList();
	int *visited = (int *) malloc(graph->nn * sizeof(int));
	for (int i = 0; i < graph->nn; i++) {
		visited[i] = 0;
	}

	enqueue(coada, s);
	int nr_parcurse = 0;
	while (nr_parcurse != graph->nn) {
		int nod = front(coada);
		dequeue(coada);
		enqueue(path, nod);
		visited[nod] = 1;
		ATNode vecin = graph->adl[nod];
		nr_parcurse++;
		while (vecin != NULL) {
			// facem dfs pentru fiecare vecin in parte al nodului
			// accesam vecin 1 facem dfs
			// accesam vecin 2 facem dfs
			// etc
			if (visited[vecin->v] == 0) {
				visited[vecin->v] = 1;
				enqueue(coada, vecin->v);
			}
			vecin = vecin->next;
		}

	}

	free(visited);
	destroyQueue(coada);
	return path;
}


void destroyGraphAdjList(TGraphL* graph){
	// TODO: 4
	for (int i = 0; i < graph->nn; i++) {
		while (graph->adl[i] != NULL) {
			ATNode aux= graph->adl[i];
			graph->adl[i] = graph->adl[i]->next;
			free(aux);
		}
		//free(graph->adl);
	}
	free(graph->adl);
	free(graph);
}

void removeEdgeList(TGraphL* graph, int v1, int v2){
	TNode* it = graph->adl[v1];
	TNode* prev = NULL;
	while(it != NULL && it->v != v2){
		prev = it;
		it = it->next;
	}

	if(it == NULL)return;

	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v1] = it->next;
	free(it);

	it = graph->adl[v2];
	prev = NULL;
	while(it != NULL && it->v != v1){
		prev = it;
		it = it->next;
	}
	if(it == NULL) return;
	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v2] = it->next;

	free(it);
}

void removeNodeList(TGraphL* graph, int v){
	for(int i = 0; i < graph->nn;i++){
		removeEdgeList(graph,v,i);
	}
}
