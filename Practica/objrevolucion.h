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
    void darVuelta(std::vector<Tupla3f> &perfil_original);

    // Funciones de dibujado sobrecargadas para poder
    // gestionar el cambio de tapas desde el dibujado
    // sin modificar el vector
    void draw_ModoInmediato(int modo) override;
    void draw_ModoDiferido(int modo) override;
    void draw_ModoAjedrez() override;

protected:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, char eje);
    int N, M;

    // Si están activas las tapas
    bool _tapa_sup;
    bool _tapa_inf;
    // Si se quieren las tapas
    bool q_tapa_sup;
    bool q_tapa_inf;

    GLuint id_tapas[2]; // Sup y inf

private:
    void detectarTapas(std::vector<Tupla3f> & perfil_original, char eje, std::vector<Tupla3f> & tapas);
    void anadirTapas(std::vector<Tupla3f> & tapas, char eje);   

    // Funciones auxiliares de contructores
    void const_tapas(bool inf, bool sup);
    void const_malla(int n, std::vector<Tupla3f> archivo);
} ;

#endif
