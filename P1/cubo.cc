/*
* Practicas de IG
* Domingo Martin Perandres© 2014-2018
* dmartin@ugr.es
*
* GPL 3
*/

#include "cubo.h"

/**
*
*@param
*@returns
*/

_cubo::_cubo(float Size)
{
  Vertices.resize(8);

  Vertices[0]=_vertex3f(Size/2,-Size/2,Size/2);
  Vertices[1]=_vertex3f(Size/2,-Size/2,-Size/2);
  Vertices[2]=_vertex3f(-Size/2,-Size/2,-Size/2);
  Vertices[3]=_vertex3f(-Size/2,-Size/2,Size/2);
  Vertices[4]=_vertex3f(Size/2,Size/2,Size/2);
  Vertices[5]=_vertex3f(Size/2,Size/2,-Size/2);
  Vertices[6]=_vertex3f(-Size/2,Size/2,-Size/2);
  Vertices[7]=_vertex3f(-Size/2,Size/2,Size/2);

  Triangles.resize(12);

  // Cara de abajo ////
  Triangles[0]=_vertex3ui(3,0,1);
  Triangles[1]=_vertex3ui(1,2,3);

  // Cara de arriba ////
  Triangles[2]=_vertex3ui(4,5,6);
  Triangles[3]=_vertex3ui(6,7,4);

  // Cara frente ////
  Triangles[4]=_vertex3ui(4,0,3);
  Triangles[5]=_vertex3ui(3,7,4);

  // Cara posterior ////
  Triangles[6]=_vertex3ui(1,5,6);
  Triangles[7]=_vertex3ui(6,2,1);

  // Cara derecha ////
  Triangles[8]=_vertex3ui(4,5,1);
  Triangles[9]=_vertex3ui(1,0,4);

  // Cara izquierda ////
  Triangles[10]=_vertex3ui(6,7,3);
  Triangles[11]=_vertex3ui(3,2,6);
}
