CC=g++
CFLAGS=-Wall -g
NAME=SolarSystem
LIBS=-lSDL2 -lGLEW -lGL

main:
	$(CC) $(CFLAGS) $(LIBS) -o $(NAME) Main.cpp	Renderer.cpp Shader.cpp

clean:
	rm -rf SolarSystem