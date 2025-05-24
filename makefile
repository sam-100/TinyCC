CC=gcc
BIN= bin/scanner.o bin/main.o bin/parser.o
CFLAGS= -I include
# Target compiler rule
tinycc: ${BIN}
	$(CC) -o $@ ${BIN}

# Object files in the bin directory
bin/main.o: src/main.c
	$(CC) -c -o $@ ${CFLAGS} src/main.c
bin/scanner.o: src/scanner.c include/parser.h
	$(CC) -c -o $@ ${CFLAGS} src/scanner.c
bin/parser.o: src/parser.c
	$(CC) -c -o $@ ${CFLAGS} src/parser.c
	
# Scanner and parser
src/scanner.c: src/scanner.flex
	flex -o $@ src/scanner.flex
src/parser.c include/parser.h:	src/parser.bison
	bison -o src/parser.c --header=include/parser.h src/parser.bison

# Clean the project
clean:
	@rm -rf bin/* include/* src/parser.c src/scanner.c tinycc
