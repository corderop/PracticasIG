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

   public:
   Persona();

   void draw(int modoD, int modoV, bool ajedrez);

} ;

#endif