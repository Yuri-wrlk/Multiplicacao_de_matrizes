############################# Makefile ##########################
CC = g++
CFLAGS = -W -std=c+11 -lpthread
SRC= $(wildcard *.cpp)
EXEC = main
OBJ = $(SRC:.cpp = .o)

all: $(EXEC)

main: main.o
	$(CC) -o main.cpp main $(CFLAGS)
clean:
	rm -rf *.o
mrproper: clean
	rm -rf $(EXEC)
