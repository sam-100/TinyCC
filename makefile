CC=gcc
BIN= bin/scanner.o bin/main.o bin/parser.o bin/arguments.o bin/utils.o bin/exprn.o bin/stmt.o bin/decl.o bin/func.o bin/program.o bin/symbol.o bin/symtab.o bin/symtab_stack.o
CFLAGS= -I include

# Target compiler rules
tinycc: ${BIN}
	$(CC) -o $@ ${BIN}

gdb: CFLAGS += -g
gdb: tinycc

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
bin/exprn.o: src/exprn.c include/exprn.h
	$(CC) -c -o $@ ${CFLAGS} src/exprn.c
bin/stmt.o: src/stmt.c include/stmt.h
	$(CC) -c -o $@ ${CFLAGS} src/stmt.c
bin/decl.o: src/decl.c include/decl.h
	$(CC) -c -o $@ ${CFLAGS} src/decl.c
bin/program.o: src/program.c include/program.h
	$(CC) -c -o $@ ${CFLAGS} src/program.c
bin/func.o: src/func.c include/func.h
	$(CC) -c -o $@ ${CFLAGS} src/func.c
bin/symbol.o: src/symbol.c include/symbol.h
	$(CC) -c -o $@ ${CFLAGS} src/symbol.c
bin/symtab.o: src/symtab.c include/symtab.h
	$(CC) -c -o $@ ${CFLAGS} src/symtab.c
bin/symtab_stack.o: src/symtab_stack.c include/symtab_stack.h
	$(CC) -c -o $@ ${CFLAGS} src/symtab_stack.c

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
		output/* \
		tinycc

