CC=gcc
BIN= bin/scanner.o bin/main.o bin/parser.o bin/arguments.o bin/utils.o bin/exprn.o bin/stmt.o bin/decl.o bin/func.o bin/program.o bin/symbol.o bin/symtab.o bin/symtab_stack.o
CFLAGS= -I include -Werror

# Target compiler rules
tinycc: ${BIN}
	$(CC) -o $@ ${BIN}

gdb: CFLAGS += -g
gdb: tinycc

# Compiling src/
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

# Compiling src/ast/
bin/exprn.o: src/ast/exprn.c include/ast/exprn.h
	$(CC) -c -o $@ ${CFLAGS} src/ast/exprn.c
bin/stmt.o: src/ast/stmt.c include/ast/stmt.h
	$(CC) -c -o $@ ${CFLAGS} src/ast/stmt.c
bin/decl.o: src/ast/decl.c include/ast/decl.h
	$(CC) -c -o $@ ${CFLAGS} src/ast/decl.c
bin/program.o: src/ast/program.c include/ast/program.h
	$(CC) -c -o $@ ${CFLAGS} src/ast/program.c
bin/func.o: src/ast/func.c include/ast/func.h
	$(CC) -c -o $@ ${CFLAGS} src/ast/func.c

# Compiling src/symbol_table/
bin/symbol.o: src/symbol_table/symbol.c include/symbol_table/symbol.h
	$(CC) -c -o $@ ${CFLAGS} src/symbol_table/symbol.c
bin/symtab.o: src/symbol_table/symtab.c include/symbol_table/symtab.h
	$(CC) -c -o $@ ${CFLAGS} src/symbol_table/symtab.c
bin/symtab_stack.o: src/symbol_table/symtab_stack.c include/symbol_table/symtab_stack.h
	$(CC) -c -o $@ ${CFLAGS} src/symbol_table/symtab_stack.c

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

