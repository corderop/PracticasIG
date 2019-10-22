#include "aux.h"
#include "objrevolucion.h"
#include "cono.h"

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio ){

    // t_sup = false;
    // _tapa_sup = false;

    std::vector<Tupla3f> con;
    // _tapa_sup = fals
    int j = 0;

    for(int i=num_vert_perfil-1; i>=0; i--){
        Tupla3f aux(j*(radio/num_vert_perfil), i*(altura/num_vert_perfil), 0);
        con.push_back(aux);
        
        j++;
    }

    N = num_instancias_perf;
    M = con.size();

    crearMalla(con, num_instancias_perf, 'y');

}