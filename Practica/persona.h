#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED

#include "aux.h"
#include "tronco.h"
#include "pierna.h"
#include "sombrero.h"
#include "esfera.h"
#include "material.h"

class Persona
{
   private:
      Pierna *piernaIzq,
            *piernaDer;
      Tronco *tronco;
      Esfera *cabeza;
      Sombrero *sombrero;

      // Orientación
      int orientacion;
      // Avance
      float avance;
      // Posición
      Tupla3f c = {0,0,0};

   public:
      Persona();

      // Dibujar persona
      void draw(int modoD, bool modoV[]);
      
      // Rotar
      void rotar(int grados);

      // Modificar avance
      void avanzar(float mod);

      // Animación automática
      void andar(float velocidad);
      void setRotacion180();

      void moverGradoLibertad(int numero, float cambio);

      // Selección de colores
      void setColor(float R, float G, float B, int tipo);
      void setColorPiel(float R, float G, float B);
      void setColorPantalones(float R, float G, float B);
      void setColorCamiseta(float R, float G, float B);
      void setColorSombrero(float R, float G, float B);

      // Selección de materiales
      void setMaterial(Material & mat);
      void setMaterialPiel(Material & mat);
      void setMaterialPantalones(Material & mat);
      void setMaterialCamiseta(Material & mat);
      void setMaterialSombrero(Material & mat);

      // Cambio de tapas
      void cambiarTapas();

      // Coordenadas del objeto
      void modificarCoordenadas(int x, int y, int z);
      inline Tupla3f getCoordenadas(){ return c; };
} ;

#endif