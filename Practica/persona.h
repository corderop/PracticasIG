#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED

#include "aux.h"
#include "tronco.h"
#include "pierna.h"
#include "esfera.h"
#include "material.h"

class Persona
{
   private:
      Pierna *piernaIzq,
            *piernaDer;
      Tronco *tronco;
      Esfera *cabeza;

      // Orientación
      int orientacion;
      // Avance
      float avance;
      // Posición
      float x,z;

   public:
      Persona();

      // Dibujar persona
      void draw(int modoD, bool modoV[]);
      
      // Rotar
      void rotar(int grados);

      // Modificar avance
      void avanzar(float mod);

      void andar(float velocidad);

      void moverGradoLibertad(int numero, float cambio);

      // Selección de colores
      void setColor(float R, float G, float B, int tipo);
      void setColorPiel(float R, float G, float B);
      void setColorPantalones(float R, float G, float B);
      void setColorCamiseta(float R, float G, float B);

      // Selección de materiales
      void setMaterial(Material & mat);
      void setMaterialPiel(Material & mat);
      void setMaterialPantalones(Material & mat);
      void setMaterialCamiseta(Material & mat);

      // Cambio de tapas
      void cambiarTapas();
} ;

#endif