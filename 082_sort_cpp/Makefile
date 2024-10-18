CXXFLAGS=-Wall -Werror -std=gnu++98 -pedantic
TARGET=sortLines
.PHONY:
	clean

$(TARGET) : sortLines.cpp
	g++ -o $(TARGET) $(CXXFLAGS) sortLines.cpp

clean:
	rm -f $(TARGET)
