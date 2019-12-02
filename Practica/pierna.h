#ifndef PIERNA_H_INCLUDED
#define PIERNA_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "esfera.h"
#include "material.h"

class Pierna
{
   private:
        Cilindro *tobillo,
                 *antepierna;
        Esfera *rodilla;

        int gradoPierna;

        // Variable auxiliar de movimiento,
        // Si está rotando hacia alante true.
        // Si está rotando hacia atrás false.
        bool rotando;

    public:
        Pierna();

        // Dibuja la pierna
        void draw(int modoD, bool modoV[]);

        // Cambiar si en ese momento se está rotando hacia alante
        // o hacia atras.
        void setRotando(bool rot);

        // Suma al grado de rotación de la pierna
        void cambiarGradoPierna(int grado);

        // Realiza la animación para andar
        void animacionAndar(float velocidad);

        // Seleccionar el color de todos los elementos de la 
        // pierna a la vez
        void setColor(float R, float G, float B, int tipo);
        void setColorTobillo(float R, float G, float B, int tipo);
        void setColorAntepierna(float R, float G, float B, int tipo);
        void setColorRodilla(float R, float G, float B, int tipo);

        // Seleccionar el material
        void setMaterial(Material &mat);
        void setMaterialTobillo(Material &mat);
        void setMaterialAntepierna(Material &mat);
        void setMaterialRodilla(Material &mat);

        // Modificación de tapas
        void cambiarTapas();
} ;

#endif