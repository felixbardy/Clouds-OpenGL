FLAGS = -g
GL = -ldl -lglfw -I $(HEADDIR)
LIB = $(LIBDIR)/glad.a ./$(LIBDIR)/stb_image.a

SRCDIR=src
HEADDIR=include
LIBDIR=lib
BINDIR=bin
OBJDIR=obj

#export to subdir
export LIBDIR HEADDIR


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

.PHONY: all doc lib

default: lib ./$(BINDIR)/run

all: lib ./$(BINDIR)/run doc


# exécutables

# debug
./$(BINDIR)/run : ./$(OBJDIR)/main.o ./$(OBJDIR)/Engine.o ./$(OBJDIR)/Camera.o ./$(OBJDIR)/World.o ./$(OBJDIR)/Window.o ./$(OBJDIR)/Textures.o ./$(OBJDIR)/Mesh.o ./$(OBJDIR)/Shader.o
	g++ $(FLAGS) $^ -o $@ $(LIB) $(GL)

#compilable
lib:
	@make --no-print-directory -f ./$(LIBDIR)/Makefile

# partie jeu
./$(OBJDIR)/main.o : ./$(SRCDIR)/main.cpp ./$(SRCDIR)/Engine.h
	g++ $(FLAGS) -c -o $@ $<

./$(OBJDIR)/Window.o : ./$(SRCDIR)/Window.cpp ./$(SRCDIR)/Window.h
	g++ $(FLAGS) -c -o $@ $<

./$(OBJDIR)/Shader.o : ./$(SRCDIR)/Shader.cpp ./$(SRCDIR)/Shader.h
	g++ $(FLAGS) -c -o $@ $<

./$(OBJDIR)/Mesh.o : ./$(SRCDIR)/Mesh.cpp ./$(SRCDIR)/Mesh.h
	g++ $(FLAGS) -c -o $@ $<

./$(OBJDIR)/Camera.o : ./$(SRCDIR)/Camera.cpp ./$(SRCDIR)/Camera.h
	g++ $(FLAGS) -c -o $@ $<

./$(OBJDIR)/Engine.o : ./$(SRCDIR)/Engine.cpp ./$(SRCDIR)/Engine.h ./$(SRCDIR)/Camera.h ./$(SRCDIR)/Mesh.h ./$(SRCDIR)/Textures.h ./$(SRCDIR)/Window.h
	g++ $(FLAGS) -c -o $@ $<

./$(OBJDIR)/World.o : ./$(SRCDIR)/World.cpp ./$(SRCDIR)/World.h ./$(SRCDIR)/Camera.h ./$(SRCDIR)/Mesh.h ./$(SRCDIR)/Textures.h ./$(SRCDIR)/Window.h
	g++ $(FLAGS) -c -o $@ $<

./$(OBJDIR)/Textures.o : ./$(SRCDIR)/Textures.cpp ./$(SRCDIR)/Textures.h #./$(SRCDIR)/stb_image.h
	g++ $(FLAGS) -c -o $@ $<


# documentation doxygen
doc:
	doxygen doc/Doxyfile

# clean
clean:
	@rm obj/* bin/*

pentaclean: clean
	@make --no-print-directory -f ./$(LIBDIR)/Makefile clean
	@rm -rf doc/html doc/latex
