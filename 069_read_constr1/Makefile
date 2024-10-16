.PHONY=clean
TARGET=tee
CXXFLAGS=-Wall -Werror -std=gnu++98

$(TARGET) : code.cpp
	g++ -o $(TARGET) $(CXXFLAGS) code.cpp

clean :
	rm $(TARGET)
