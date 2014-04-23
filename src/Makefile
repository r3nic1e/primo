CC = g++
CPPFLAGS = -Wall -c -I../include
LDFLAGS = -lncurses
SOURCES = main.cpp editor.cpp
OBJECTS = $(SOURCES:.cpp=.o)
all: $(SOURCES) primo
primo: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o primo
.cpp.o:
	$(CC) $(CPPFLAGS) $< -o $@
clean:
	rm *.o primo
.PHONY: clean
