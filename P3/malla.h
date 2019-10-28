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
   void draw_ModoInmediato(int modo);

   // Función para crear el VBO
   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(int modo);

   // dibuja el modo ajedrez
   void draw_ModoAjedrez();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(int modoD, int modoV, bool ajedrez) ;

   void crearAjedrez();

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ;   // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> f_a;  // terna para el modo ajedrez
   std::vector<Tupla3f> c[3]; // Colores: 0->sólido, 1->puntos, 2->lineas

   GLuint id_ind, id_ver, id_col[3];

   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif