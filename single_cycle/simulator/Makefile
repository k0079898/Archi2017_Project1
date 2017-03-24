CC = gcc

single_cycle: simulator.o memory.o regfile.o instruction.o
	$(CC) -o $@ simulator.o memory.o regfile.o instruction.o
simulator.o: simulator.c memory.c memory.h regfile.c regfile.h instruction.c instruction.h
	$(CC) -c simulator.c
memory.o: memory.c memory.h regfile.c regfile.h
	$(CC) -c memory.c
regfile.o: regfile.c regfile.h memory.c memory.h
	$(CC) -c regfile.c
instrucion.o: instruction.c instruction.h regfile.c regfile.h memory.c memory.h
	$(CC) -c instruction.c
clean:
	rm -f simulator.o memory.o regfile.o
