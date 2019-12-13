// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "ply_reader.h"
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // Contructor
   Malla3D();

   // Cambiar el vector de color
   void setColor(float R, float G, float B, int tipo);

   // dibuja el objeto en modo inmediato
   virtual void draw_ModoInmediato(int modo);

   // Función para crear el VBO
   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );

   // dibuja el objeto en modo diferido (usando VBOs)
   virtual void draw_ModoDiferido(int modo);

   // dibuja el modo ajedrez
   virtual void draw_ModoAjedrez();

   void draw(int modoD, bool modoV[]);

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(int modoD, int modoV, bool ajedrez) ;

   void crearAjedrez();

   void setMaterial(Material mat);

   void setTexturas(Textura tex);

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   void calcular_normales_caras();

   virtual void calcular_texturas(){}

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ;   // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> f_a;  // terna para el modo ajedrez
   std::vector<Tupla3f> c[3]; // Colores: 0->sólido, 1->puntos, 2->lineas
   std::vector<Tupla3f> c_a;
   std::vector<Tupla3f> nc;   // Vector de normales de las caras
   std::vector<Tupla3f> nv;   // Vector de normales de los vértices
   // Texturas
   std::vector<Tupla2f> ct;
   Textura *t = nullptr;
   // Material
   Material *m = nullptr;

   GLuint id_ind, id_ver, id_col[3], id_nor, id_tex;
} ;


#endif
