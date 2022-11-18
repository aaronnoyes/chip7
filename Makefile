CC=gcc

chip7: main.o display.o
	$(CC) -o chip7 main.o display.o -lSDL2

display.o: display.c display.h
	$(CC) -c -o display.o display.c 

clean:
	rm *.o chip7
