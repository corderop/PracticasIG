#include "aux.h"
#include "objrevolucion.h"
#include "esfera.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio ){

    std::vector<Tupla3f> esf;
    int j = 0;

    for(int i=0; i<=num_vert_perfil; i++){
        Tupla3f aux(cos( (PI/2) + i*(2*PI/2)/num_vert_perfil )*radio, sin( (PI/2) + i*(2*PI/2)/num_vert_perfil)*radio, 0);
        esf.push_back(aux);
        
        j++;
    }
    
    N = num_instancias_perf;
    M = esf.size();

    crearMalla(esf, num_instancias_perf, 'y');
}