#include "Shapes.h"

namespace Shapes
{
    void initShapes() {
        std::cout<<"Initialisation des meshs primitifs..."<<std::endl;
        
        initCube();

        std::cout<<"Initialisation terminée!"<<std::endl;
    }

    void initCube()
    {
        std::cout<<"Cube...";
        /** Vertex Order Scheme
        *		   4 - 5
        *		  /   /|
        *		 0 - 1 7
        *		 |   |/
        *		 2 - 3
        */
        std::vector<float> vertices =
        {
            0.f, 1.f, 0.f,   // Top Left front 0
            1.f, 1.f, 0.f,   // Top Right front 1
            0.f, 0.f, 0.f,   // Bottom Left front 2
            1.f, 0.f, 0.f,   // Bottom Right front 3

            0.f, 1.f, 1.f,   // Top Left back 4
            1.f, 1.f, 1.f,   // Top Right back 5
            0.f, 0.f, 1.f,   // Bottom Left back 6
            1.f, 0.f, 1.f    // Bottom Right back 7
        };

        std::vector<uint> verticesOrder =
        {
            // AVANT ARRIERE
            0, 1, 2,
            2, 1, 3,

            5, 4, 7,
            7, 4, 6,

            // DROITE GAUCHE
            1, 5, 3,
            3, 5, 7,

            4, 0, 6,
            6, 0, 2,

            // HAUT BAS
            4, 5, 0,
            0, 5, 1,

            6, 2, 7,
            7, 2, 3
        };

        std::vector<float> uv =
        {
            0.f, 0.f,
            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.f
        };

        std::vector<uint> uvIndex
        {
            1, 2, 0,
            0, 2, 3,

            1, 2, 0,
            0, 2, 3,

            1, 2, 0,
            0, 2, 3,

            1, 2, 0,
            0, 2, 3,

            3, 0, 2,
            2, 0, 1,

            0, 1, 3,
            3, 1, 2
        };
        cube = Mesh();
        cube.setPolygon(vertices, verticesOrder, uv, uvIndex/*, color, colorId*/);
        std::cout<<"OK!"<<std::endl;
    }

    Mesh cube;
} // namespace Shapes
