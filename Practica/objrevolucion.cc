#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {

   _tapa_inf = _tapa_sup = true;
   q_tapa_inf = q_tapa_sup = true;

}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   std::vector<Tupla3f> perfil;

   q_tapa_inf = _tapa_inf = tapa_inf;
   q_tapa_sup = _tapa_sup = tapa_sup;

   N = num_instancias;

   ply::read_vertices(archivo ,perfil);
   M = perfil.size();

   if(perfil[0][1] < perfil[perfil.size()-1][1])
      darVuelta(perfil);

   crearMalla(perfil, N, 'y');
   crearAjedrez();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
    
   q_tapa_inf = _tapa_inf = tapa_inf;
   q_tapa_sup = _tapa_sup = tapa_sup;

   N = num_instancias;
   M = archivo.size();
   
   if(archivo[0][1] < archivo[M-1][1])
      darVuelta(archivo);

   crearMalla(archivo, N, 'y');
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, char eje) {
   float x, y, z;
   int a, b;
   std::vector<Tupla3f> tapas;

   detectarTapas(perfil_original, eje, tapas);
   int M = perfil_original.size();

   // Añadir vertices
   for(int i=0; i<N; i++){
      for(int j=0; j<M; j++){
         y = perfil_original[j][1];
         z = perfil_original[j][0]*sin(2*PI*i/N);
         x = perfil_original[j][0]*cos(2*PI*i/N);

         Tupla3f auxV(x,y,z);
         v.push_back(auxV);  
      }
   }

   // Añadir triángulos
   for(int i=0; i<N; i++){
      for(int j=0; j<M-1; j++){
         a = i*M + j;
         b = M*((i+1)%N) + j;

         Tupla3i auxF1(a,b,b+1), auxF2(a,b+1,a+1);
         f.push_back(auxF1);
         f.push_back(auxF2);
      }
   }

   anadirTapas(tapas, eje);
}

void ObjRevolucion::detectarTapas(std::vector<Tupla3f> & perfil_original, char eje, std::vector<Tupla3f> & tapas){

   switch(eje){
      case 'y':
         if(perfil_original[0][0] == 0 && perfil_original[0][2] == 0 ){
            Tupla3f aux = perfil_original[0];
            perfil_original.erase(perfil_original.begin());
            tapas.push_back(aux);
            M--;
         }
         else{
            Tupla3f aux(0,perfil_original[0][1],0);
            tapas.push_back(aux);
         }

         if(perfil_original[perfil_original.size()-1][0] == 0 && perfil_original[perfil_original.size()-1][2] == 0){
            Tupla3f aux = perfil_original[perfil_original.size()-1];
            perfil_original.pop_back();
            tapas.push_back(aux);
            M--;
         }
         else{
            Tupla3f aux(0,perfil_original[perfil_original.size()-1][1],0);
            tapas.push_back(aux);
         }
         
         break;
   }
}

void ObjRevolucion::anadirTapas(std::vector<Tupla3f> & tapas, char eje){

   switch(eje){
      case 'y':
         v.push_back(tapas.back());
         v.push_back(tapas.front());

         break;
   }

   // Añadir triángulos tapas (única vez que lo hace)
   // INF
   for(int i=0; i<N; i++){
      Tupla3i aux(M*N, M*(i+1)-1, M*(((i+1)%N)+1)-1);
      f.push_back(aux);
   }
   
   // SUP
   for(int i=0; i<N; i++){
      Tupla3i aux(M*N+1, ((i+1)%N)*M,i*M);
      f.push_back(aux);
   }
}

void ObjRevolucion::cambiarTapas(){

   if(q_tapa_inf && _tapa_inf){
      _tapa_inf = false;
   }
   else if(q_tapa_inf){
      _tapa_inf = true;
   }

   if(q_tapa_sup && _tapa_sup){
      _tapa_sup = false;
   }
   else if(q_tapa_sup){
      _tapa_sup = true;
   }
}


void ObjRevolucion::darVuelta(std::vector<Tupla3f> &perfil_original){
   std::vector<Tupla3f> aux = perfil_original;
   int tam = perfil_original.size();
   perfil_original.clear();

   for(int i=0; i<tam; i++){
      perfil_original.push_back(aux.back());
      aux.pop_back();
   }
}

void ObjRevolucion::draw_ModoInmediato(int modo){
  // Activamos el uso de un array de vértices
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, v.data());
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, c[modo].data());
  glEnableClientState( GL_NORMAL_ARRAY );
  glNormalPointer( GL_FLOAT, 0, nv.data() );

  // Elemento sin tapas
  glDrawElements(GL_TRIANGLES, (f.size()-2*N)*3, GL_UNSIGNED_INT, f.data());

  if(_tapa_inf)
     glDrawElements(GL_TRIANGLES, N*3, GL_UNSIGNED_INT, f.data()[f.size()-2*N]);

  if(_tapa_sup)
     glDrawElements(GL_TRIANGLES, N*3, GL_UNSIGNED_INT, f.data()[f.size()-N]);
     

  // Desactivamos el uso de ambos arrays
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
}

// void ObjRevolucion::draw_ModoDiferido(int modo)
// {
//    if(id_ver == 0)
//       id_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*sizeof(float)*3, v.data());
   
//    if(id_ind == 0)
//       id_ind = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*sizeof(int)*3, f.data());
   
//    if(id_col[modo] == 0)
//       id_col[modo] = CrearVBO(GL_ARRAY_BUFFER, c[modo].size()*sizeof(float)*3, c[modo].data());

//    // especificar localización y formato de la tabla de vértices, habilitar tabla
//    glBindBuffer( GL_ARRAY_BUFFER, id_ver );  // activar VBO de vértices
//    glVertexPointer( 3, GL_FLOAT, 0, 0 );     // especifica formato y offset (=0)
//    glBindBuffer( GL_ARRAY_BUFFER, 0 );       // desactivar VBO de vértices.
   
//    glBindBuffer( GL_ARRAY_BUFFER, id_col[modo] ); 
//    glColorPointer(3, GL_FLOAT, 0, 0);
//    glBindBuffer( GL_ARRAY_BUFFER, 0 );
   
//    glEnableClientState( GL_VERTEX_ARRAY );   // habilitar tabla de vértices
//    glEnableClientState(GL_COLOR_ARRAY);

//    // visualizar triángulos con glDrawElements (puntero a tabla == 0)
//    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_ind); // activar VBO de triángulos
//    glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0 ) ;
//    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );     // desactivar VBO de triángulos
//    // desactivar uso de array de vértices
//    glDisableClientState( GL_VERTEX_ARRAY );
//    glDisableClientState( GL_COLOR_ARRAY );
// }
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjRevolucion::draw_ModoAjedrez(){

   if(f_a.empty())
      crearAjedrez();

   // Para que no se vean sombras
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, v.data());
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_FLOAT, 0, c[0].data());

   // Esto lo hago por si el objeto tiene un número de triángulos impar
   int N2_1 = floor(N/2),
       N2_2 = ceil(N/2),
       mitad = floor(f_a.size()/2),
       mitad2 = ceil(f_a.size()/2);
       

   // Elemento sin tapas
   glDrawElements(GL_TRIANGLES, (mitad-N2_1*2)*3, GL_UNSIGNED_INT, f_a.data());

   if(_tapa_inf)
      glDrawElements(GL_TRIANGLES, N2_1*3, GL_UNSIGNED_INT, f_a.data()[mitad-2*N2_1]);

   if(_tapa_sup)
      glDrawElements(GL_TRIANGLES, N2_1*3, GL_UNSIGNED_INT, f_a.data()[mitad-N2_1]);
   
   setColor(0.0, 1.0, 1.0, 0);

   // Elemento sin tapas
   glDrawElements(GL_TRIANGLES, (mitad2-N2_2*2)*3, GL_UNSIGNED_INT, f_a.data()[mitad]);

   if(_tapa_inf)
      glDrawElements(GL_TRIANGLES, N2_2*3, GL_UNSIGNED_INT, f_a.data()[mitad + mitad2-2*N2_1]);

   if(_tapa_sup)
      glDrawElements(GL_TRIANGLES, N2_2*3, GL_UNSIGNED_INT, f_a.data()[mitad + mitad-N2_1]);

   // Hecho para el redibujado
   setColor(1.0, 0.0, 0.0, 0);

   // Desactivamos el uso de ambos arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}