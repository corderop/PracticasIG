#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED

#include "aux.h"
#include "tronco.h"
#include "pierna.h"
#include "esfera.h"

class Persona
{
   private:
    Pierna *piernaIzq,
           *piernaDer;
    Tronco *tronco;
    Esfera *cabeza;

    // Orientación
    int orientacion;
    // Avance
    float avance;

   public:
   Persona();

   // Dibujar persona
   void draw(int modoD, bool modoV[]);
   
   // Rotar
   void rotar(int grados);

   // Modificar avance
   void avanzar(float mod);

   void andar(float velocidad);
} ;

#endif