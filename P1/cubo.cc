#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   // Vertices
   Tupla3f v0(lado/2,-lado/2,lado/2), v1(lado/2,-lado/2,-lado/2), v2(-lado/2,-lado/2,-lado/2), v3(-lado/2,-lado/2,lado/2),
           v4(lado/2,lado/2,lado/2),  v5(lado/2,lado/2,-lado/2),  v6(-lado/2,lado/2,-lado/2),  v7(-lado/2,lado/2,lado/2);

   v.push_back(v0);
   v.push_back(v1);
   v.push_back(v2);
   v.push_back(v3);
   v.push_back(v4);
   v.push_back(v5);
   v.push_back(v6);
   v.push_back(v7);

   //Triangulos
   Tupla3i  f0(0,2,1),  f1(0,3,2),   // Cara de abajo
            f2(4,5,6),  f3(6,7,4),   // Cara de arriba
            f4(0,4,3),  f5(4,7,3),   // Cara de frente
            f6(1,2,6),  f7(6,5,1),   // Cara posterior
            f8(0,1,5),  f9(5,4,0),   // Cara derecha
            f10(2,3,7), f11(7,6,2);  // Cara izquierda

   f.push_back(f0);
   f.push_back(f1);
   f.push_back(f2);
   f.push_back(f3);
   f.push_back(f4);
   f.push_back(f5);
   f.push_back(f6);
   f.push_back(f7);
   f.push_back(f8);
   f.push_back(f9);
   f.push_back(f10);
   f.push_back(f11);

   // Color
   Tupla3f c0(1.0,0.0,0.0), c1(1.0,0.0,0.0), c2(1.0,0.0,0.0), c3(1.0,0.0,0.0),
           c4(1.0,0.0,0.0), c5(1.0,0.0,0.0), c6(1.0,0.0,0.0), c7(1.0,0.0,0.0);

   c.push_back(c0);
   c.push_back(c1);
   c.push_back(c2);
   c.push_back(c3);
   c.push_back(c4);
   c.push_back(c5);
   c.push_back(c6);
   c.push_back(c7);
}

