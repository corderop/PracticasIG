// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
  public:
    ObjRevolucion();
    ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
    ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
    void cambiarTapas();

protected:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, char eje);
    int N, M;

private:
    void detectarTapas(std::vector<Tupla3f> & perfil_original, bool &sup, bool &inf, char eje, std::vector<Tupla3f> & tapas);
    void anadirTapas(std::vector<Tupla3f> & tapas, bool sup, bool inf, char eje);
    void darVuelta(std::vector<Tupla3f> &perfil_original);

    bool _tapa_sup;
    bool _tapa_inf;
} ;

#endif
