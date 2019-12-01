#ifndef TRONCO_H_INCLUDED
#define TRONCO_H_INCLUDED

#include "aux.h"
#include "cilindro.h"

class Tronco
{
   private:
    Cilindro *cuerpo,
             *brazoIzq,
             *brazoDer;

   public:
   Tronco();

   void draw(int modoD, int modoV, bool ajedrez);

} ;

#endif