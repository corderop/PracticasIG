#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

Malla3D::Malla3D(){
   id_ind = id_ver = id_col[0] = id_col[1] = id_col[2] = 0;
}

void Malla3D::crearAjedrez(){
   int a=0, 
       b=ceil(f.size()/2);

   f_a.resize(f.size());

   for(int i=0; i<f.size(); i++){
      if(i%2 == 0){
         f_a[a] = f[i];
         a++;
      }
      else{
         f_a[b] = f[i];
         b++;
      }
   }
}

void Malla3D::setColor(float R, float G, float B, int tipo){

   // Evitar segmentation fault por que se salga del vector
   if(tipo>=0 && tipo<=2){

      c[tipo].clear();

      for(int i=0; i<v.size(); i++){
         Tupla3f color(R,G,B);

         c[tipo].push_back(color);
      }

   }
   else std::cout<<"setColor: Tipo mal indicado"<<std::endl;
}

void Malla3D::draw_ModoInmediato(int modo)
{

  // Activamos el uso de un array de vértices
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, v.data());
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, c[modo].data());

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


void Malla3D::draw_ModoDiferido(int modo)
{
   if(id_ver == 0)
      id_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*sizeof(float)*3, v.data());
   
   if(id_ind == 0)
      id_ind = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*sizeof(int)*3, f.data());
   
   if(id_col[modo] == 0)
      id_col[modo] = CrearVBO(GL_ARRAY_BUFFER, c[modo].size()*sizeof(float)*3, c[modo].data());

   // especificar localización y formato de la tabla de vértices, habilitar tabla
   glBindBuffer( GL_ARRAY_BUFFER, id_ver );  // activar VBO de vértices
   glVertexPointer( 3, GL_FLOAT, 0, 0 );     // especifica formato y offset (=0)
   glBindBuffer( GL_ARRAY_BUFFER, 0 );       // desactivar VBO de vértices.
   
   glBindBuffer( GL_ARRAY_BUFFER, id_col[modo] ); 
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer( GL_ARRAY_BUFFER, 0 );

   // // Para que no se vean sombras
   // glShadeModel(GL_FLAT);
   
   glEnableClientState( GL_VERTEX_ARRAY );   // habilitar tabla de vértices
   glEnableClientState(GL_COLOR_ARRAY);

   // visualizar triángulos con glDrawElements (puntero a tabla == 0)
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_ind); // activar VBO de triángulos
   glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0 ) ;
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );     // desactivar VBO de triángulos
   // desactivar uso de array de vértices
   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState( GL_COLOR_ARRAY );
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw_ModoAjedrez(){

   if(f_a.empty())
      crearAjedrez();

   // Para que no se vean sombras
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, v.data());
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_FLOAT, 0, c[0].data());

   glShadeModel(GL_FLAT);

   // Esto lo hago por si el objeto tiene un número de triángulos impar
   int mitad = floor(f_a.size()/2),
       mitad2 = ceil(f_a.size()/2);

   glDrawElements(GL_TRIANGLES, mitad*3, GL_UNSIGNED_INT, f_a.data());
   
   setColor(0.0, 1.0, 1.0, 0);

   // Dibujamos los elementos
   glDrawElements(GL_TRIANGLES, mitad2*3, GL_UNSIGNED_INT, f_a.data()[mitad]);

   // Hecho para el redibujado
   setColor(1.0, 0.0, 0.0, 0);

   // Desactivamos el uso de ambos arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}

void Malla3D::draw(int modoD, int modoV, bool ajedrez)
{

   // Activamos aquí el color para que funcione para ambos modos   
   if(modoD == 1){
      if(ajedrez)
         draw_ModoAjedrez();
      else
         draw_ModoInmediato(modoV);
   }
   else if(modoD == 2)
      draw_ModoDiferido(modoV);

}

// Cálculo de normales

void Malla3D::calcular_normales(){

   Tupla3f aux(0,0,0);
   nv.resize(v.size(), aux);

   for(int i=0; i<f.size(); i++){
      nv[f[i][0]] = nv[f[i][0]] + nc[i];
      nv[f[i][1]] = nv[f[i][1]] + nc[i];
      nv[f[i][2]] = nv[f[i][2]] + nc[i];
   }

   // Crear la versión normalizada
   for(int i=0; i<nv.size(); i++)
      nv[i] = nv[i].normalized();

}

void Malla3D::calcular_normales_caras(){

   for(int i=0; i<f.size(); i++){
      Tupla3f a = v[f[i][2]] - v[f[i][0]];
      Tupla3f b = v[f[i][2]] - v[f[i][1]];
      
      Tupla3f m = a.cross(b);
      Tupla3f n = m.normalized();

      nc.push_back(n);
   }
}