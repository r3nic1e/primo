SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
CC = g++
CPPFLAGS = -c -Iigloo -I../include
LDFLAGS =
all: $(SOURCES) build-test test
test:
	./test
build-test: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o test
.cpp.o:
	$(CC) $(CPPFLAGS) $< -o $@
clean:
	rm *.o test
.PHONY: clean test
