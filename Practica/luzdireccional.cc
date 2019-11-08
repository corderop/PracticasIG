#include "aux.h"
#include "luzdireccional.h"

LuzDireccional::LuzDireccional( Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){

    this->posicion[0] = direccion[0];
    this->posicion[1] = direccion[1];
    this->posicion[2] = direccion[2];
    this->posicion[3] = 0.0; // Para luz direccional

    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
}