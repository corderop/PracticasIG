#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

class Camara
{
    private:
        Tupla3f eye,
                at,
                up;
        int tipo; // Ortogonal o Perspectiva
        float left, right, near, far;

    public:

        Camara();

        // Rotar la cámara
        void rotarXExaminar(float angle);
        void rotarYExaminar(float angle);
        void rotarZExaminar(float angle);
        void rotarXFirstPerson(float angle);
        void rotarYFirstPerson(float angle);
        void rotarYFirstPerson(float angle);

        // Mover la cámara
        void mover(float x, float y, float z);

        // Hacer zoom
        void zoom(float factor);


} ;

#endif