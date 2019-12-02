#ifndef TRONCO_H_INCLUDED
#define TRONCO_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "brazo.h"

class Tronco
{
   private:
    Cilindro *cuerpo;
    Brazo    *brazoIzq,
             *brazoDer;

   public:
   Tronco();

   void draw(int modoD, bool modoV[]);

   void animacionAndar(float velocidad);

} ;

#endif