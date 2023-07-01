#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

typedef struct MinHeapNode
{
    int v;
    int d;
} MinHeapNode;


typedef struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    MinHeapNode **elem;
} MinHeap;


MinHeapNode* newNode(int v, int d)
{
    MinHeapNode *new_node = (MinHeapNode *) malloc(sizeof(MinHeapNode));
    new_node->v = v;
    new_node->d = d;
    return new_node;
}

MinHeap* newQueue(int capacity)
{
    MinHeap *new_queue = (MinHeap *) malloc(capacity * sizeof(MinHeap));
    new_queue->size = capacity;
    new_queue->capacity = capacity;
    new_queue->pos = (int *) malloc(capacity * sizeof(int));
    return new_queue;

}

void swap(MinHeapNode** a, MinHeapNode** b)
{
    MinHeapNode *aux = *a;
    *a = *b;
    *b = aux;
}

void SiftDown(MinHeap* h, int idx)
{
    int left_child = 2 * idx + 1;
    int right_child = 2 * idx + 2;
    int minimum = idx;
    
    if (left_child < h->size && h->elem[left_child]->d < h->elem[minimum]->d) {
        minimum = left_child;
    }

    if (right_child < h->size && h-> elem[right_child]->d < h->elem[minimum]->d) {
        minimum = right_child;
    }

    if (minimum != idx) {
        swap(&h->elem[minimum], &h->elem[idx]);
        SiftDown(h, minimum);
    }
}

int isEmpty(MinHeap* h)
{
    if (!h) return 0;
    if (!h->size) return 0;
    if (!h->capacity) return 0;
    return 1;
}

MinHeapNode* removeMin(MinHeap* h)
{
    MinHeapNode *first_node = h->elem[0];
    MinHeapNode *ultim_node = h->elem[h->size - 1];
    h->size--;
    h->elem[0] = ultim_node;
    SiftDown(h, 0);
    return first_node;
}

void SiftUp(MinHeap* h, int v, int d)
{
    int i = 0;
    int idx = 0;
    while (i < h->size) {
        if (h->elem[i]->v == v && h->elem[i]->d == d) {
            idx = i;
            break;
        }
        i++;
    }
    int parent = floor((idx - 1) / 2);

    while (parent >= 0 && h->elem[parent]->d > h->elem[idx]->d) {
        swap(&h->elem[parent], &h->elem[idx]);
        idx = parent;
        parent = floor((idx - 1) / 2);
    }
}

int isInMinHeap(MinHeap *h, int v)
{
    return 1;
}

#endif

