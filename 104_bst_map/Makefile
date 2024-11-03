CXXFLAGS=-Wall -Werror -std=gnu++98 -pedantic -ggdb3
TARGETS=test-bst test-bstmap

all : $(TARGETS)

test-bst : test-bst.cpp bst.h
	g++ -o $@ $(CXXFLAGS) $<

test-bstmap : test-bstmap.cpp bstmap.h
	g++ -o $@ $(CXXFLAGS) $<

.PHONY: clean
clean : 
	rm -f *.o $(TARGETS)
