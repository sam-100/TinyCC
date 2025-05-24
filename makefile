CC=gcc
BIN= bin/scanner.o bin/main.o
FLAGS= -c -I include
# Target compiler rule
tinycc: ${BIN}
	$(CC) -o $@ ${BIN}

# Object files in the bin directory
bin/main.o: src/main.c
	$(CC) -o $@ ${FLAGS} src/main.c
bin/scanner.o: src/scanner.c include/parser.h
	$(CC) -o $@ ${FLAGS} src/scanner.c
bin/parser.o: src/parser.c
	$(CC) -o $@ ${FLAGS} src/parser.c

# Scanner and parser
src/scanner.c: src/scanner.flex
	flex -o $@ src/scanner.flex
src/parser.c include/parser.h:	src/parser.bison
	bison -o src/parser.c --header=include/parser.h src/parser.bison

# Clean the project
clean:
	rm -rf bin/* include/* src/parser.c src/scanner.c tinycc
