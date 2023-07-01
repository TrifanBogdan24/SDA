# TRIFAN BOGDAN-CRISTIAN, 312 CD, SEMIGRUPA I
# TEMA 3 - S.D.A.
CC=gcc
CFLAGS=-Wall -g
CS='coding style'

build: tema3

tema3: tema3.o task1.o task2.o structuri.o
	$(CC) $(CFLAGS) -o tema3 tema3.o task1.o task2.o structuri.o

tema3.o: tema3.c task1.h task2.h structuri.h
	$(CC) $(CFLAGS) -c tema3.c

task1.o: task1.c task1.h structuri.h
	$(CC) $(CFLAGS) -c task1.c

task2.o: task2.c task2.h structuri.h
	$(CC) $(CFLAGS) -c task2.c

structuri.o: structuri.c structuri.h
	$(CC) $(CFLAGS) -c structuri.c

run_1: build
	./tema3 1

run_2: build
	./tema3 2

clean:
	rm -f *.o exec

archive:
#	In cazul in care atunci cand updatam arhiva
#	ne asteptam sa eliminam mai multe fisiere pe care nu le mai folosim,
#	stergem arhiva si o refacem de la 0.
#	intrucat nu putem verifica in Makefile daca documentele din arhivei .zip
#	mai exista in afara ei
	rm -rf tema3.zip
	zip -r tema3.zip Makefile README README.md *.c *.h

valgrind_1:
	valgrind --leak-check=yes --track-origins=yes ./tema3 1

valgrind_2:
	valgrind --leak-check=yes --track-origins=yes ./tema3 2

check:
	./run_tests.sh

coding-style:
	cd $(CS) ; ./cs.sh ../; cd ../
