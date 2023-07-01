// TRIFAN BOGDAN-CRISTIAN, 312 CD, SEMIGRUPA I
// TEMA 3 - S.D.A.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structuri.h"
#include "task1.h"
#include "task2.h"

int main(int argc, char const *argv[])
{
    if (argc < DOI) {
        printf("Numar insuficient de argumente in linia de comanda.\n");
        return UNU;
    }

    if (argc > DOI) {
        printf("Prea multe argumente primite in linia de comanda.\n");
        return UNU;
    }

    // argc = 2
    if (strcmp(argv[UNU], ONE_STRING) * strcmp(argv[UNU], TWO_STRING)
        != ZERO) {
        printf("Argument invalid. Exista doar doua cerinte.\n");
        printf("Pentru rezolvarea primului task, ");
        printf("scrieti in linia de comanda : ./tema3 1\n");
        printf("Pentru rezolvarea celui de al doilea task, ");
        printf("scrieti in linia de comanda : ./tema3 2\n");
        return UNU;
    }

    FILE * fin = fopen("tema3.in", "rt");
    FILE * fout = fopen("tema3.out", "wt");
    if (!fin || !fout) {
        printf("Problema la deschiderea fisierelor.");
        return UNU;
    }

    if (strcmp(argv[UNU], ONE_STRING) == ZERO)
        solve_task_one(fin, fout);

    if (strcmp(argv[UNU], TWO_STRING) == ZERO)
        solve_task_two(fin, fout);

    fclose(fin);
    fclose(fout);
    return ZERO;
}
