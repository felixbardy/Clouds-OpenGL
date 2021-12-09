#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

#include "Mesh.h"

namespace Shapes
{
    void initShapes();

    void initCube();   //!< Initialise le mesh de cube
    void initTerrain(); //!<Initialise un mesh de terrain

    extern Mesh cube;
    extern Mesh terrain;
}; // namespace Shapes

#endif //SHAPES_H
