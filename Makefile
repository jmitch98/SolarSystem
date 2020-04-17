CC=g++
CFLAGS=-Wall -g
NAME=SolarSystem
LIBS=-lSDL2 -lGL

main:
	$(CC) $(CFLAGS) $(LIBS) -o $(NAME) Main.cpp	