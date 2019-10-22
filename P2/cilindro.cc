#include "aux.h"
#include "objrevolucion.h"
#include "cilindro.h"

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio ){

    std::vector<Tupla3f> cil;

    for(int i=num_instancias_perf-1; i>=0; i--){
       Tupla3f aux(radio, i*(altura/num_vert_perfil), 0);
       cil.push_back(aux);
    }

    N = num_instancias_perf;
    M = cil.size();

    // darVuelta();

    crearMalla(cil, num_instancias_perf, 'y');
}