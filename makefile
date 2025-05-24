CC=gcc


all: bin/main.o bin/scanner.o bin/parser.o
	$(CC) -o tinycc bin/main.o bin/scanner.o

bin/main.o: src/main.c
	$(CC) -c -o bin/main.o -I include src/main.c
bin/scanner.o: src/scanner.c include/parser.h
	$(CC) -c -o bin/scanner.o -I include src/scanner.c
bin/parser.o: src/parser.c
	$(CC) -c -o bin/parser.o -I include src/parser.c

src/scanner.c: src/scanner.flex
	flex src/scanner.flex
	mv lex.yy.c src/scanner.c

src/parser.c include/parser.h:	src/parser.bison
	bison src/parser.bison --header=include/parser.h -d -o src/parser.c

clean:
	rm -rf bin/* include/* src/parser.c src/scanner.c tinycc
