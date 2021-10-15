LIBDIR := ./$(LIBDIR)
HEADDIR := ./$(HEADDIR)

all: $(LIBDIR)/glad.a ./$(LIBDIR)/stb_image.a ./$(LIBDIR)/FastNoise.a ./$(LIBDIR)/lodepng.a
	@: #this is for silencing make

./$(LIBDIR)/glad.a: ./$(LIBDIR)/glad.c
	g++ -c -o $@ $< -I $(HEADDIR)

./$(LIBDIR)/stb_image.a : ./$(LIBDIR)/stb_image.cpp
	g++ -c -o $@ $< -I $(HEADDIR)
	
./$(LIBDIR)/FastNoise.a : ./$(LIBDIR)/FastNoise.cpp
	g++ -c -o $@ $< -I $(HEADDIR)
	
./$(LIBDIR)/lodepng.a : ./$(LIBDIR)/lodepng.cpp
	g++ -c -o $@ $< -I $(HEADDIR)


clean:
	@rm -f $(LIBDIR)/*.a
