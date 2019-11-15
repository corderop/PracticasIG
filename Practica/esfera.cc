#include "aux.h"
#include "objrevolucion.h"
#include "esfera.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio ){

    q_tapa_inf = q_tapa_sup = false;
    std::vector<Tupla3f> esf;

    Tupla3f aux1(0, radio, 0);
    esf.push_back(aux1);

    for(int i=1; i<=num_vert_perfil-1; i++){
        double a = (i*M_PI)/num_vert_perfil;
        Tupla3f aux2( radio*sin(a), cos(a)*radio ,0);
        esf.push_back(aux2);
    }

    Tupla3f aux3(0, -radio, 0);
    esf.push_back(aux3);
    
    N = num_instancias_perf;
    M = esf.size();

    crearMalla(esf, num_instancias_perf, 'y');
}