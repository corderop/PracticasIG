

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

    // Cubo y tetraedro
    cubo = new Cubo(75);
    tetraedro = new Tetraedro();

    // PLY sin revolución
    ply_no1 = new ObjPLY("plys/ant.ply");
    ply_no1->setColor(1.0, 0.0, 0.0, 0);
    ply_no1->setColor(0.0, 1.0, 0.0, 1);
    ply_no1->setColor(0.0, 0.0, 0.0, 2);

    // PLY con revolución
    ply_rev = new ObjRevolucion("plys/peon.ply", 40, true, false);
    ply_rev->setColor(1.0, 0.0, 0.0, 0);
    ply_rev->setColor(0.0, 1.0, 0.0, 1);
    ply_rev->setColor(0.0, 0.0, 0.0, 2);

    // Cilindro, cono y esfera
    cilindro = new Cilindro(40,40,100,40);
    cilindro->setColor(1.0, 0.0, 0.0, 0);
    cilindro->setColor(0.0, 1.0, 0.0, 1);
    cilindro->setColor(0.0, 0.0, 0.0, 2);

    cono = new Cono(40, 40, 100, 40);
    cono->setColor(1.0, 0.0, 0.0, 0);
    cono->setColor(0.0, 1.0, 0.0, 1);
    cono->setColor(0.0, 0.0, 0.0, 2);

    esfera = new Esfera(40, 40, 50);
    esfera->setColor(1.0, 0.0, 0.0, 0);
    esfera->setColor(0.0, 1.0, 0.0, 1);
    esfera->setColor(0.0, 0.0, 0.0, 2);

    objeto = -1;  // Ninguno seleccionado
    modoV = 0;    // Modo solido por defecto
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

void Escena::selDibujado(Malla3D * objeto){
   
   bool ajedrez = (modoV == 4);

   switch (modoV){
      case 0: 
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         objeto->draw(modoD, modoV, ajedrez);
         break;
      case 1: 
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         objeto->draw(modoD, 0, ajedrez);
         glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
         objeto->draw(modoD, modoV, ajedrez);
         break;
      case 2: 
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         objeto->draw(modoD, 0, ajedrez);
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         objeto->draw(modoD, modoV, ajedrez);
         break;
      case 3:
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         objeto->draw(modoD, 0, ajedrez);
         glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
         objeto->draw(modoD, 1, ajedrez);
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         objeto->draw(modoD, 2, ajedrez);
         break;
      case 4:
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         objeto->draw(modoD, 0, ajedrez);
         ajedrez = true;
      break;
   }

}

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
   glEnable(GL_CULL_FACE);

	change_observer();
    ejes.draw();

    bool ajedrez = (modoV == 3);

    if(objeto == 0){
      selDibujado(cubo);
    }
    else if(objeto == 1)
      selDibujado(tetraedro);
    else if(objeto == 2){
      glPushMatrix();
         glScalef(5.0,5.0,5.0);
         selDibujado(ply_no1);
      glPopMatrix();
    }
    else if(objeto == 3){
       if(tapas){
         ply_rev->cambiarTapas();
         ply_rev->crearAjedrez();
         tapas=false;
       }
       glPushMatrix();
         glScalef(50.0,50.0,50.0);
         selDibujado(ply_rev);
       glPopMatrix();
    }
    else if(objeto == 4){
       if(tapas){
         cilindro->cambiarTapas();
         cono->cambiarTapas();
         esfera->cambiarTapas();
         cilindro->crearAjedrez();
         cono->crearAjedrez();
         esfera->crearAjedrez();
         tapas=false;
       }
       glPushMatrix();
         glTranslatef(0.0,-50.0,0.0);
         glTranslatef(-120.0,0.0,0.0);
         selDibujado(cilindro);
         glTranslatef(240.0,0.0,0.0);
         selDibujado(cono);
         glTranslatef(0.0,+50.0,0.0);
         glTranslatef(-120.0,0.0,0.0);
         selDibujado(esfera);
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
         else if(modoMenu == SELVISUALIZACION){
            modoV = 3;
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
            modoV = 1;
         }
         else if(modoMenu == SELOBJETO){
            objeto = 2;
         }
         break;
       case 'L' :
         if(modoMenu == SELVISUALIZACION){
            modoV = 2;
         }
         break;
       case 'S' :
         if(modoMenu == SELVISUALIZACION){
            modoV = 0;
         }
         break;
       case 'A' :
         if(modoMenu == SELVISUALIZACION){
            modoV = 4;
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