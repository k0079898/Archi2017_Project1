CC = gcc

single_cycle: *.o
	$(CC) -o $@ *.o
simulator.o: simulator.c memory.c memory.h
	$(CC) -c simulator.c
memory.o: memory.c memory.h
	$(CC) -c memory.c
clean: *.o
	rm -f *.o
