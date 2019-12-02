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

        int gradoPierna;

        // Variable auxiliar de movimiento,
        // Si está rotando hacia delante true.
        // Si está rotando hacia atrás false.
        bool rotando;

    public:
        Pierna();

        void draw(int modoD, bool modoV[]);

        void setRotando(bool rot);

        void cambiarGradoPierna(int grado);

        void animacionAndar(float velocidad);
} ;

#endif