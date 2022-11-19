CC=gcc

chip7: main.o display.o cpu.o
	$(CC) -o chip7 main.o display.o cpu.o -lSDL2

display.o: display.c display.h
	$(CC) -c -o display.o display.c 

cpu.o: cpu.c cpu.h
	$(CC) -c -o cpu.o cpu.c 

clean:
	rm *.o chip7
