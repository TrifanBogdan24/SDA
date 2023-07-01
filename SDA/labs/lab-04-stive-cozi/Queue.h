#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	Item elem;
	struct QueueNode *next;
}QueueNode;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	long size;
}Queue;

Queue* createQueue(void){
	// TODO: Cerinta 2
	Queue * coada = malloc(sizeof(Queue));
	coada->front = NULL;
	coada->rear = NULL;
	coada->size = 0;
	return coada;
} 

int isQueueEmpty(Queue *q){
	// TODO: Cerinta 2
	return !(q != NULL && q->front != NULL);
}

void enqueue(Queue *q, Item elem) {
	QueueNode * nou = malloc(sizeof(QueueNode));
	nou->elem = elem;
	nou->next = NULL;
	
	if (q == NULL) {
		// coada vida
		// q = createQueue();
		q = malloc(sizeof(Queue));
		q->front = q->rear = nou;
		q->size = 1;
		return;
	}
	
	if (q->front == NULL) {
		// coada are un element null
		q->front = q->rear = nou;
		q->size = 1;
		return;
	}

	// coada are cel putin un element
	q->rear->next = nou;
	q->rear = nou;
	q->size++;

	// TODO: Cerinta 2
}

Item front(Queue* q){
	// TODO: Cerinta 2
	if (q != NULL && q->front != NULL) {
		return q->front->elem;
	}
}

void dequeue(Queue* q){
	// TODO: Cerinta 2
	if (q == NULL || q->front == NULL)
		return;	// coada este vida
	
	QueueNode* stergator = q->front;
	q->front = q->front->next;
	free(stergator);
	q->size--;

	if (q->front == NULL) {
		// coada este vida
		q->rear = NULL;
		q->size = 0;
	}
}

void destroyQueue(Queue *q) {

	while (q->size) {
		dequeue(q);
	}

	if (q)
		free(q);
	// TODO: Cerinta 2
}

#endif
