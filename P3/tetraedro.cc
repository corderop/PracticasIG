#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{

   // Vertices
   Tupla3f v0(-100/2,-100/2,-100/2), v1(0,-100/2,100/2), 
           v2(100/2,-100/2,-100/2),  v3(0,100/2,0);

   v.push_back(v0);
   v.push_back(v1);
   v.push_back(v2);
   v.push_back(v3);

   // Triangulos
   Tupla3i  f0(0,1,3),  f1(1,2,3),
            f2(2,0,3),  f3(0,2,1);
   
   f.push_back(f0);
   f.push_back(f1);
   f.push_back(f2);
   f.push_back(f3);

   // Colores
   setColor(1.0, 0.0, 0.0, 0);
   setColor(0.0, 1.0, 0.0, 1);
   setColor(0.0, 0.0, 1.0, 2);

}

