# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++98 -Wall -Werror -pedantic

# Executable name
EXEC = circles

# Source files
SRCS = main.cpp point.cpp circle.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target to compile the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean target to remove object files and the executable
clean:
	rm -f $(OBJS) $(EXEC)

