#include "Engine.h"
#include "Textures.h"


int main(int argc, char*argv[])
{
    Engine Test;
    Test.init(500, 500);
    Test.setBackgroundColor(0.4f, 0.4f, 0.8f, 1.f);
    Test.run();
    return 0;
}
