############################# Makefile ##########################
CC = g++
CFLAGS = -W -Wall -ansi
SRC= $(wildcard *.cpp)
EXEC = main
OBJ = $(SRC:.cpp = .o)

all: $(EXEC)

main: main.o
	$(CC) -std=c++0x -o main.cpp main $(CFLAGS)
clean:
	rm -rf *.o
mrproper: clean
	rm -rf $(EXEC)