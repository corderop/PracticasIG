#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

Malla3D::Malla3D(){
   id_ind = id_ver = 0;
}

void Malla3D::setColor(float R, float G, float B){
   Tupla3f c0(R,G,B), c1(R,G,B), c2(R,G,B), c3(R,G,B),
           c4(R,G,B), c5(R,G,B), c6(R,G,B), c7(R,G,B);

   c[0] = c0;
   c[1] = c1;
   c[2] = c2;
   c[3] = c3;
   c[4] = c4;
   c[5] = c5;
   c[6] = c6;
   c[7] = c7;
}

void Malla3D::draw_ModoInmediato()
{

  // Activamos el uso de un array de vértices
  glEnable(GL_CULL_FACE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, v.data());
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, c.data());

  // Para que no se vean sombras
  glShadeModel(GL_FLAT);

  // Dibujamos los elementos
  glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());

  // Desactivamos el uso de ambos arrays
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

GLuint Malla3D::CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram ){
   GLuint id_vbo ;                     // resultado: identificador de VBO
   glGenBuffers( 1, & id_vbo );        // crear nuevo VBO, obtener identificador (nun-ca 0)
   glBindBuffer( tipo_vbo, id_vbo );   // activar el VBO usando su identificador
   // esta instrucción hace la transferencia de datos desde RAM hacia GPU
   glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );
   glBindBuffer( tipo_vbo, 0 );        // desactivación del VBO (activar 0)
   return id_vbo ;                     // devolver el identificador resultado
}


void Malla3D::draw_ModoDiferido()
{
   if(id_ver == 0)
      id_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*sizeof(float)*3, v.data());
   
   if(id_ind == 0)
      id_ind = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*sizeof(int)*3, f.data());

   // especificar localización y formato de la tabla de vértices, habilitar tabla
   glBindBuffer( GL_ARRAY_BUFFER, id_ver );  // activar VBO de vértices
   glVertexPointer( 3, GL_FLOAT, 0, 0 );     // especifica formato y offset (=0)
   glBindBuffer( GL_ARRAY_BUFFER, 0 );       // desactivar VBO de vértices.
   glEnableClientState( GL_VERTEX_ARRAY );   // habilitar tabla de vértices
   
   // visualizar triángulos con glDrawElements (puntero a tabla == 0)
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_ind); // activar VBO de triángulos
   glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0 ) ;
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );     // desactivar VBO de triángulos
   // desactivar uso de array de vértices
   glDisableClientState( GL_VERTEX_ARRAY );
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw_ModoAjedrez(){

   // Para que no se vean sombras

   glEnable(GL_CULL_FACE);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, v.data());
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_FLOAT, 0, c.data());

   glShadeModel(GL_FLAT);

   glDrawElements(GL_TRIANGLES, f.size()*3/2, GL_UNSIGNED_INT, f.data());
   setColor(0.0, 1.0, 1.0);

   // Dibujamos los elementos
   glDrawElements(GL_TRIANGLES, f.size()*3/2, GL_UNSIGNED_INT, f.data()[6]);

   // Hecho para el redibujado
   setColor(1.0, 0.0, 0.0);

   // Desactivamos el uso de ambos arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}

void Malla3D::draw(int modo, bool ajedrez)
{
   // Activamos aquí el color para que funcione para ambos modos   
   if(modo == 1){
      if(ajedrez)
         draw_ModoAjedrez();
      else
         draw_ModoInmediato();
   }
   else if(modo == 2)
      draw_ModoDiferido();

}

