#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

class Camara
{
    private:
        Tupla3f eye,
                at,
                up;
        int tipo; // 0 - Ortográfica, 1 - Perspectiva
        float fov, aspect, near, far;

        void rotar(float g, char eje, int vector);
        Tupla3f matrizRotacion();

    public:

        Camara(int tipo, Tupla3f ojo, Tupla3f arriba, Tupla3f punto);

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
} ;

#endif