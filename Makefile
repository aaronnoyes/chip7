CC=gcc
CFLAGS=-ggdb

chip7: main.o display.o cpu.o
	$(CC) -o chip7 main.o display.o cpu.o -lSDL2 $(CFLAGS)

display.o: display.c display.h
	$(CC) -c -o display.o display.c $(CFLAGS)

cpu.o: cpu.c cpu.h
	$(CC) -c -o cpu.o cpu.c $(CFLAGS)

clean:
	rm *.o chip7
