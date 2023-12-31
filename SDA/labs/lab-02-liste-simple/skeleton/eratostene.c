#include <stdio.h>

typedef int T;
#include "SortedList.h"

TSortedList getNaturals(int A, int B) {
    TSortedList nats = NULL;
    int i;
    for (i = A; i <= B; i++) {
        nats = insert(nats, i);
    }
    return nats;
}

TSortedList getPrimes(int N) {
    TSortedList nats = getNaturals(2, N);

    // TODO: Cerința Bonus
    TSortedList santinela = nats;
    while( santinela != NULL) {
        for( int i = 2; i <= N / santinela->value ; i++) {
            santinela = deleteOnce(santinela , santinela->value * i);
        }
        santinela = santinela->next;

    }
    return nats;
}

void printInts(TSortedList list) {
    while (!isEmpty(list)) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    printInts(getPrimes(100));
    return 0;
}
