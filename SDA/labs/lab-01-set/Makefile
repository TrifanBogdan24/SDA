CC=gcc -std=c9x
LT= longTest
CT = charTest

all: $(LT) $(CT)

build: $(LT) $(CT)

$(LT):
	$(CC) $(LT).c -o $(LT)

$(CT):
	$(CC) $(CT).c -o $(CT)

clean: 
	rm -f $(LT) $(CT)

archive:
	zip -r lab-01.zip *.c *.h *.txt *.pdf ./$(LT) ./$(CT)
