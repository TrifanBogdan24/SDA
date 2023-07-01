#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INPUT_LEN 256


typedef int Item;
#include "Queue.h"


void printArray(int *arr, int len){
  for(int i=0; i < len; i++)  
    printf("%d ", arr[i]);
}

int arrayMaximum(const int* arr, int len){
	int max = arr[0];
	for(int i = 1; i < len; i++){
		if(arr[i] > max) 
			max = arr[i];
	}
	return max;
}

int getNumberOfDigits(int num){
	int digits = 0;
	while(num){
		num = num/10;
		digits++;
	}
	return digits;
}



void extraction(int *arr, int *index , Queue * q) {
	int i = *index;
	while (isQueueEmpty(q) == 0) {
		
		arr[i] = front(q);
		// printf("%d\n" ,arr[i]);
		dequeue(q);
		i++;
	}
	*index = i;
	return;

}
void radixSort(int *arr, int len){

	// TODO: Cerinta 4 - Implementation must use Queues
	// 1. Initialize Queues for each digit, i.e. our buckets
	Queue* zero = createQueue();
	Queue* unu = createQueue();
	Queue* doi = createQueue();
	Queue* trei = createQueue();
	Queue* patru = createQueue();
	Queue* cinci = createQueue();
	Queue* sase = createQueue();
	Queue* sapte = createQueue();
	Queue* opt = createQueue();
	Queue* noua = createQueue();

	// 2. Compute number of iterations to sort the array:
	int nr_cifre = 0;
	int max_cifre = 0;
	for (int i = 0 ; i < len ; i++) {
		int aux = arr[i];
		int nr  = 0;
		do {
			nr++;
			aux = aux/10;
		} while (aux != 0);
		
		if (nr > max_cifre) {
			max_cifre = nr;
		}
		nr_cifre += nr;
	}

	int div = 1;
	for (int i = 0 ; i < max_cifre; i++) {
		for (int j = 0 ; j < len ; j++) {
			if ( (arr[j]/div) % 10 == 0 ) enqueue(zero, arr[j]);
			else if ( (arr[j]/div) % 10 == 1 ) enqueue(unu, arr[j]);
			else if ( (arr[j]/div) % 10 == 2 ) enqueue(doi, arr[j]);
			else if ( (arr[j]/div) % 10 == 3 ) enqueue(trei, arr[j]);
			else if ( (arr[j]/div) % 10 == 4 ) enqueue(patru, arr[j]);
			else if ( (arr[j]/div) % 10 == 5 ) enqueue(cinci, arr[j]);
			else if ( (arr[j]/div) % 10 == 6 ) enqueue(sase, arr[j]);
			else if ( (arr[j]/div) % 10 == 7 ) enqueue(sapte, arr[j]);
			else if ( (arr[j]/div) % 10 == 8 ) enqueue(opt, arr[j]);
			else if ( (arr[j]/div) % 10 == 9 ) enqueue(noua, arr[j]);

		}

		int j = 0;
		extraction(arr, &j, zero);
		extraction(arr, &j, unu);
		extraction(arr, &j, doi);
		extraction(arr, &j, trei);
		extraction(arr, &j, patru);
		extraction(arr, &j, cinci);
		extraction(arr, &j, sase);
		extraction(arr, &j, sapte);
		extraction(arr, &j, opt);
		extraction(arr, &j, noua);
		div = div * 10;
		// for( int j = 0 ; j < len ;j++) {
		// 	printf("%d ", arr[j]);
		// }
		// printf("\n");
	}

	// 2a. Compute array maximum
	// 2b. Compute maximum number of digits


	// Radix sort
	// 3. Iterate over the maximum number of digits
	
	// 3a. Place the number in a bucket according to its digit 
	// 3b. Re-construct the array by using each bucket in order
	
	//4. Destroy Queues
	destroyQueue(zero);
	destroyQueue(unu);
	destroyQueue(doi);
	destroyQueue(trei);
	destroyQueue(patru);
	destroyQueue(cinci);
	destroyQueue(sase);
	destroyQueue(sapte);
	destroyQueue(opt);
	destroyQueue(noua);
}

int main(void){
	

    int len;
    char fileBuffer[MAX_INPUT_LEN];
    FILE* inputFile = fopen("input-radix-sort.csv","r");
    if(inputFile == NULL) return 1;

    int capacity = MAX_INPUT_LEN;
    int *arr = (int*) malloc(capacity*sizeof(int));

    int count = 0;
    while(fgets(fileBuffer, MAX_INPUT_LEN, inputFile) != NULL){
      fileBuffer[strcspn(fileBuffer, "\r\n")] = 0;
      len = strlen(fileBuffer);
      if(len == 0) break;

      char *token = strtok(fileBuffer,",\n");
      if(token == NULL) return 1;
      len = 0;
	  arr[len++] = atoi(token);
      while(token != NULL){
      	if(len == capacity){
      		capacity <<= 1;
      		arr = realloc(arr, capacity*sizeof(int));
      	}
    	
      	token = strtok(NULL,",\r\n");
      	if(token != NULL)
      		arr[len++] = atoi(token);     	
      }

      count++;
      printf("Input array %d:\t", count);
      printArray(arr, len);
      printf("\n");
      radixSort(arr, len);
      printf("Sorted array %d:\t", count);
      printArray(arr, len);
      printf("\n");
      printf("\n");
  	}

	free(arr);
	fclose(inputFile);
	return 0;
}
