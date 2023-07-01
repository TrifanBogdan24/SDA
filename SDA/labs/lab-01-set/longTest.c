#include <stdio.h>
#include <string.h>

typedef char T;
#include "OrderedSet.h"


void print_multime(OrderedSet* set_input) {
    for( int i = 0 ; i < set_input->size ; i++) printf("%d ", set_input->elements[i]);
    printf("\n");
    return ;
}


OrderedSet* interval_set(int x, int start , int stop) {
    while( start % x != 0 ) start++;
    OrderedSet* multime = createOrderedSet( stop/x - start/x +1);
    for( int i = start/x ; i <= stop/x ; i++ ) {
        add( multime, i*x);
    }
    return multime;
}

int main(int argc, char* argv[]) {
  
    OrderedSet* m1 = interval_set( 3 , 4 ,25);
    OrderedSet* m2 = interval_set( 4 , 5 , 30);
    OrderedSet* reuniune = unionOrderedSets( m1 , m2);
    OrderedSet* intersectie = intersectOrderedSets( m1 , m2);
    printf("Multimea multiplilor lui  3 din intervalul [4, 25] : ");
    print_multime(m1);
    printf("Multimea multiplilor lui  4 din intervalul [5, 30] : ");
    print_multime(m2);
    printf("Reuniunea celor doua multimi :");
    print_multime(reuniune);
    printf("Intersectia celor doua multimi :");
    print_multime(intersectie);
    


    return 0;
}
