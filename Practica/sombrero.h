#ifndef SOMBRERO_H_INCLUDED
#define SOMBRERO_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "material.h"

class Sombrero
{
   private:
        Cilindro *arriba,
                 *abajo;

        // Altura del gorro
        float altura;

        // Facilitar la animación automática
        bool subiendo = true;

        // Altura máxima y mínima posible
        const int ALT_MAX = 15, 
                  ALT_MIN = 11;

    public:
        Sombrero();

        // Dibuja el sombrero
        void draw(int modoD, bool modoV[]);

        // Suma a la altura del sombrero
        void cambiarAlturaSombrero(float suma);

        // Realiza la animación para andar
        void animacionAndar(float velocidad);

        // Seleccionar el color de todos los elementos de la 
        // Sombrero a la vez
        void setColor(float R, float G, float B, int tipo);

        // Seleccionar el material
        void setMaterial(Material &mat);

        // Modificación de tapas
        void cambiarTapas();
} ;

#endif