CC=g++
CXXFLAGS=-std=c++11 -Wall
LDFLAGS=
SOURCES=$(wildcard *.cpp */*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=war_game

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
