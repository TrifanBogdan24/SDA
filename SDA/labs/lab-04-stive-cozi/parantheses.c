#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 256

typedef char Item;
#include "Stack.h"


int good_indentation(char c1 , char c2) {
  // functia va returna 1 daca c2 este un dintre parantezele corecte care o pot urma pe c1
  if (c1 == '(' && (c2 == ']' || c2 == '}' || c2 == '[' || c2 == '{') ) return 0;
  if (c1 == '[' && (c2 == ')' || c2 == '}'  || c2== '{') ) return 0; 
  if (c1 == '{' && (c2 == ')' || c2 == ']') ) return 0;
  return 1;
}

int isBalanced(const char *str, int length){

  /* TODO: Cerinta 3
  * Implementation must use a stack.
  * Do NOT forget to deallocate the memory you use.
  */
  Stack * stiva = createStack();    
 
  for (int i = 0 ; i < strlen(str) ; i++) {
   
  // stiva nu este vida
  // comparam ultimul element din stiva cu paranteza de la indicele curent
  
  if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
    push(stiva , str[i]);
  } else {
    if (isStackEmpty(stiva) == 1) {
      // stiva este vida, deci paranteza de la indicele i trebuie sa fie deschisa
      if (str[i] == ')' || str[i] == ']' || str[i] == '}') {
        destroyStack(stiva);
        return 0;
      }
    }
    char sc = top(stiva);
    pop(stiva);
    int ok_rotunda = (sc == '(' && (str[i] == ']' || str[i] == '}' || str[i] == '[' || str[i] == '{'));
    int ok_dreapta = (sc == '[' && (str[i] == ')' || str[i] == '}'  || str[i] == '{'));
    int ok_acolada = (sc == '{' && (str[i] == ')' || str[i] == ']') );
    int rasp = (ok_rotunda == 0 && (ok_dreapta));
    if ( good_indentation(sc, str[0]) == 0) {
      printf("%c %c\n" , sc , str[i]);
      destroyStack(stiva);
      return 0;
    } 
  }
    
  }
  destroyStack(stiva);
  return 1;
      
}

int main(){
    int len;
    char buffer[MAX_INPUT_LEN];
    FILE* inputFile = fopen("input-parantheses.txt","r");
    if(inputFile == NULL) return 1;


    while(fgets(buffer, MAX_INPUT_LEN, inputFile) != NULL){
      buffer[strcspn(buffer, "\r\n")] = 0;
      len = strlen(buffer);
      if(len == 0) break;

      if(isBalanced(buffer, len))
        printf("%s ---> is balanced.\n", buffer);
      else
        printf("%s ---> not balanced.\n", buffer);
    }

    fclose(inputFile);

    return 0;
}
