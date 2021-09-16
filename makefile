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

all: ./$(BINDIR)/run doc clean


# exécutables

# debug
./$(BINDIR)/run : ./$(OBJDIR)/main.o ./$(OBJDIR)/engine.o ./$(OBJDIR)/camera.o ./$(OBJDIR)/world.o ./$(OBJDIR)/window.o ./$(OBJDIR)/stb_image.o ./$(OBJDIR)/textures.o ./$(OBJDIR)/mesh.o ./$(OBJDIR)/shader.o ./$(OBJDIR)/glad.o 
	g++ $(FLAGS) $^ -o $@ $(CURSES) $(GL)

#compilable

# partie jeu
./$(OBJDIR)/main.o : ./$(SRCDIR)/main.cpp ./$(SRCDIR)/engine.h ./$(SRCDIR)/glad.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

./$(OBJDIR)/window.o : ./$(SRCDIR)/window.cpp ./$(SRCDIR)/window.h ./$(SRCDIR)/glad.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

./$(OBJDIR)/shader.o : ./$(SRCDIR)/shader.cpp ./$(SRCDIR)/shader.h ./$(SRCDIR)/glad.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

./$(OBJDIR)/mesh.o : ./$(SRCDIR)/mesh.cpp ./$(SRCDIR)/mesh.h ./$(SRCDIR)/glad.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

./$(OBJDIR)/camera.o : ./$(SRCDIR)/camera.cpp ./$(SRCDIR)/camera.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

./$(OBJDIR)/engine.o : ./$(SRCDIR)/engine.cpp ./$(SRCDIR)/engine.h ./$(SRCDIR)/camera.h ./$(SRCDIR)/mesh.h ./$(SRCDIR)/textures.h ./$(SRCDIR)/window.h ./$(SRCDIR)/glad.h
	g++ $(FLAGS) -c -o $@ $< $(GL)

./$(OBJDIR)/world.o : ./$(SRCDIR)/world.cpp ./$(SRCDIR)/world.h ./$(SRCDIR)/camera.h ./$(SRCDIR)/mesh.h ./$(SRCDIR)/textures.h ./$(SRCDIR)/window.h ./$(SRCDIR)/glad.h
	g++ $(FLAGS) -c -o $@ $< $(GL)
	
./$(OBJDIR)/textures.o : ./$(SRCDIR)/textures.cpp ./$(SRCDIR)/textures.h ./$(SRCDIR)/stb_image.h ./$(SRCDIR)/glad.h
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
