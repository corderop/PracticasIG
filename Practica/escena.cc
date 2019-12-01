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

    objeto = -1;  // Ninguno seleccionado
    modoD = 1;    // Modo inmediato por defecto
    luzS = -1;
    angulo = -1;
    
    luz[0] = nullptr;
    luz[1] = nullptr;
    luz[2] = nullptr;
    luz[3] = nullptr;
    luz[4] = nullptr;
    luz[5] = nullptr;
    luz[6] = nullptr;
    luz[7] = nullptr;

    modoV[0] = false;
    modoV[1] = false;
    modoV[2] = true;    // Modo solido por defecto
    modoV[3] = false;
    modoV[4] = false;

    // Material de prueba
    Tupla4f col4(0.61424, 0.04136, 0.04136, 1.0);
    Tupla4f col5(0.727811, 0.626959, 0.626959, 1.0);
    Tupla4f col6(0.1745, 0.01175, 0.01175, 1.0);
    Material ruby(col4, col5, col6, 0.6*128);

    Tupla4f col1(0.07568, 0.61424, 0.07568, 1.0);
    Tupla4f col2(0.633, 0.727811, 0.633, 1.0);
    Tupla4f col3(0.0215, 0.1745, 0.0215, 1.0);
    Material esmeralda(col1, col2, col3, 0.6*128);

    Tupla4f col7(0.75164, 0.60648, 0.22648, 1.0);
    Tupla4f col8(0.628281, 0.555802, 0.366065, 1.0);
    Tupla4f col9(0.24725, 0.1995, 0.0745, 1.0);
    Material gold(col7, col8, col9, 0.4*128);

    // Cubo y tetraedro
    cubo = new Cubo(75);
    cubo->setColor(1.0, 0.0, 0.0, 0);
    cubo->setColor(0.0, 1.0, 0.0, 1);
    cubo->setColor(0.0, 0.0, 1.0, 2);
    cubo->setMaterial(ruby);

    tetraedro = new Tetraedro();
    tetraedro->setColor(0.0, 0.0, 1.0, 0);
    tetraedro->setColor(1.0, 0.0, 0.0, 1);
    tetraedro->setColor(0.0, 0.0, 0.0, 2);
    tetraedro->setMaterial(esmeralda);
    
    // Cilindro, cono y esfera
    cilindro = new Cilindro(40,80,30);
    cilindro->setColor(1.0, 0.0, 0.0, 0);
    cilindro->setColor(0.0, 1.0, 0.0, 1);
    cilindro->setColor(0.0, 0.0, 0.0, 2);
    cilindro->setMaterial(esmeralda);

    cono = new Cono(40, 80, 30);
    cono->setColor(1.0, 0.0, 0.0, 0);
    cono->setColor(0.0, 1.0, 0.0, 1);
    cono->setColor(0.0, 0.0, 0.0, 2);
    cono->setMaterial(ruby);

    esfera = new Esfera(40, 40, 30);
    esfera->setColor(1.0, 0.0, 0.0, 0);
    esfera->setColor(0.0, 1.0, 0.0, 1);
    esfera->setColor(0.0, 0.0, 0.0, 2);
    esfera->setMaterial(gold);

    // P3
    peon1 = new ObjRevolucion("plys/peon.ply", 40, true, true);
    peon1->setColor(1.0, 1.0, 1.0, 0);
    peon1->setColor(0.0, 1.0, 0.0, 1);
    peon1->setColor(0.0, 0.0, 1.0, 2);
    peon1->setMaterial(esmeralda);

    peon2 = new ObjRevolucion("plys/peon.ply", 40, true, true);
    peon2->setColor(1.0, 1.0, 1.0, 0);
    peon2->setColor(0.0, 1.0, 0.0, 1);
    peon2->setColor(0.0, 0.0, 1.0, 2);
    peon2->setMaterial(ruby);

    // P4
    persona = new Persona();

    // Luces
    Tupla3f pos(0, 0, 0);
    Tupla4f colL(1.0, 1.0, 1.0, 1.0);
    luz[0] = new LuzPosicional(pos, GL_LIGHT0, colL, colL, colL);
    luz[1] = new LuzDireccional({0,0}, GL_LIGHT1, colL, colL, colL);
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

void Escena::selDibujado(Malla3D * objeto){
   
   bool ajedrez = modoV[3];

   // Activación modo puntos
   if(modoV[0]){
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      objeto->draw(modoD, 1, ajedrez);
   }

   // Activación modo líneas
   if(modoV[1]){
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      objeto->draw(modoD, 2, ajedrez);
   }

   // Activación modo sólido
   if(modoV[3] || modoV[2] || modoV[4] ){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      objeto->draw(modoD, 0, ajedrez);
   }
}

void Escena::changeTapas(){
   cilindro->cambiarTapas();
   cono->cambiarTapas();
   esfera->cambiarTapas();
   peon1->cambiarTapas();
   peon2->cambiarTapas();
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
   glEnable(GL_NORMALIZE);
   glDisable(GL_LIGHTING);
   glShadeModel(GL_FLAT);

   change_observer();
   ejes.draw();

   if(tapas){
      changeTapas();
      tapas=false;
   }

   if(modoV[4]){
      glEnable(GL_LIGHTING);
      glShadeModel(GL_SMOOTH); // Si se comenta usa el modo FLAT
      // Activación de luces
      luz[0]->activar();
      luz[1]->activar();
   }

   if(objeto == 0){
      glPushMatrix();
         glTranslatef(+80.0,0.0,0.0);
         selDibujado(cubo);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-80.0,0.0,0.0);
         selDibujado(tetraedro);
      glPopMatrix();
   }
   else if(objeto == 1){
      glPushMatrix();
         glTranslatef(+80.0,-40.0,0.0);
         selDibujado(cilindro);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-80.0,-40.0,0.0);
         selDibujado(cono);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0.0,0.0,-80.0);
         selDibujado(esfera);
      glPopMatrix();
   }
   else if(objeto == 2){
      // glPushMatrix();
      //    glTranslatef(-80.0,0.0,0.0);
      //    glScalef(30.0,30.0,30.0);
      //    selDibujado(peon2);
      // glPopMatrix();
      // glPushMatrix();
      //    glTranslatef(+80.0,0.0,0.0);
      //    glScalef(30.0,30.0,30.0);
      //    selDibujado(peon1);
      // glPopMatrix();
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      persona->draw(modoD, 0, false);
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
      // -------------
      // Teclas principales

      // Salir
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
      // Sel. objeto
      case 'O' :
         modoMenu=SELOBJETO; 
         break ;
      // Sel. modo visualización
      case 'V' :
         modoMenu=SELVISUALIZACION;
      break ;
      // Sel. modo dibujado
      case 'D' :
         modoMenu=SELDIBUJADO;
      break ;

      // -------------
      // Subopciones

      // Sel. objeto
      // Cubo
      case 'C' :
         if(modoMenu == SELOBJETO){
            objeto = 0;
         }
      break;
      // Cilindro, cono, esfera
      case 'M' :
         if(modoMenu == SELOBJETO){
            objeto = 1;
         }
      break;
      // Escena
      case 'X' :
         if(modoMenu == SELOBJETO){
            objeto = 2;
         }
      break;

      // Cambiar tapas
      case 'F':
         tapas = true;
      break;

      // Modo de dibujado y selección luz
      case '0' :
         if(modoV[4]){
            luzS = 0;
         }
      break;
      case '1' :
         // Modo inmediato
         if(modoMenu == SELDIBUJADO){
            modoD = 1;
         }
         else if(modoV[4]){
            luzS = 1;
         }
      break;
      case '2' :
         // Modo diferido
         if(modoMenu == SELDIBUJADO){
            modoD = 2;
         }
         else if(modoV[4]){
            luzS = 2;
         }
      case '3' :
         if(modoV[4]){
            luzS = 3;
         }
      break;
      case '4' :
         if(modoV[4]){
            luzS = 4;
         }
      break;
      case '5' :
         if(modoV[4]){
            luzS = 5;
         }
      break;
      case '6' :
         if(modoV[4]){
            luzS = 6;
         }
      break;
      case '7' :
         if(modoV[4]){
            luzS = 7;
         }
      break;

      // Modo visualización
      // Modo puntos
      case 'P' :
         if(modoMenu == SELVISUALIZACION){
            if(modoV[0]){
               modoV[0] = false;
            }
            else{
               modoV[0] = true;
               modoV[3] = false;
               modoV[4] = false;
            }
         }
      break;
      // Modo líneas
      case 'L' :
         if(modoMenu == SELVISUALIZACION){
            if(modoV[1]){
               modoV[1] = false;
            }
            else{
               modoV[1] = true;
               modoV[3] = false;
               modoV[4] = false;
            }
         }
      break;
      // Modo solido
      case 'S' :
      if(modoMenu == SELVISUALIZACION){
         if(modoV[2]){
            modoV[2] = false;
         }
         else{
            modoV[2] = true;
            modoV[3] = false;
            modoV[4] = false;
         }
      }
      break;
      // Modo ajedrez y selecion del angulo alpha
      case 'A' :
         if(modoMenu == SELVISUALIZACION && !modoV[4]){
            modoV[0] = false;
            modoV[1] = false;
            modoV[2] = false;
            modoV[3] = true;
            modoV[4] = false;
         }
         else if(modoV[4]){
            angulo = 0;
         }
      break;
      // Modo visualización
      case 'I' :
         if(modoMenu == SELVISUALIZACION){
            modoV[0] = false;
            modoV[1] = false;
            modoV[2] = false;
            modoV[3] = false;
            modoV[4] = true;
         }
      break;  
      // Selección Beta 
      case 'B' :
         if(modoV[4]){
            angulo = 1;
         }
      break;
      // Incrementar angulo
      case '>' :
         if(modoV[4] && angulo!=-1 && luzS!=-1 && luz[luzS] != nullptr){
            if(luz[luzS]->esDireccional()){
               if(angulo == 0)   luz[luzS]->variarAnguloAlpha(1);
               else              luz[luzS]->variarAnguloBeta(1);
            }
         }
      break;
      // Decrementar angulo
      case '<' :
         if(modoV[4] && angulo!=-1 && luzS!=-1 && luz[luzS] != nullptr){
            if(luz[luzS]->esDireccional()){
               if(angulo == 0)   luz[luzS]->variarAnguloAlpha(-1);
               else              luz[luzS]->variarAnguloBeta(-1);
            }
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
