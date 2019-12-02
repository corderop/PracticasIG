#ifndef TRONCO_H_INCLUDED
#define TRONCO_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "brazo.h"
#include "material.h"

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

   void moverBrazo(int numero, float cambio);

   // Set color
   void setColor(float R, float G, float B, int tipo);
   void setColorCuerpo(float R, float G, float B, int tipo);
   void setColorBrazos(float R, float G, float B, int tipo);

   // Selección del material
   void setMaterial(Material &mat);
   void setMaterialCuerpo(Material &mat);
   void setMaterialBrazos(Material &mat);

   void cambiarTapas();
} ;

#endif