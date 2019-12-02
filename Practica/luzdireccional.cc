#include "aux.h"
#include "luzdireccional.h"

LuzDireccional::LuzDireccional( Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){

    alpha = direccion[0];
    beta = direccion[1];

    calcularDireccion();
    this->posicion[3] = 0.0; // Para luz direccional

    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
}

void LuzDireccional::variarAnguloAlpha(float incremento){
    alpha += incremento;
    calcularDireccion();
}

void LuzDireccional::variarAnguloBeta(float incremento){
    beta += incremento;
    calcularDireccion();
}

void LuzDireccional::calcularDireccion(){
    posicion[0] = sin(alpha*(PI/180));                      // x
    posicion[1] = sin(beta*(PI/180));                       // y
    posicion[2] = cos(alpha*(PI/180))*cos(beta*(PI/180));   // z
}