#ifndef OBJECTS_H
#define OBJECTS_H

#include "Object.h"
#include "Shapes.h"

class Cube : public Object
{
public:
    Cube() : Object()
    {
        setFaceCulling(true);
        setTextureTypeTo2D();
        setMesh(&Shapes::cube);
    }
    ~Cube() {}
};

class Terrain : public Object
{
public:
  Terrain() : Object()
  {
      setFaceCulling(true);
      setTextureTypeTo2D();
      setMesh(&Shapes::terrain);
  }
  ~Terrain() {}
};



#endif //OBJECTS_H
