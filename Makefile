all: galgebra
	./galgebra

galgebra: main.o
	g++ main.o -o galgebra

main.o: main.cpp galgebra.hpp core.hpp geometric_laws.hpp algebraic_laws.hpp
	g++ -I. -c main.cpp -o main.o

clean:
	rm ./galgebra ./main.o
