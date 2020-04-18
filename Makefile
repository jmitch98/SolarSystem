CC=g++
CFLAGS=-Wall -g
NAME=SolarSystem
LIBS=-lSDL2 -lGLEW -lGL
IDIRS=-I"./include"

main:
	$(CC) $(CFLAGS) $(IDIRS) $(LIBS) -o $(NAME) Main.cpp	Renderer.cpp Shader.cpp

check:
	python2 $$CPPLINT --filter=-legal,-build --extensions=hpp,cpp,c,h,cc *.h *.cpp *.hpp

clean:
	rm -rf SolarSystem