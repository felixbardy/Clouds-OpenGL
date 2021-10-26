#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

#include "Mesh.h"

namespace Shapes
{
    void initShapes();

    void initCube();   //!< Initialise le mesh de cube
    extern Mesh cube;
}; // namespace Shapes

#endif //SHAPES_H