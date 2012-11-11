CC=/sw/bin/gcc-fsf-4.7
CC_LIBRARY_PATH=/sw/lib/gcc4.7/lib
CC_LIBRARY=stdc++
BOOST_INCLUDE_PATH=/sw/include
BOOST_LIBRARY_PATH=/sw/lib
BOOST_UNIT_TEST_FRAMEWORK=boost_unit_test_framework-mt

all:
	$(CC) -g3 -std=gnu++11 -I$(BOOST_INCLUDE_PATH) -c -o test.o test.cpp
	$(CC) -L$(CC_LIBRARY_PATH) -l$(CC_LIBRARY) -L$(BOOST_LIBRARY_PATH) -l$(BOOST_UNIT_TEST_FRAMEWORK) -o test_galgebra test.o
	(./test_galgebra --log_level=all --report_format=XML --report_level=detailed)

clean:
	rm ./test_galgebra ./test.o
