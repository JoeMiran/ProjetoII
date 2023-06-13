all:	matrizes
matrizes:
	gcc -c src/matrizes.c -o build/matrizes.o
	gcc -c src/main.c -o build/main.o
	gcc build/matrizes.o build/main.o -o build/matrizes
	./build/matrizes
aplicacao:
	gcc -c src/matrizes.c -o build/matrizes.o
	gcc -c src/main.c -o build/main.o
	gcc build/matrizes.o build/main.o -o build/matrizes
	
teste:
	./build/matrizes
clean:
	rm -rf build/*.o
	rm -rf build/*matrizes
	rm -rf doc/html/*.css
	rm -rf doc/html/*.html
	rm -rf doc/html/*.png
	rm -rf doc/html/*.svg
	rm -rf doc/html/*.js
	rm -rf doc/html/*.dot
.PHONY:	doc
doc:
	doxygen doxyfile
make:
	rm -rf src/*.out
	gcc src/teste.c -lgsl -o src/a.out
	./src/a.out
	
	