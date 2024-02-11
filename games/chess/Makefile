CC=g++
CFLAGS=-Wall -g -ggdb
SOURCES=chessExample.cpp Chess.cpp
OBJECTS=$(SOURCES:.cpp=.o)

main: chessExample.cpp
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(CC) $(OBJECTS) $(CFLAGS) -o chess

clean:
	rm -rf $(OBJECTS) chess
