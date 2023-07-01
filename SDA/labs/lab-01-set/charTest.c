#include <stdio.h>
#include <string.h>

typedef char T;
#include "OrderedSet.h"

/*
  Function that returns an ordered set with long elements between
  @start and @end that are multiples of @div
*/

OrderedSet* letters(char *word) {
  long len = strlen(word);
  long idx;

  OrderedSet* set = createOrderedSet(len);

  for (idx = 0; idx < len; idx++)
    add(set, word[idx]);

  return set;
}

// -----------------------------------------------------------------------------

/*
  Function that prints the size and the elements of an ordered set.
*/

void printOrderedCharSet(OrderedSet* set) {
  long idx;
  printf("There are %ld letters:", set->size);                 // print the size
  for(idx = 0; idx < set->size; idx++)
    printf(" %c", set->elements[idx]);                     // print each element
  printf("\n");
}

// -----------------------------------------------------------------------------


int main(int argc, char* argv[]) {
  OrderedSet *s1, *s2, *sU, *sI;
  char input1[] = "bai ce pusca mea" , input2[] = "nu vrei sa imi dai";
  s1 = letters(input1);            // the set of letters in "mississippi"
  printf("%s: " , input1);
  printOrderedCharSet(s1);

  s2 = letters(input2);                        // the set of letters in "small"
  printf("%s: " , input2);
  printOrderedCharSet(s2);

  sU = unionOrderedSets(s1, s2);                    // the union of the two sets
  printf("reunion: ");
  printOrderedCharSet(sU);

  sI = intersectOrderedSets(s1, s2);                         // the intersection
  printf("intersection: ");
  printOrderedCharSet(sI);

  return 0;
}
