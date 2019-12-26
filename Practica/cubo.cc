#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
    // Vertices
    // 8 principales 0-7
    // 4 duplicados para texturas 8-11
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
    v.push_back(v0); // 8
    v.push_back(v1); // 9
    v.push_back(v2); // 10
    v.push_back(v3); // 11
    v.push_back(v4); // 12
    v.push_back(v5); // 13
    v.push_back(v6); // 14
    v.push_back(v7); // 15

   // Triangulos
   // 12 principales
   // 4 duplicados para texturas (cara superior e inferior)
    Tupla3i f0(0,1,3),    f1(1,2,3),     // Cara de frente
            f2(1,5,2),    f3(5,6,2),     // Cara de abajo
            f4(4,0,7),    f5(0,3,7),     // Cara de arriba
            f6(7,6,4),    f7(6,5,4),     // Cara posterior
            f8(3,2,7),    f9(2,6,7),     // Cara derecha
            f10(4,5,0),   f11(5,1,0),    // Cara izquierda
            // Dupliacadas
            f12(8,9,11),  f13(9,10,11),  // Cara de frente
            f14(9,13,10), f15(13,14,10), // Cara de abajo
            f16(12,8,15), f17(8,11,15),  // Cara de arriba
            f18(15,14,12),f19(14,13,12), // Cara posterior
            f20(11,10,15),f21(10,14,15), // Cara derecha
            f22(12,13,8), f23(13,9,8);   // Cara izquierda

    // Cara de frente
    f.push_back(f12);
    f.push_back(f13);
    f.push_back(f0);
    f.push_back(f1);
    // Cara inferior
    f.push_back(f2);
    f.push_back(f3);
    f.push_back(f14);
    f.push_back(f15);
    // Cara superior
    f.push_back(f16);
    f.push_back(f17);
    f.push_back(f4);
    f.push_back(f5);
    // Cara posterior
    f.push_back(f18);
    f.push_back(f19);
    f.push_back(f6);
    f.push_back(f7);
    // Cara derecha
    f.push_back(f8);
    f.push_back(f9);
    f.push_back(f20);
    f.push_back(f21);
    // Cara izquierda
    f.push_back(f10);
    f.push_back(f11);
    f.push_back(f22);
    f.push_back(f23);
}

void Cubo::calcular_texturas(){
    // ct.resize(12);
    // ct[0] = {0,0};
    // ct[1] = {0,1};
    // ct[2] = {1,1};
    // ct[3] = {1,0};
    // ct[4] = {1,0};
    // ct[5] = {1,1};
    // ct[6] = {0,1};
    // ct[7] = {0,0};
    // ct[8] = {0,1};
    // ct[9] = {1,1};
    // ct[10] = {0,0};
    // ct[11] = {1,0};
}