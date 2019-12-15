#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

Malla3D::Malla3D(){
   id_ind = id_ver = id_col[0] = id_col[1] = id_col[2] = id_nor = 0;
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

   setColor(1.0, 0.0, 0.0, 3);
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
   else if(tipo == 3){
      c_a.clear();

      for(int i=0; i<v.size(); i++){
         Tupla3f color(R,G,B);

         c_a.push_back(color);
      }

   }
   else std::cout<<"setColor: Tipo mal indicado"<<std::endl;
}

void Malla3D::draw_ModoInmediato(int modo)
{

  // Activamos el uso de un array de vértices
  glVertexPointer(3, GL_FLOAT, 0, v.data());
  glColorPointer(3, GL_FLOAT, 0, c[modo].data());
  glNormalPointer( GL_FLOAT, 0, nv.data() );

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState( GL_NORMAL_ARRAY );
  if(!ct.empty()){
      glEnableClientState( GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
  }
  // Dibujamos los elementos
  glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());

  // Desactivamos el uso de ambos arrays
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState( GL_TEXTURE_COORD_ARRAY);
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

   if(id_nor == 0)
      id_nor = CrearVBO(GL_ARRAY_BUFFER, nv.size()*sizeof(float)*3, nv.data());
   
   if(id_tex == 0)
      id_tex = CrearVBO(GL_ARRAY_BUFFER, ct.size()*sizeof(float)*2, ct.data());

   // especificar localización y formato de la tabla de vértices, habilitar tabla
   glBindBuffer( GL_ARRAY_BUFFER, id_ver );  // activar VBO de vértices
   glVertexPointer( 3, GL_FLOAT, 0, 0 );     // especifica formato y offset (=0)
   glBindBuffer( GL_ARRAY_BUFFER, 0 );       // desactivar VBO de vértices.
   
   glBindBuffer( GL_ARRAY_BUFFER, id_col[modo] ); 
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer( GL_ARRAY_BUFFER, 0 );

   glBindBuffer( GL_ARRAY_BUFFER, id_nor );
   glNormalPointer(GL_FLOAT, 0, 0 );
   glBindBuffer( GL_ARRAY_BUFFER, 0 );      
   
   glEnableClientState( GL_VERTEX_ARRAY );   // habilitar tabla de vértices
   glEnableClientState(GL_COLOR_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);

   if(!ct.empty()){
      glEnableClientState( GL_TEXTURE_COORD_ARRAY);
      glBindBuffer( GL_ARRAY_BUFFER, id_tex);
      glTexCoordPointer(2, GL_FLOAT, 0, 0);
      glBindBuffer( GL_ARRAY_BUFFER, 0 ); 
  }

   // visualizar triángulos con glDrawElements (puntero a tabla == 0)
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_ind); // activar VBO de triángulos
   glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0 ) ;
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );     // desactivar VBO de triángulos
   // desactivar uso de array de vértices
   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState( GL_COLOR_ARRAY );
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState( GL_TEXTURE_COORD_ARRAY);
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
   glColorPointer(3, GL_FLOAT, 0, c_a.data());

   // Esto lo hago por si el objeto tiene un número de triángulos impar
   int mitad = floor(f_a.size()/2),
       mitad2 = ceil(f_a.size()/2);

   // Hecho para el redibujado
   setColor(1.0, 0.0, 0.0, 3);

   glDrawElements(GL_TRIANGLES, mitad*3, GL_UNSIGNED_INT, f_a.data());
   
   setColor(0.0, 1.0, 1.0, 3);

   // Dibujamos los elementos
   glDrawElements(GL_TRIANGLES, mitad2*3, GL_UNSIGNED_INT, f_a.data()[mitad]);

   // Desactivamos el uso de ambos arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}

void Malla3D::draw(int modoD, bool modoV[]){
   // Activación modo puntos
   if(modoV[0]){
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      draw(modoD, 1, modoV[3]);
   }

   // Activación modo líneas
   if(modoV[1]){
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      draw(modoD, 2, modoV[3]);
   }

   // Activación modo sólido
   if(modoV[3] || modoV[2] || modoV[4] ){
      if(t != nullptr && modoV[5]){
         glEnable( GL_TEXTURE_2D );
         t->activar();
      }
      
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      draw(modoD, 0, modoV[3]);
      glDisable( GL_TEXTURE_2D );
   }
}

void Malla3D::draw(int modoD, int modoV, bool ajedrez)
{
   if(m != nullptr)
      m->aplicar();
   if(nv.empty())
      calcular_normales();
   
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

   calcular_normales_caras();

   Tupla3f aux(0,0,0);
   nv.resize(v.size(), aux);

   for(int i=0; i<nc.size(); i++){
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
      Tupla3f a = v[f[i][1]] - v[f[i][0]];
      Tupla3f b = v[f[i][2]] - v[f[i][0]];
      
      Tupla3f m = a.cross(b);
      Tupla3f n = m.normalized();

      nc.push_back(n);
   }
}

void Malla3D::setTexturas(Textura tex){
   t = new Textura(tex);
}

void Malla3D::setMaterial(Material mat){
   m = new Material(mat);
}

void Malla3D::modificarCoordenadas(int x, int y, int z){
   coord = {x,y,z};
}