CC = gcc # GCC Compiler
CFLAGS = -ansi -Wall -pedantic # Flags
GLOBALS_FILES = globals.h 
ALL_OBJ =  utils.o table.o preassembler.o

assembler: $(EXE_DEPS) $(GLOBALS_FILES)
	$(CC) -g $(EXE_DEPS) $(CFLAGS) -o $@
	
assembler.o:  assembler.c $(GLOBALS_FILES)
	$(CC) -c assembler.c $(CFLAGS) -o $@

preassembler: preassembler.c preassembler.h $(ALL_OBJ) 
	$(CC) -g preassembler.c $(CFLAGS) $(ALL_OBJ) -o $@


table.o: table.c table.h $(GLOBALS_FILES)
	$(CC) -c table.c $(CFLAGS) -o $@

utils.o: utils.c utils.h $(GLOBALS_FILES)
	$(CC) -c utils.c $(CFLAGS) -o $@

