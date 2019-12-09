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
//    Tupla3f v0(lado/2,-lado/2,lado/2), v1(lado/2,-lado/2,-lado/2), v2(-lado/2,-lado/2,-lado/2), v3(-lado/2,-lado/2,lado/2),
//            v4(lado/2,lado/2,lado/2),  v5(lado/2,lado/2,-lado/2),  v6(-lado/2,lado/2,-lado/2),  v7(-lado/2,lado/2,lado/2);
    Tupla3f v0(-lado/2,lado/2,lado/2),  v1(-lado/2,-lado/2,lado/2),  v2(lado/2,-lado/2,lado/2),  v3(lado/2,lado/2,lado/2),
            v4(-lado/2,lado/2,-lado/2), v5(-lado/2,-lado/2,-lado/2), v6(lado/2,-lado/2,-lado/2), v7(lado/2,lado/2,-lado/2);
   
   v.push_back(v0);
   v.push_back(v1);
   v.push_back(v2);
   v.push_back(v3);
   v.push_back(v4);
   v.push_back(v5);
   v.push_back(v6);
   v.push_back(v7);

   //Triangulos
   Tupla3i  f0(0,1,3), f1(1,2,3),   // Cara de frente
            f2(1,5,2), f3(5,6,2),   // Cara de abajo
            f4(4,0,7), f5(0,3,7),   // Cara de arriba
            f6(7,6,4), f7(6,5,4),   // Cara posterior
            f8(3,2,7), f9(2,6,7),   // Cara derecha
            f10(4,5,0),f11(5,1,0);  // Cara izquierda

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
}

void Cubo::calcular_texturas(){
    ct.push_back({0.0,0.0});
    ct.push_back({0.0,1.0});
    ct.push_back({1.0,1.0});
    ct.push_back({1.0,0.0});
    // ct.push_back({1.0,1.0});
    // ct.push_back({1.0,0.0});
    // ct.push_back({0.0,0.0});
    // ct.push_back({0.0,1.0});
}