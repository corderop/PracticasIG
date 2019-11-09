#include "aux.h"
#include "objrevolucion.h"
#include "cono.h"

Cono::Cono(const int num_instancias_perf, const float altura, const float radio ){
    std::vector<Tupla3f> con;
    
    Tupla3f aux1(0, altura, 0);
    con.push_back(aux1);
    Tupla3f aux2(radio, 0, 0);
    con.push_back(aux2);

    N = num_instancias_perf;
    M = con.size();

    crearMalla(con, num_instancias_perf, 'y');

}