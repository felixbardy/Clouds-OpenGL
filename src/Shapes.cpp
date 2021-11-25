#include "Shapes.h"
#include <cassert>

namespace Shapes
{
    void initShapes() {
        std::cout<<"Initialisation des meshs primitifs..."<<std::endl;

        initCube();
        initTerrain();

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

    void initTerrain()
    {
      const int width = 50;
      const int height = 50;

      const int maxHeight = 12;
      FastNoise fastNoise;
      fastNoise.SetSeed(42);
      fastNoise.SetNoiseType(FastNoise::NoiseType::Perlin);
      fastNoise.SetFractalOctaves(5);
      fastNoise.SetFrequency(0.1);
      fastNoise.SetFractalLacunarity(2.0);
      auto getNoise = [fastNoise](int x, int y) -> float{return ((fastNoise.GetNoise(x, y)+1)/2)*maxHeight;};


      assert(width >= 2 && height >=2);

      std::cout<<"Terrain...";

      std::vector<float> vertices;
      for(int i=0; i<width; i++)
      {
          for(int j=0; j<height; j++)
          {
             vertices.push_back(i);
             //vertices.push_back(((fastNoise.GetNoise(i, j)+1)/2)*maxHeight);
             vertices.push_back(getNoise(i, j));
             vertices.push_back(j);
          }
      }

      std::vector<uint> verticesOrder;
      for(int i=0; i<width-1; i++)
      {
          for(int j=0; j<height-1; j++)
          {
              // 1ere face
              verticesOrder.push_back((i+1)*(height)+j+1);
              verticesOrder.push_back(i*height+j+1);
              verticesOrder.push_back((i+1)*(height)+j);

              // 2eme face
              verticesOrder.push_back((i+1)*(height)+j);
              verticesOrder.push_back(i*height+j+1);
              verticesOrder.push_back((i)*(height)+j);
          }
      }

      std::vector<float> uv;
      for(int i=0; i<3; i++)
      {
          for(int j=0; j<3; j++)
          {
              uv.push_back((float)i/2);
              uv.push_back((float)j/2);
          }
      }

      int weight[6] = {4, 1, 3, 3, 1, 0};
      std::vector<uint> uvIndex;
      for(int i=0; i<width-1; i++)
      {
          for(int j=0; j<height-1; j++)
          {
              int typeTerrain = 0;
              float heightPoint = getNoise (i, j);

              if(heightPoint<maxHeight/4)
              {
                  typeTerrain = 3;
              }else if(heightPoint<maxHeight/2)
              {
                  typeTerrain = 4;
              }else if(heightPoint<3*(maxHeight/4))
              {
                  typeTerrain = 1;
              }else
              {
                  typeTerrain = 0;
              }

              for(int k=0; k<6; k++)
              {

                  uvIndex.push_back(weight[k]+typeTerrain);
              }

              // uvIndex.push_back(4);
              // uvIndex.push_back(1);
              // uvIndex.push_back(3);
              //
              // uvIndex.push_back(3);
              // uvIndex.push_back(1);
              // uvIndex.push_back(0);

              // // 1ere face
              // uvIndex.push_back((i+1)*(height)+j+1);
              // uvIndex.push_back(i*height+j+1);
              // uvIndex.push_back((i+1)*(height)+j);
              //
              // // 2eme face
              // uvIndex.push_back((i+1)*(height)+j);
              // uvIndex.push_back(i*height+j+1);
              // uvIndex.push_back((i)*(height)+j);
          }
      }

      // Pour afficher une image entière
      // std::vector<float> uv;
      // for(int i=0; i<width; i++)
      // {
      //     for(int j=0; j<height; j++)
      //     {
      //         uv.push_back((float)i/(width-1));
      //         uv.push_back((float)j/(height-1));
      //     }
      // }
      //
      // std::vector<uint> uvIndex;
      // for(int i=0; i<width-1; i++)
      // {
      //     for(int j=0; j<height-1; j++)
      //     {
      //         // 1ere face
      //         uvIndex.push_back((i+1)*(height)+j+1);
      //         uvIndex.push_back(i*height+j+1);
      //         uvIndex.push_back((i+1)*(height)+j);
      //
      //         // 2eme face
      //         uvIndex.push_back((i+1)*(height)+j);
      //         uvIndex.push_back(i*height+j+1);
      //         uvIndex.push_back((i)*(height)+j);
      //     }
      // }

      terrain = Mesh();
      terrain.setPolygon(vertices, verticesOrder, uv, uvIndex/*, color, colorId*/);
      std::cout<<"OK!"<<std::endl;
    }

    Mesh cube;
    Mesh terrain;
} // namespace Shapes
