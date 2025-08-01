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
	bin/tac_print.o \
	bin/code_gen.o \
	bin/return_check.o \
	bin/integer_to_string.o \
	bin/string_to_integer.o \
	bin/read_int.o \
	bin/print_int.o \
	bin/print_char.o \
	bin/read_char.o \

CFLAGS= -I include -Werror

# Link all object files to produce the final executible
tinycc: ${BIN}
	$(CC) -o $@ ${BIN}

gdb: CFLAGS += -g
gdb: tinycc

# Compiling src files
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

# Compiling src/ast module
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

# Compiling src/phases/frontend module
bin/construct_symtab.o: src/phases/frontend/construct_symtab.c include/phases/frontend/construct_symtab.h
	$(CC) -c -o $@ ${CFLAGS} src/phases/frontend/construct_symtab.c
bin/resolve_name.o: src/phases/frontend/resolve_name.c include/phases/frontend/resolve_name.h
	$(CC) -c -o $@ ${CFLAGS} src/phases/frontend/resolve_name.c
bin/typecheck.o: src/phases/frontend/typecheck.c include/phases/frontend/typecheck.h
	$(CC) -c -o $@ ${CFLAGS} src/phases/frontend/typecheck.c

# Compiling src/phases/middleend module
bin/generate_tac.o: src/phases/middleend/generate_tac.c include/phases/middleend/generate_tac.h
	$(CC) -c -o $@ ${CFLAGS} src/phases/middleend/generate_tac.c
bin/memory_layout.o: src/phases/middleend/memory_layout.c include/phases/middleend/memory_layout.h
	$(CC) -c -o $@ ${CFLAGS} src/phases/middleend/memory_layout.c
bin/return_check.o: src/phases/middleend/return_check.c include/phases/middleend/return_check.h
	$(CC) -c -o $@ ${CFLAGS} src/phases/middleend/return_check.c

# Compiling src/phases/backend module
bin/code_gen.o: src/phases/backend/code_gen.c include/phases/backend/code_gen.h
	$(CC) -c -o $@ ${CFLAGS} src/phases/backend/code_gen.c

# Compiling src/symbol_table module
bin/symbol.o: src/symbol_table/symbol.c include/symbol_table/symbol.h
	$(CC) -c -o $@ ${CFLAGS} src/symbol_table/symbol.c
bin/symtab.o: src/symbol_table/symtab.c include/symbol_table/symtab.h
	$(CC) -c -o $@ ${CFLAGS} src/symbol_table/symtab.c
bin/symtab_stack.o: src/symbol_table/symtab_stack.c include/symbol_table/symtab_stack.h
	$(CC) -c -o $@ ${CFLAGS} src/symbol_table/symtab_stack.c
bin/symtab_print.o: src/symbol_table/print.c include/symbol_table/print.h
	$(CC) -c -o $@ ${CFLAGS} src/symbol_table/print.c


# Compiling src/tac module
bin/tac_operand.o: src/tac/tac_operand.c include/tac/tac_operand.h
	$(CC) -c -o $@ ${CFLAGS} src/tac/tac_operand.c
bin/tac_stmt.o: src/tac/tac_stmt.c include/tac/tac_stmt.h
	$(CC) -c -o $@ ${CFLAGS} src/tac/tac_stmt.c
bin/tac_print.o: src/tac/print.c include/tac/print.h
	$(CC) -c -o $@ ${CFLAGS} src/tac/print.c

# Compiling src/runtime-support module
bin/string_to_integer.o: src/runtime-support/string_to_integer.c
	$(CC) -c -o $@ ${CFLAGS} src/runtime-support/string_to_integer.c
bin/integer_to_string.o: src/runtime-support/integer_to_string.c
	$(CC) -c -o $@ ${CFLAGS} src/runtime-support/integer_to_string.c
bin/read_int.o: src/runtime-support/read_int.asm
	nasm -f elf64 -Iinclude/runtime-support/ -o $@ src/runtime-support/read_int.asm
bin/print_int.o: src/runtime-support/print_int.asm
	nasm -f elf64 -Iinclude/runtime-support/ -o $@ src/runtime-support/print_int.asm
bin/read_char.o: src/runtime-support/read_char.asm
	nasm -f elf64 -o $@ src/runtime-support/read_char.asm
bin/print_char.o: src/runtime-support/print_char.asm
	nasm -f elf64 -o $@ src/runtime-support/print_char.asm


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

# Run the compiler on a sample input with all options enabled
run: tinycc
	./tinycc input/main.b --show-tokens --show-ast --show-symtab --show-tac
