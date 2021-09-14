#include "engine.h"



int main()
{
    engine Test;
    Test.init("./shaders/shader.vs", "./shaders/shader.fs", 500, 500);
    Test.setBackgroundColor(0.4f, 0.4f, 0.8f, 1.f);
    Test.run();
    return 0;
}