LIBDIR := ./$(LIBDIR)
HEADDIR := ./$(HEADDIR)

all: $(LIBDIR)/glad.a ./$(LIBDIR)/stb_image.a ./$(LIBDIR)/FastNoise.a ./$(LIBDIR)/lodepng.a ./$(LIBDIR)/imgui.a ./$(LIBDIR)/imgui_impl_opengl3.a ./$(LIBDIR)/imgui_impl_glfw.a ./$(LIBDIR)/imgui_draw.a ./$(LIBDIR)/imgui_tables.a ./$(LIBDIR)/imgui_widgets.a ./$(LIBDIR)/imgui_demo.a
	@: #this is for silencing make

./$(LIBDIR)/glad.a: ./$(LIBDIR)/glad.c
	g++ -c -o $@ $< -I $(HEADDIR)

./$(LIBDIR)/stb_image.a : ./$(LIBDIR)/stb_image.cpp
	g++ -c -o $@ $< -I $(HEADDIR)
	
./$(LIBDIR)/FastNoise.a : ./$(LIBDIR)/FastNoise.cpp
	g++ -c -o $@ $< -I $(HEADDIR)
	
./$(LIBDIR)/lodepng.a : ./$(LIBDIR)/lodepng.cpp
	g++ -c -o $@ $< -I $(HEADDIR)
	
./$(LIBDIR)/imgui.a : ./$(LIBDIR)/imgui.cpp ./$(LIBDIR)/imgui.cpp 
	g++ -c -o $@ $< -I $(HEADDIR)

./$(LIBDIR)/imgui_demo.a : ./$(LIBDIR)/imgui_demo.cpp
	g++ -c -o $@ $< -I $(HEADDIR)

./$(LIBDIR)/imgui_impl_opengl3.a : ./$(LIBDIR)/imgui_impl_opengl3.cpp
	g++ -c -o $@ $< -I $(HEADDIR)

./$(LIBDIR)/imgui_impl_glfw.a : ./$(LIBDIR)/imgui_impl_glfw.cpp
	g++ -c -o $@ $< -I -lglfw $(HEADDIR)

./$(LIBDIR)/imgui_draw.a : ./$(LIBDIR)/imgui_draw.cpp
	g++ -c -o $@ $< -I $(HEADDIR)

./$(LIBDIR)/imgui_tables.a : ./$(LIBDIR)/imgui_tables.cpp
	g++ -c -o $@ $< -I $(FLAGS) $(HEADDIR)

./$(LIBDIR)/imgui_widgets.a : ./$(LIBDIR)/imgui_widgets.cpp
	g++ -c -o $@ $< -I $(FLAGS) $(HEADDIR)


clean:
	@rm -f $(LIBDIR)/*.a
