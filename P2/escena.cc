

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    // .......completar: ...
    // .....
    cubo = new Cubo(75);
    tetraedro = new Tetraedro();
    ply_no1 = new ObjPLY("plys/ant.ply");
    ply_no2 = new ObjPLY("plys/ant.ply");
    ply_rev = new ObjRevolucion("plys/peon.ply", 40, true, true);
    
    std::vector<Tupla3f> cil;

    for(int i=0; i<40; i++){
       Tupla3f aux(20, i, 0);
       cil.push_back(aux);
    }

    cilindro = new Cilindro(40,40,100,40);

    objeto = -1;  // Ninguno seleccionado
    modoV = 2;    // Modo solido por defecto
    modoD = 1;    // Modo inmediato por defecto
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
   glEnable(GL_CULL_FACE);

	change_observer();
    ejes.draw();

    bool ajedrez = (modoV == 3);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    switch (modoV){
       case 0: 
         glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
         break;
       case 1: 
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         break;
       case 2: 
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         break;
       case 3: 
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         ajedrez = true;
         break;
    }

    if(objeto == 0)
      cubo->draw(modoD, ajedrez);
    else if(objeto == 1)
      tetraedro->draw(modoD, ajedrez);
    else if(objeto == 2){
      glPushMatrix();
         glScalef(5.0,5.0,5.0);
         glTranslatef(-20.0,0.0,0.0);
         ply_no1->setColor(1.0,0,0);
         ply_no1->draw(modoD, ajedrez);
         glTranslatef(+40.0,0.0,0.0);
         ply_no2->setColor(0.0,0.0,0.0);
         ply_no2->draw(modoD, ajedrez);
      glPopMatrix();
    }
    else if(objeto == 3){
       if(tapas){
         ply_rev->cambiarTapas();
         ply_rev->crearAjedrez();
         tapas=false;
       }
       glPushMatrix();
         ply_rev->setColor(1.0,0,0);
         glScalef(50.0,50.0,50.0);
         ply_rev->draw(modoD, ajedrez);
       glPopMatrix();
       
    }
    else if(objeto == 4){
       if(tapas){
         cilindro->cambiarTapas();
         cilindro->crearAjedrez();
         tapas=false;
       }
       glPushMatrix();
         cilindro->setColor(1.0,0,0);
         glTranslatef(0.0,-50.0,0.0);
         cilindro->draw(modoD, ajedrez);
       glPopMatrix();
    }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO; 
         break ;
        case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         break ;
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         break ;
         // COMPLETAR con los diferentes opciones de teclado
       case 'C' :
         if(modoMenu == SELOBJETO){
            objeto = 0;
         }
         break;
       case 'T' :
         if(modoMenu == SELOBJETO){
            objeto = 1;
         }
         break;
       case 'R' :
         if(modoMenu == SELOBJETO){
            objeto = 3;
         }
         break;
       case 'X' :
         // Cilindro
         if(modoMenu == SELOBJETO){
            objeto = 4;
         }
         break;
       case 'F':
         // Alternar tapas
         if(objeto==3 || objeto==4){
            tapas = true;
         }
         break;
       case 'P' :
         if(modoMenu == SELVISUALIZACION){
            modoV = 0;
         }
         else if(modoMenu == SELOBJETO){
            objeto = 2;
         }
         break;
       case 'L' :
         if(modoMenu == SELVISUALIZACION){
            modoV = 1;
         }
         break;
       case 'S' :
         if(modoMenu == SELVISUALIZACION){
            modoV = 2;
         }
         break;
       case 'A' :
         if(modoMenu == SELVISUALIZACION){
            modoV = 3;
         }
         break;
       case '1' :
         if(modoMenu == SELDIBUJADO){
            modoD = 1;
         }
         break;
       case '2' :
         if(modoMenu == SELDIBUJADO){
            modoD = 2;
         }
         break;
            
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
