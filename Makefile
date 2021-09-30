FLAGS = -g
LIB = -I $(HEADDIR)

SRCDIR=src
HEADDIR=include
LIBDIR=lib
BINDIR=bin
OBJDIR=obj

#export to subdir
export LIBDIR HEADDIR


OS=`uname`

#detecting Operating system
ifeq ( $(OS), Darwin ) # is MacOS
	GL = -ldl -lglfw
else #is Linux
	GL = -ldl -lglfw -pthread ./$(LIBDIR)/stb_image.a ./$(LIBDIR)/FastNoise.a
endif

.PHONY: all doc lib

default: lib ./$(BINDIR)/run

all: lib ./$(BINDIR)/run doc

generate : lib ./$(BINDIR)/generate


# * * * * * * * #
# *EXECUTABLES* #
# * * * * * * * #

# debug
./$(BINDIR)/run : ./$(OBJDIR)/main.o ./$(OBJDIR)/Engine.o ./$(OBJDIR)/Camera.o ./$(OBJDIR)/World.o ./$(OBJDIR)/Window.o ./$(OBJDIR)/Worley.o ./$(OBJDIR)/Textures.o ./$(OBJDIR)/Mesh.o ./$(OBJDIR)/Shader.o ./$(LIBDIR)/glad.a
	g++ $(FLAGS) $^ -o $@ $(LIB) $(GL)

./$(BINDIR)/generate : ./$(OBJDIR)/generate.o ./$(OBJDIR)/Textures.o ./$(OBJDIR)/Worley.o ./$(LIBDIR)/glad.a 
	g++ $(FLAGS) $^ -o $@ $(LIB) $(GL)

# * * * * * * * * * #
# *FICHIERS OBJETS* #
# * * * * * * * * * #

lib/%.a: lib

# Compilation des librairies
lib:
	@make --no-print-directory -f ./$(LIBDIR)/Makefile

# Règle par défaut de compilation des sources
./$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	g++ $(FLAGS) -c -o $@ $< $(LIB)

# Règles avec dépendances spécifiques

./$(OBJDIR)/generate.o : ./$(SRCDIR)/generate.cpp ./$(SRCDIR)/Textures.h
	g++ $(FLAGS) -c -o $@ $< $(LIB)

./$(OBJDIR)/main.o : ./$(SRCDIR)/main.cpp ./$(SRCDIR)/Engine.h
	g++ $(FLAGS) -c -o $@ $< $(LIB)

./$(OBJDIR)/Engine.o : ./$(SRCDIR)/Engine.cpp ./$(SRCDIR)/Engine.h ./$(SRCDIR)/Camera.h ./$(SRCDIR)/Mesh.h ./$(SRCDIR)/Textures.h ./$(SRCDIR)/Window.h
	g++ $(FLAGS) -c -o $@ $< $(LIB)

./$(OBJDIR)/World.o : ./$(SRCDIR)/World.cpp ./$(SRCDIR)/World.h ./$(SRCDIR)/Camera.h ./$(SRCDIR)/Mesh.h ./$(SRCDIR)/Textures.h ./$(SRCDIR)/Window.h
	g++ $(FLAGS) -c -o $@ $< $(LIB)

./$(OBJDIR)/Textures.o : ./$(SRCDIR)/Textures.cpp ./$(SRCDIR)/Textures.h ./$(SRCDIR)/Worley.h#./$(SRCDIR)/stb_image.h
	g++ $(FLAGS) -c -o $@ $< $(LIB)


# documentation doxygen
doc:
	doxygen doc/Doxyfile

# clean
clean:
	@rm -f obj/* bin/*

pentaclean: clean
	@make --no-print-directory -f ./$(LIBDIR)/Makefile clean
	@rm -rf doc/html doc/latex
