FLAGS = -g
GL = -ldl -lglfw

SRCDIR=src
HEADDIR=include
LIBDIR=build
BINDIR=bin
OBJDIR=obj

OS=`uname`

#detecting Operating system
ifeq ( $(OS), Windows_NT )     # is Windows
    #TODO Fais ton truc Mattéo
else
  ifeq ( $(OS), Darwin ) # is MacOS
    GL = -ldl -lglfw
  else #is Linux
    #TODO à compléter
  endif
endif

.PHONY: all doc

default: ./$(BINDIR)/run

all: ./$(BINDIR)/run doc




# exécutables

# debug
./$(BINDIR)/run : ./$(OBJDIR)/main.o ./$(OBJDIR)/Engine.o ./$(OBJDIR)/Camera.o ./$(OBJDIR)/World.o ./$(OBJDIR)/Window.o ./$(OBJDIR)/stb_image.o ./$(OBJDIR)/Textures.o ./$(OBJDIR)/Mesh.o ./$(OBJDIR)/Shader.o ./$(OBJDIR)/glad.o 
	g++ $(FLAGS) $^ -o $@ $(GL)

#compilable

# partie jeu
./$(OBJDIR)/main.o : ./$(SRCDIR)/main.cpp ./$(SRCDIR)/Engine.h ./$(SRCDIR)/glad.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

./$(OBJDIR)/Window.o : ./$(SRCDIR)/Window.cpp ./$(SRCDIR)/Window.h ./$(SRCDIR)/glad.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

./$(OBJDIR)/Shader.o : ./$(SRCDIR)/Shader.cpp ./$(SRCDIR)/Shader.h ./$(SRCDIR)/glad.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

./$(OBJDIR)/Mesh.o : ./$(SRCDIR)/Mesh.cpp ./$(SRCDIR)/Mesh.h ./$(SRCDIR)/glad.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

./$(OBJDIR)/Camera.o : ./$(SRCDIR)/Camera.cpp ./$(SRCDIR)/Camera.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

./$(OBJDIR)/Engine.o : ./$(SRCDIR)/Engine.cpp ./$(SRCDIR)/Engine.h ./$(SRCDIR)/Camera.h ./$(SRCDIR)/Mesh.h ./$(SRCDIR)/Textures.h ./$(SRCDIR)/Window.h ./$(SRCDIR)/glad.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

./$(OBJDIR)/World.o : ./$(SRCDIR)/World.cpp ./$(SRCDIR)/World.h ./$(SRCDIR)/Camera.h ./$(SRCDIR)/Mesh.h ./$(SRCDIR)/Textures.h ./$(SRCDIR)/Window.h ./$(SRCDIR)/glad.h
	g++ $(FLAGS) -c -o $@ $< $(GL)
	
./$(OBJDIR)/Textures.o : ./$(SRCDIR)/Textures.cpp ./$(SRCDIR)/Textures.h ./$(SRCDIR)/stb_image.h ./$(SRCDIR)/glad.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

./$(OBJDIR)/glad.o : ./$(SRCDIR)/glad.c ./$(SRCDIR)/glad.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

./$(OBJDIR)/stb_image.o : ./$(SRCDIR)/stb_image.cpp ./$(SRCDIR)/stb_image.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

# documentation doxygen
doc:
	doxygen doc/Doxyfile

# clean
clean:
	@rm obj/* bin/*

pentaclean: clean
	@rm -rf doc/html doc/latex