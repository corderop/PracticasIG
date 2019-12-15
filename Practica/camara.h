#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

class Camara
{
    private:
        Tupla3f eye,
                at,
                up;
        float left, top;
        int tipo; // 0 - Ortográfica, 1 - Perspectiva
        float fov, aspect, near, far;

        // Ejes sobre la camara y vector de dirección
        Tupla3f Vv, Vx, Vy;

        void rotarFPS(float g, char eje);
        void rotarAlrededor(float g, char eje);
        Tupla3f matrizRotacion(Tupla3f eje, Tupla3f v, float g);

    public:

        Camara(int tp, Tupla3f ojo, Tupla3f arriba, Tupla3f punto, float alto, float ancho);

        // Rotar la cámara
        void rotarXExaminar(float angle);
        void rotarYExaminar(float angle);
        void rotarZExaminar(float angle);
        void rotarXFirstPerson(float angle);
        void rotarYFirstPerson(float angle);

        // Mover la cámara
        void mover(float x, float y, float z);

        // Hacer zoom
        void zoom(float factor);

        // Seleccionar el observador
        void setObserver();

        // Seleccionar la proyección
        void setProyeccion();

        inline void setAt(Tupla3f punto){ at = punto; };
} ;

#endif