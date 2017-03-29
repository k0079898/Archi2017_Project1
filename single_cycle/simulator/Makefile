CC = gcc

single_cycle: simulator.o memory.o regfile.o instruction.o
	$(CC) -o $@ simulator.o memory.o regfile.o instruction.o
simulator.o: simulator.c memory.c memory.h regfile.c regfile.h instruction.c instruction.h
	$(CC) -c -g simulator.c
memory.o: memory.c memory.h regfile.c regfile.h
	$(CC) -c -g memory.c
regfile.o: regfile.c regfile.h memory.c memory.h
	$(CC) -c -g regfile.c
instrucion.o: instruction.c instruction.h regfile.c regfile.h memory.c memory.h
	$(CC) -c -g instruction.c
clean:
	rm -f simulator.o memory.o regfile.o instruction.o
