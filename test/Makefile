SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
CC = g++
CPPFLAGS = -c -Iigloo/
LDFLAGS =
all: $(SOURCES) test
test: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o test
	./test
.cpp.o:
	$(CC) $(CPPFLAGS) $< -o $@
clean:
	rm *.o test
.PHONY: clean test
