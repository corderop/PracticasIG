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

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO} menu;
class Escena
{

   private:

    /**
     * Hecho para ahorrar código cuando se quiere dibujar en diferentes modos simultaneamente
     */
    void selDibujado(Malla3D * objeto);

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
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
   ObjPLY * ply_no1 = nullptr;
   ObjRevolucion * ply_rev = nullptr;
   Cilindro * cilindro = nullptr;
   Cono * cono = nullptr;
   Esfera * esfera = nullptr;

   int objeto, modoD; // Objeto, modo de visualizacion, modo de dibujado
   bool modoV[5]; // 0 - Puntos, 1 - lineas, 2 - solido, 3 - ajedrez, 4 - iluminacion
   bool tapas = false;
   // Objeto: -1 nada, 0 cubo, 1 tetraedro, 2 ply cargado, 3 ply revolución
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
