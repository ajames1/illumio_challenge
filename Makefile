CC=g++ --std=c++11

challenge: challenge.cpp NATTable.cpp NATTable.h
	$(CC) -o challenge challenge.cpp NATTable.cpp

tests: tests.cpp NATTable.cpp NATTable.h
	$(CC) -o tests tests.cpp NATTable.cpp

clean: 
	rm -f challenge tests OUTPUT
