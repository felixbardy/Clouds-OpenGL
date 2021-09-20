#include "Engine.h"



int main()
{
    Engine Test;
    Test.init("./shaders/felix_test.vs", "./shaders/felix_test.fs", 500, 500);
    Test.setBackgroundColor(0.4f, 0.4f, 0.8f, 1.f);
    Test.run();

    return 0;
}
