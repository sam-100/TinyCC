CC=gcc
BIN= bin/scanner.o bin/main.o bin/parser.o bin/arguments.o bin/utils.o bin/ast.o bin/print-ast.o
CFLAGS= -I include

# Target compiler rule
tinycc: ${BIN}
	$(CC) -o $@ ${BIN}

# Object files in the bin directory
bin/main.o: src/main.c include/arguments.h
	$(CC) -c -o $@ ${CFLAGS} src/main.c
bin/scanner.o: src/scanner.c include/parser.h
	$(CC) -c -o $@ ${CFLAGS} src/scanner.c
bin/parser.o: src/parser.c
	$(CC) -c -o $@ ${CFLAGS} src/parser.c
bin/arguments.o: src/arguments.c include/arguments.h
	$(CC) -c -o $@ ${CFLAGS} src/arguments.c
bin/utils.o: src/utils.c include/utils.h
	$(CC) -c -o $@ ${CFLAGS} src/utils.c
bin/ast.o: src/ast.c include/ast.h
	$(CC) -c -o  $@ ${CFLAGS} src/ast.c
bin/print-ast.o: src/print-ast.c include/print-ast.h
	$(CC) -c -o $@ ${CFLAGS} src/print-ast.c

# Scanner and parser
src/scanner.c: src/scanner.flex
	flex -o $@ src/scanner.flex
src/parser.c include/parser.h:	src/parser.bison
	bison -o src/parser.c --header=include/parser.h src/parser.bison

# Clean the project
clean:
	@rm -rf bin/* \
		include/parser.h \
		src/parser.c src/scanner.c \
		tinycc
