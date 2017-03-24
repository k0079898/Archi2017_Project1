CC = gcc

single_cycle: simulator.o memory.o regfile.o
	$(CC) -o $@ simulator.o memory.o regfile.o
simulator.o: simulator.c memory.c memory.h regfile.c regfile.h
	$(CC) -c simulator.c
memory.o: memory.c memory.h regfile.c regfile.h
	$(CC) -c memory.c
regfile.o: regfile.c regfile.h memory.c memory.h
	$(CC) -c regfile.c
clean:
	rm -f simulator.o memory.o regfile.o
