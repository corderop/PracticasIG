#include "aux.h"
#include "luzposicional.h"

LuzPosicional::LuzPosicional( Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){

    this->posicion[0] = posicion[0];
    this->posicion[1] = posicion[1];
    this->posicion[2] = posicion[2];
    this->posicion[3] = 1.0; // Para luz posicional

    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
}

void LuzPosicional::variarPosicion(float x, float y, float z){
    posicion[0] += x;
    posicion[1] += y;
    posicion[2] += z;
}
