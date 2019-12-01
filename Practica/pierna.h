#ifndef PIERNA_H_INCLUDED
#define PIERNA_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "esfera.h"

class Pierna
{
   private:
    Cilindro *tobillo,
             *antepierna;
    Esfera *rodilla;

   public:
   Pierna();

   void draw(int modoD, int modoV, bool ajedrez);

} ;

#endif