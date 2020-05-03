CC=g++
CFLAGS=-Wall -g
NAME=SolarSystem
LIBS=-lSDL2 -lGLEW -lGL -lassimp
IDIRS=-I"./include" -I"./deps"
OBJECTS=Main.o Shader.o Model.o Mesh.o Renderer.o OrbitalBody.o SolarSystem.o
OBJDIR=obj

main: $(OBJECTS)
	$(CC) $(CFLAGS) $(IDIRS) $(OBJECTS) -o $(NAME) $(LIBS) 

.cpp.o:
	$(CC) $(CFLAGS) $(IDIRS) -c $*.cpp $(LIBS) 

check:
	python2 $$CPPLINT --filter=-legal,-build --extensions=hpp,cpp,c,h,cc ./include/*.h *.cpp *.hpp

clean:
	rm -rf $(NAME) *.o