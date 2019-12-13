#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz{

    protected:
      Tupla4f posicion;
      GLenum id;
      Tupla4f colorAmbiente;
      Tupla4f colorDifuso;
      Tupla4f colorEspecular;

    public:
      void activar();
      bool esDireccional();

     virtual void variarAnguloAlpha(float incremento){};
     virtual void variarAnguloBeta(float incremento){};
     virtual void variarPosicion(float x, float y, float z){};
};

#endif