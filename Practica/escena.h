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
#include "persona.h"
#include "cuadro.h"
#include "textura.h"
#include "camara.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO, SELAUTO, SELMANUAL, SELCAMARAS} menu;

class Escena
{

    private:

        // ***************
        // Variables
        // ***************

        // // Cámara provisional
        // GLfloat Observer_distance;
        // GLfloat Observer_angle_x;
        // GLfloat Observer_angle_y;

        // Ventana y transformación de la perspectiva
        // GLfloat Width, Height, Front_plane, Back_plane;
        GLfloat Width, Height;

        // Interacción con el ususario
        menu modoMenu=NADA;

        // Interacción con el ratón
        int pulsado = 0,    // 0 - ninguno, 1 - raton der, 2 - raton izq
            x_actual,       // Coordenada x para mover en primera persona para detectar movimiento
            y_actual,       // Coordenada x para mover en primera persona para detectar movimiento
            x_sel = -1,     // X cuando se pulsa en pantalla
            y_sel = -1,     // Y cuando se pulsa en pantalla
            obj_selec = 0;  // Objeto seleccionado. Hecho para poder seleccionar y deseleccionar un objeto.
        Tupla3f posicionObjeto = {0,0,0};

        // Forma de dibujado
        int objeto,         // Escena a dibujar cuando hay varias posibles
            modoD;          // Modo de dibujado: 1 - inmediato, 2 - diferido
        bool modoV[6];      // Modo de visualización: 0 - Puntos, 1 - lineas, 2 - solido, 3 - ajedrez, 4 - iluminacion, 5 - texturas
        bool tapas = false; // Indica si hay que cambiar de estado las tapas

        // Selecciones
        int luzS,           // Número de la luz seleccionada
            angulo,         // Ángulo a modificar
            camS;           // Camara activa
        bool luzActiva[8];  // Situación de cada luz

        // Animación
        bool animarAutomatico = false,              // Animación automática de los modelos de la escena
             animarAutomaticoLuces = false;         // Animación automática de las luces animadas
        float velocidadAnimacion = 1,               // Velocidad de la animación de modelos
              velocidadAnimacionLuz = 1,            // Velocidad de la animación de luces
              velocidadManual[7] = {1,1,1,1,1,1,1}; // Velocidad de cada grado de libertad independiente
        int manualActivado = 0;                     // Grado de libertad a animar de modo manual

        // Objetos de la escena
        Ejes ejes;                          // Ejes

        Cubo * cubo = nullptr ;             // Cubo
        Cuadro * cuadro = nullptr;          // Cuadro para aplicar textura
        Tetraedro * tetraedro= nullptr ;    // Tetraedro

        ObjPLY * ply = nullptr;             // PLY
        Cilindro * cilindro = nullptr;      // Cilindro
        Cono * cono = nullptr;              // Cono
        Esfera * esfera = nullptr;          // Esfera
        ObjRevolucion * peon1 = nullptr;    // PLY por revolución

        Persona *persona = nullptr;         // Modelo jerárquico

        Cilindro *p1;
        Cilindro *p2;

        Luz* luz[8];                        // Luces
        Camara* camaras[8];                 // Camaras

        // Objetos escena
        Cubo *muro1, *muro2;
        Cuadro *suelo;

        // ***************
        // Funciones
        // ***************

        // Hecho para ahorrar código cuando se quiere dibujar en diferentes modos simultaneamente
        void changeTapas();

        // Activar todas las luces de la escena
        void activarLuces();

        // Llamadas a los draw de los objetos así como las transformaciones correspondientes
        void dibujarObjetos();

        // Función auxiliar para el constructor
        void auxConstructor();

        // Creación de objetos
        void crearObjetos();

        // Modificación de los colores de todos los elementos de la escena
        void setColor();
        // Modificación de las texturas de todos los elementos de la escena
        void setTexturas();
        // Modificación de los materiales de todos los elementos de la escena
        void setMateriales();
        // Modificación de las coordenadas de texturas de todos los objetos de la escena
        void setCoordTexturas();

        // Dibuja los objetos con un solo color para poder seleccionarlos
        void dibujaSeleccion();
        // Según la selección declara que ha sido seleccionado
        void obtenerObjetoSeleccionado();

        // Transformación de cámara
        void change_projection();
        void change_observer();
        void clear_window();

    public:

        // Constructor principal
        Escena();

        // Ventana
        void inicializar( int UI_window_width, int UI_window_height );
        void redimensionar( int newWidth, int newHeight ) ;

        // Función de dibujado
        void dibujar() ;

        // Interacción con la escena
        bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
        void teclaEspecial( int Tecla1, int x, int y );

        // Muestra las opciones de interacción con el teclado por consola
        void opcionesInteraccion();

        // Animación del modelo de forma automática
        void animarModeloAutomaticamente();

        // Animación del modelo manual
        //   numero: número de grado de libertad
        //   suma: modificación del grado de libertad
        void animarModeloManual(int numero, float suma);

        // Animación automática de luces
        void animarLuces();

        // Interacción con el ratón
        void clickRaton( int boton, int estado, int x, int y);
        void ratonMovido( int x, int y);

        // Detección de objetos
        // Cambiar el at de la camara actual para que esta gire en torno a el
        void setPuntoRotacion(Malla3D *ptr);
};
#endif
