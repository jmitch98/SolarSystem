CC=g++
CFLAGS=-Wall -g
NAME=SolarSystem
LIBS=-lSDL2 -lGLEW -lGL -lassimp
IDIRS=-I"./include"

main:
	$(CC) $(CFLAGS) $(IDIRS) $(LIBS) -o $(NAME) Main.cpp	Renderer.cpp Shader.cpp Mesh.cpp Model.cpp

check:
	python2 $$CPPLINT --filter=-legal,-build --extensions=hpp,cpp,c,h,cc ./include/*.h *.cpp *.hpp

clean:
	rm -rf SolarSystem