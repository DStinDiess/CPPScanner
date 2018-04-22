CC_FLAGS = --std=c++11 -Wall -Werror
CC = g++
EXEC = cppscanner
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

clean:
	rm -rf $(EXEC) $(OBJECTS)
