// #############################################################################
// CLASE CUADRO
// #############################################################################

#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "aux.h"

class Cuadro : public Malla3D
{
    public:

        // Inicializa vértices y triángulos pero no colores
        Cuadro(float l=1);

        // Calcular las coordenadas de texturas del cuadro
        void calcular_texturas();
} ;

#endif