#include "aux.h"
#include "objrevolucion.h"
#include "cilindro.h"

Cilindro::Cilindro(const int num_instancias_perf, const float altura, const float radio){

    std::vector<Tupla3f> cil;

    Tupla3f aux1(radio, altura, 0);
    cil.push_back(aux1);
    Tupla3f aux2(radio, 0, 0);
    cil.push_back(aux2);

    N = num_instancias_perf;
    M = cil.size();

    crearMalla(cil, num_instancias_perf, 'y');
}