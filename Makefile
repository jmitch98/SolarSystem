CC=g++
CFLAGS=-Wall -g
NAME=SolarSystem
LIBS=-lSDL2 -lGLEW -lGL

main:
	$(CC) $(CFLAGS) $(LIBS) -o $(NAME) Main.cpp	Renderer.cpp Shader.cpp

check:
	python2 $$CPPLINT --filter=-legal,-build --extensions=hpp,cpp,c,h,cc *.h *.cpp *.hpp

clean:
	rm -rf SolarSystem