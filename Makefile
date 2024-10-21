# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11

# Source files
SRCS = loadbalancer.cpp request.cpp webserver.cpp main.cpp

# Output executable
TARGET = run

# Default rule: compile and link in one step
all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean rule to remove the executable
clean:
	rm -f $(TARGET)
