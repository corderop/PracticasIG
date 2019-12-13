// #############################################################################
// CLASE CUBO
// #############################################################################

#ifndef CUBO_H_INCLUDED
#define CUBO_H_INCLUDED

#include "aux.h"

class Cubo : public Malla3D
{
    private:

        // Calcular las coordenadas de texturas del cubo
        void calcular_texturas() override;

    public:

        // Inicializa vértices y triángulos pero no colores
        Cubo(float l=1);
} ;

#endif
