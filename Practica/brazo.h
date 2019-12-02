#ifndef BRAZO_H_INCLUDED
#define BRAZO_H_INCLUDED

#include "aux.h"
#include "cilindro.h"

class Brazo
{
    private:
        Cilindro *brazo;

        int gradoBrazo;

        // Variable auxiliar de movimiento,
        // Si está rotando hacia delante true.
        // Si está rotando hacia atrás false.
        bool rotando;

    public:
        Brazo();

        void draw(int modoD, bool modoV[]);

        void setRotando(bool rot);

        void cambiarGradoBrazo(int grado);

        void animacionAndar(float velocidad);

} ;

#endif