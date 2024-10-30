CXXFLAGS=-Wall -Werror -std=gnu++98 -pedantic -ggdb3
TARGET=test-bs

$(TARGET) : search.o test-bsearch.o
	g++ -o $@ $(CXXFLAGS) $^

%.o : %.cpp function.h
	g++ -o $@ $(CXXFLAGS) -c $<

.PHONY:clean

clean :
	rm -f $(TARGET) *.o

