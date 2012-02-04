PLATFORM := $(shell uname)

ifeq ($(PLATFORM),Darwin)
BOOST_INCLUDE_DIRECTORY=/sw/include/boost-1_41
endif

ifeq ($(PLATFORM),Linux)
BOOST_INCLUDE_DIRECTORY=/usr/include
endif

all: galgebra
	./galgebra

galgebra: main.o
	g++ main.o -o galgebra

main.o: main.cpp galgebra.hpp core.hpp geometric_laws.hpp algebraic_laws.hpp
	g++ -I$(BOOST_INCLUDE_DIRECTORY) -I. -c main.cpp -o main.o

clean:
	rm ./galgebra ./main.o
