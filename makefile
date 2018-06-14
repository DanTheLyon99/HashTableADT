test:
	gcc -Wall -g -std=c99 src/*.c -Iinclude -o bin/test

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*
