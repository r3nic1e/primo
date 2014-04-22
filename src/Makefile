CC = g++
CPPFLAGS = -Wall -c
LDFLAGS = -lncurses
all: main
main: main.o
	$(CC) $(LDFLAGS) main.o -o main
main.o:
	$(CC) $(CPPFLAGS) main.cpp -o main.o
clean:
	rm main.o main
.PHONY: clean
