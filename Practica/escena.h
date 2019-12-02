#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz.h"
#include "luzdireccional.h"
#include "luzposicional.h"
#include "tronco.h"
#include "pierna.h"
#include "persona.h"
#include "brazo.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO} menu;
class Escena
{

   private:

    /**
     * Hecho para ahorrar código cuando se quiere dibujar en diferentes modos simultaneamente
     */
    void changeTapas();

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();

   void clear_window();

   menu modoMenu=NADA;
   // Objetos de la escena
   Ejes ejes;
   // 0
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
   
   // 1
   Cilindro * cilindro = nullptr;
   Cono * cono = nullptr;
   Esfera * esfera = nullptr;

   // 2
   ObjRevolucion * peon1 = nullptr;
   ObjRevolucion * peon2 = nullptr;

   // 3
   Persona *persona = nullptr;
   Brazo *brazo = nullptr;

   // Luces
   Luz* luz[8];

   int objeto, modoD; // Objeto, modo de visualizacion, modo de dibujado
   bool modoV[5]; // 0 - Puntos, 1 - lineas, 2 - solido, 3 - ajedrez, 4 - iluminacion
   bool tapas = false; // Indica si hay que cambiar de estado las tapas
   int luzS, angulo; // Número de la luz seleccionada y angulo a modificar
   // Objeto: -1 nada, 0 cubo, 1 cilindro, esfera y cono, 2 escena
   // Modo visualizacion: 0 solido, 1 puntos, 2 lineas, 3 todos, 4 ajedrez
   // Modo dibujado: 1 Modo inmediato, 2 Modo diferido
   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
