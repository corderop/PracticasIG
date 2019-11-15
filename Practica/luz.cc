#include "aux.h"
#include "luz.h"

void Luz::activar(){
    // Activamos la luz
    glEnable(id);

    // Configuramos sus respectivos colores
    glLightfv( id, GL_AMBIENT, colorAmbiente);
    glLightfv( id, GL_DIFFUSE, colorDifuso);
    glLightfv( id, GL_SPECULAR, colorEspecular);

    // Configuramos su posición en escena
    glLightfv(id, GL_POSITION, posicion);
}

bool Luz::esDireccional(){
    return posicion[3]==0;
}