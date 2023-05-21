all:
	gcc -c src/matrizes.c -o build/matrizes.o
	gcc -c src/main.c -o build/main.o
	gcc build/matrizes.o build/main.o -o build/matrizes
	./build/matrizes
clean:
	rm -rf build/*.o
	rm -rf build/*matrizes
	rm -rf build/*.css
	rm -rf build/*.html
	rm -rf build/*.png
	