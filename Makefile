all:
	gcc -c matrizes.c -o matrizes.o
	gcc -c main.c -o main.o
	gcc matrizes.o main.o -o matrizes
	./matrizes
clean:
	rm -rf *.o