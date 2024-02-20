CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -pedantic -I.


all: josephus


main: josephus.cc josephus.h 
	g++ $(CXXFLAGS) -o josephus josephus.cc 

clean:
	rm -f josephus

.PHONY: all clean
