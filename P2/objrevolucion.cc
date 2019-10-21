#include "aux.h"
#include "objrevolucion.h"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   std::vector<Tupla3f> perfil;  

   _tapa_inf = tapa_inf;
   _tapa_sup = tapa_sup;
   N = num_instancias;

   ply::read_vertices(archivo ,perfil);
   M = perfil.size();

   if(perfil[0][1] < perfil[perfil.size()-1][1])
      darVuelta(perfil);


   crearMalla(perfil, num_instancias, 'y');

}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
    _tapa_inf = tapa_inf;
    _tapa_sup = tapa_sup;
    N = num_instancias;
    M = archivo.size();
    
    if(archivo[0][1] < archivo[M-1][1])
      darVuelta(archivo);

    crearMalla(archivo, num_instancias, 'y');
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, char eje) {
   const double PI = 3.14159265358979323846;
   float x, y, z;
   int a, b;
   bool sup, inf;
   std::vector<Tupla3f> tapas;

   detectarTapas(perfil_original, sup, inf, eje, tapas);
   int M = perfil_original.size();

   // Añadir vertices
   for(int i=0; i<num_instancias; i++){
      for(int j=0; j<M; j++){
         y = perfil_original[j][1];
         z = perfil_original[j][0]*sin(2*PI*i/num_instancias);
         x = perfil_original[j][0]*cos(2*PI*i/num_instancias);

         Tupla3f auxV(x,y,z);
         v.push_back(auxV);  
      }
   }

   // Añadir triángulos
   for(int i=0; i<num_instancias; i++){
      for(int j=0; j<M-1; j++){
         a = i*M + j;
         b = M*((i+1)%num_instancias) + j;

         Tupla3i auxF1(a,b,b+1), auxF2(a,b+1,a+1);
         f.push_back(auxF1);
         f.push_back(auxF2);
      }
   }

   anadirTapas(tapas, !sup, !inf, eje);
   
   // Añadir triángulos tapas
   // SUP
   if(_tapa_sup)
      for(int i=0; i<num_instancias; i++){
         Tupla3i aux(M*num_instancias, ((i+1)%num_instancias)*M,i*M);
         f.push_back(aux);
      }

   // INF
   if(_tapa_inf)
      for(int i=0; i<num_instancias; i++){
         Tupla3i aux(M*num_instancias+1, M*(i+1)-1, M*(((i+1)%num_instancias)+1)-1);
         f.push_back(aux);
      }
}

void ObjRevolucion::detectarTapas(std::vector<Tupla3f> & perfil_original, bool &sup, bool &inf, char eje, std::vector<Tupla3f> & tapas){
   sup = inf = false;

   switch(eje){
      case 'y':
         if(perfil_original[0][0] == 0 && perfil_original[0][2] == 0 ){
            sup = true;
            Tupla3f aux = perfil_original[0];
            perfil_original.erase(perfil_original.begin());
            tapas.push_back(aux);
         }
         else{
            Tupla3f aux(0,0,0);
            tapas.push_back(aux);
         }

         if(perfil_original[perfil_original.size()-1][0] == 0 && perfil_original[perfil_original.size()-1][2] == 0){
            inf = true;
            Tupla3f aux = perfil_original[perfil_original.size()-1];
            perfil_original.pop_back();
            tapas.push_back(aux);
         }
         else{
            Tupla3f aux(0,0,0);
            tapas.push_back(aux);
         }
         
         break;
   }
}

void ObjRevolucion::anadirTapas(std::vector<Tupla3f> & tapas, bool sup, bool inf, char eje){

   switch(eje){
      case 'y':
         if(!sup){
            v.push_back(tapas[0]);
         }
         else{
            Tupla3f aux(0,v[0][1],0);
            v.push_back(aux);
         }

         if(!inf){
            v.push_back(tapas[1]);
         }
         else{
            Tupla3f aux(0,v[v.size()-2][1],0);
            v.push_back(aux);
         }

         break;
   }
}

void ObjRevolucion::cambiarTapas(){

   if(_tapa_inf || _tapa_sup){

      if(_tapa_inf)
         for(int i=0; i<N; i++){
            f.pop_back();
         }

      if(_tapa_sup)
         for(int i=0; i<N; i++){
            f.pop_back();
         }  

      _tapa_sup = false;
      _tapa_inf = false;
   }
   else{

      if(!_tapa_sup)
         for(int i=0; i<N; i++){
            Tupla3i aux(M*N, ((i+1)%N)*M, i*M);
            f.push_back(aux);
         }

      if(!_tapa_inf)
         for(int i=0; i<N; i++){
            Tupla3i aux(M*N+1, M*(i+1)-1, M*(((i+1)%N)+1)-1);
            f.push_back(aux);
         }

      _tapa_sup = true;
      _tapa_inf = true;
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
