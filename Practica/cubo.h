// #############################################################################
// CLASE CUBO
// #############################################################################

#ifndef CUBO_H_INCLUDED
#define CUBO_H_INCLUDED

#include "aux.h"

class Cubo : public Malla3D
{
    public:

        // Inicializa vértices y triángulos pero no colores
        Cubo(float l=1);

        // Calcular las coordenadas de texturas del cubo por defecto
        // (Aplicar una textura cuadrada de igual forma a todas las caras del cubo)
        void calcular_texturas();
} ;

#endif
