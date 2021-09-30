#include "Engine.h"
#include "Textures.h"


int main(int argc, char*argv[])
{
    Engine test;
    test.init("./shaders/nuage.vs", "./shaders/nuage.fs", 500, 500);
    test.setBackgroundColor(0.4f, 0.4f, 0.8f, 1.f);
    test.run();
    return 0;
}
