vector.o: vector.h vector.cpp
	g++ -c vector.cpp -o vector.o -I -Wall

dictionary-test.o: vector.h dictionary.h dictionary-test.h dictionary-test.cpp
	g++ -c dictionary-test.cpp -o dictionary-test.o -I -Wall

dictionary-main.o: vector.h dictionary.h dictionary-test.h dictionary-main.cpp
	g++ -c dictionary-main.cpp -o dictionary-main.o -I -Wall

dictionary: vector.o dictionary-test.o dictionary-main.o
	g++ vector.o dictionary-test.o dictionary-main.o -o dictionary -I -Wall

.PHONY: clean

clean:
	rm -f *.o
