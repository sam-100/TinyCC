CC=gcc
BIN= bin/scanner.o \
	bin/main.o \
	bin/parser.o \
	bin/arguments.o \
	bin/utils.o \
	bin/exprn.o \
	bin/stmt.o \
	bin/decl.o \
	bin/func.o \
	bin/program.o \
	bin/symbol.o \
	bin/symtab.o \
	bin/symtab_stack.o \
	bin/tac_stmt.o \
	bin/tac_operand.o \
	bin/ast_print.o \
	bin/symtab_print.o \
	bin/construct_symtab.o \
	bin/resolve_name.o \
	bin/typecheck.o \
	bin/generate_tac.o \
	bin/memory_layout.o \
	bin/tac_print.o

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
bin/ast_print.o: src/ast/print.c include/ast/print.h
	$(CC) -c -o $@ ${CFLAGS} src/ast/print.c

# Compiling src/phases/frontend
bin/construct_symtab.o: src/phases/frontend/construct_symtab.c include/phases/frontend/construct_symtab.h
	$(CC) -c -o $@ ${CFLAGS} src/phases/frontend/construct_symtab.c
bin/resolve_name.o: src/phases/frontend/resolve_name.c include/phases/frontend/resolve_name.h
	$(CC) -c -o $@ ${CFLAGS} src/phases/frontend/resolve_name.c
bin/typecheck.o: src/phases/frontend/typecheck.c include/phases/frontend/typecheck.h
	$(CC) -c -o $@ ${CFLAGS} src/phases/frontend/typecheck.c

# Compiling src/phases/middleend
bin/generate_tac.o: src/phases/middleend/generate_tac.c include/phases/middleend/generate_tac.h
	$(CC) -c -o $@ ${CFLAGS} src/phases/middleend/generate_tac.c
bin/memory_layout.o: src/phases/middleend/memory_layout.c include/phases/middleend/memory_layout.h
	$(CC) -c -o $@ ${CFLAGS} src/phases/middleend/memory_layout.c



# Compiling src/symbol_table/
bin/symbol.o: src/symbol_table/symbol.c include/symbol_table/symbol.h
	$(CC) -c -o $@ ${CFLAGS} src/symbol_table/symbol.c
bin/symtab.o: src/symbol_table/symtab.c include/symbol_table/symtab.h
	$(CC) -c -o $@ ${CFLAGS} src/symbol_table/symtab.c
bin/symtab_stack.o: src/symbol_table/symtab_stack.c include/symbol_table/symtab_stack.h
	$(CC) -c -o $@ ${CFLAGS} src/symbol_table/symtab_stack.c
bin/symtab_print.o: src/symbol_table/print.c include/symbol_table/print.h
	$(CC) -c -o $@ ${CFLAGS} src/symbol_table/print.c


# Compiling src/tac/
bin/tac_operand.o: src/tac/tac_operand.c include/tac/tac_operand.h
	$(CC) -c -o $@ ${CFLAGS} src/tac/tac_operand.c
bin/tac_stmt.o: src/tac/tac_stmt.c include/tac/tac_stmt.h
	$(CC) -c -o $@ ${CFLAGS} src/tac/tac_stmt.c
bin/tac_print.o: src/tac/print.c include/tac/print.h
	$(CC) -c -o $@ ${CFLAGS} src/tac/print.c


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



run: tinycc
	./tinycc input/main.b --show-tokens --show-ast --show-symtab --show-tac
