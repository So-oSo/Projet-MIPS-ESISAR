BIN = mips
OBJECTS = main.o instruction_execution.o instruction_assembly.o
CFLAGS = -Wall
CC = gcc

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN)

#mips_controller.o: mips_controller.c mips_controller.h
#	$(CC) $(CFLAGS) -c mips_controller.c

instruction_execution.o: instruction_execution.c instruction_execution.h
	$(CC) $(CFLAGS) -c instruction_execution.c

instruction_assembly.o: instruction_assembly.c instruction_assembly.h
	$(CC) $(CFLAGS) -c instruction_assembly.c


main.o:	main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm $(OBJECTS) $(BIN)
