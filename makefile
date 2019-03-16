dictionary-main.o: dictionary-main.cpp dictionary-test.h 
	g++ -c dictionary-main.cpp -o dictionary-main.o -I -Wall

vector.o: vector.h vector.cpp
	g++ -c vector.cpp -o vector.o -I -Wall

dictionary-test.o: dictionary-test.h dictionary-test.cpp dictionary.cpp
	g++ -c dictionary-test.cpp -o dictionary-test.o -I -Wall

dictionary: dictionary-main.o vector.o dictionary-test.o
	g++ dictionary-main.o vector.o -o dictionary dictionary-test.o -I -Wall

.PHONY: clean

clean:
	rm -f *.o
