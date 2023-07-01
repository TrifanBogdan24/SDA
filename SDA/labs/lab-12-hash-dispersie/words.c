#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Key;
typedef int Value;
typedef long(*HashFunction)(Key, long);

typedef struct Element {
  Key key;
  Value value;
  struct Element *next;
} Element;

typedef struct HashTable {
  Element** elements;
  long size;
  HashFunction hashFunction;
} HashTable;

void initHashTable(HashTable **h, long size, HashFunction f) {
  // Cerinta 1
  return ;
  (*h)->hashFunction = f;
  (*h)->size = size;
  (*h)->elements = malloc(size * sizeof(Element));
  for (int i = 0; i < size; i++) {
    (*h)->elements[i] = malloc(sizeof(struct Element));
    (*h)->elements[i] = NULL;
  }
}

int exists(HashTable *hashTable, Key key) {
  // Cerinta 1
  for (long i = 0; i < hashTable->size; i++) {
    Element *elem = hashTable->elements[i];
    while (elem) {
      if (elem->key == key)
        return 1;
      elem = elem->next;
    }
    
  }
  return 0;
}

Value get(HashTable *hashTable, Key key) {
  // Cerinta 1
  if (!exists(hashTable, key))
    return -1;  // cheia nu se afla in dictionar
  
  for (long i = 0; i < hashTable->size; i++) {
    Element *elem = hashTable->elements[i];
    while (elem) {
      if (elem->key == key)
        return elem->value;
      elem = elem->next;
    }
    
  }
  return -1; // cheia nu se afla in dictionar
}

void put(HashTable *hashTable, Key key, Value value) {
  // Cerinta 1
  if (hashTable->size == 0) {

    hashTable->elements[0]->key = key;
    hashTable->elements[0]->value = value;
    return ;
  }

  for (long i = 0; i < hashTable->size; i++) {
    if (hashTable->elements[i]->key == key) {
      // cheia sa afla in dictionar
      // adaugam la finalul listei
      Element *iterator = hashTable->elements[i];
      while (iterator && !iterator->next)
        iterator = iterator->next;

      Element *new_elem = (Element *) malloc(sizeof(Element));
      new_elem->key = key;
      new_elem->value = value;
      new_elem->next = NULL;

      iterator->next = new_elem;
      return ;
    }
  }

  // trebuie sa adaugam o  cheie noua
  hashTable->elements[hashTable->size] = (Element *) malloc(sizeof(Element));
  hashTable->elements[hashTable->size]->key = key;
  hashTable->elements[hashTable->size]->value = value;
  hashTable->elements[hashTable->size]->next = NULL;
  hashTable->size++;
}

void deleteKey(HashTable *hashTable, Key key) {
  // Cerinta 1

  // mutam cheia ca fiind ultimul element, pe care il eliminam
}

void print(HashTable *hashTable) {
  // Cerinta 1
  printf("Dimensiunea : %ld\n", hashTable->size);
  for (long i = 0 ; i < hashTable->size; i++) {
    printf("%s : (", hashTable->elements[i]->key);
    Element *iterator = hashTable->elements[i];
    while (iterator) {
      printf("%d ", iterator->value);
      iterator = iterator->next;
    }
    printf(")\n");
  }

}

void freeHashTable(HashTable *hashTable) {
  // Cerinta 1
  for (long i = hashTable->size - 1; i >= 0; i--) {
    Element *iterator = hashTable->elements[i];
    while (iterator) {
      Element *aux = iterator;
      iterator = iterator->next;
      free(iterator);
    }
  }
  free(hashTable->elements);
  free(hashTable);
}


long hash1(Key word, long size) {
  // Cerinta 2
  long h = 0;
  for (long i = 0; i < size; i++)
    h = h * 17 + word[i];
  
  return (h % size);
}



int main(int argc, char* argv[]) {
  HashTable *hashTable;
  FILE *f1, *f2;
  char word[256];
  long hashSize, common;
  char cuvant[256][256];
  int nr_aparitii[256];
  int nr_cuvinte = 0;
  hashSize = atoi(argv[1]);
  f1 = fopen(argv[2], "r");
  f2 = fopen(argv[3], "r");

 // initHashTable(&hashTable, hashSize, &hash1);

  // Cerinta 3

  // ...


  // Cerinta 4

  // ...
  printf("Asta trebuie sa contina corect tabel corect de hashing :\n");
  initHashTable(&hashTable, hashSize, hash1);
  printf("%ld\n", hashTable->size);
  while (fscanf(f1, "%s", word) == 1) {
    // nu este hash-table :
    strcpy(cuvant[nr_cuvinte], word);
    nr_aparitii[nr_cuvinte] = 0;
    nr_cuvinte++;
    for (int i = 0; i < nr_cuvinte; i++)
      if (strcmp(cuvant[i], cuvant[nr_cuvinte - 1]) == 0)
        nr_aparitii[nr_cuvinte - 1]++;

    // este hash-table :
    
    // Value get_val = get(hashTable, word);
    //int exista = exists(hashTable, word);
    // if (exists(hashTable, word) == 1)
    //   put(hashTable, word, get_val + 1);
    // else
    //  put(hashTable, word, get_val);
  }
  for (int i = 0; i < nr_cuvinte; i++) {
    printf("%d : `%s` apare de %d ori \n", i, cuvant[i], nr_aparitii[i]);
  }

  Key cheie = (char *)malloc(100 * sizeof(char));
  strcpy(cheie, "hello, world!");
  printf("Hashul lui '%s' = %ld\n", cheie, hash1(cheie, (long)strlen(cheie)));
  
  strcpy(cheie, "24 BGD");
  printf("Hashul lui '%s' = %ld\n", cheie, hash1(cheie, (long)strlen(cheie)));
  
  strcpy(cheie, "boss");
  printf("Hashul lui '%s' = %ld\n", cheie, hash1(cheie, (long)strlen(cheie)));
  
  strcpy(cheie, "sultan");
  printf("Hashul lui '%s' = %ld\n", cheie, hash1(cheie, (long)strlen(cheie)));
  
  printf("Aici este structura implementata de mine de hash-table :\n");


  printf("Common words: %ld\n", common);

  fclose(f1);
  fclose(f2);
  return 0;
}
