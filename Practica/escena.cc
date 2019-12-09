#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    opcionesInteraccion();
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    objeto = -1;  // Ninguno seleccionado
    modoD = 1;    // Modo inmediato por defecto
    luzS = 0;
    angulo = -1;
    
    luz[0] = nullptr;
    luz[1] = nullptr;
    luz[2] = nullptr;
    luz[3] = nullptr;
    luz[4] = nullptr;
    luz[5] = nullptr;
    luz[6] = nullptr;
    luz[7] = nullptr;

    luzActiva[0] = true;
    luzActiva[1] = true;
    luzActiva[2] = true;
    luzActiva[3] = true;
    luzActiva[4] = true;
    luzActiva[5] = true;
    luzActiva[6] = true;
    luzActiva[7] = true;

    modoV[0] = false;
    modoV[1] = false;
    modoV[2] = true;    // Modo solido por defecto
    modoV[3] = false;
    modoV[4] = false;

    // Creamos una textura
    Textura tex("texturas/wall.jpg");

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

    Tupla4f col10(1.0, 0.829, 0.829, 0.922);
    Tupla4f col11(0.296648, 0.296648, 0.296648, 0.922);
    Tupla4f col12(0.25, 0.20725, 0.20725, 0.922);
    Material skin(col10, col11, col12, 11.264);

    // Cubo y tetraedro
    cubo = new Cubo(75);
    cubo->setColor(1.0, 0.0, 0.0, 0);
    cubo->setColor(0.0, 1.0, 0.0, 1);
    cubo->setColor(0.0, 0.0, 1.0, 2);
    cubo->setMaterial(ruby);
    cubo->setTexturas(tex);

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
    persona->setColorPiel(236.0/256, 188.0/256, 180.0/256);
    persona->setColorCamiseta(0,0,1.0);
    persona->setColorPantalones(1.0,0,0);
    persona->setColor(0.0, 0.0, 0.0, 2);
    persona->setColor(0.0, 1.0, 0.0, 1);
    persona->setMaterialPiel(skin);
    persona->setMaterialCamiseta(ruby);
    persona->setMaterialPantalones(esmeralda);

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

void Escena::changeTapas(){
   cilindro->cambiarTapas();
   cono->cambiarTapas();
   esfera->cambiarTapas();
   peon1->cambiarTapas();
   peon2->cambiarTapas();
   persona->cambiarTapas();
}

void Escena::activarLuces(){
   glEnable(GL_LIGHTING);
   // Activación de luces
   if(luzActiva[0] && luz[0]!=nullptr)  luz[0]->activar(); else glDisable(GL_LIGHT0);
   if(luzActiva[1] && luz[1]!=nullptr)  luz[1]->activar(); else glDisable(GL_LIGHT1);
   if(luzActiva[2] && luz[2]!=nullptr)  luz[2]->activar(); else glDisable(GL_LIGHT2);
   if(luzActiva[3] && luz[3]!=nullptr)  luz[3]->activar(); else glDisable(GL_LIGHT3);
   if(luzActiva[4] && luz[4]!=nullptr)  luz[4]->activar(); else glDisable(GL_LIGHT4);
   if(luzActiva[5] && luz[5]!=nullptr)  luz[5]->activar(); else glDisable(GL_LIGHT5);
   if(luzActiva[6] && luz[6]!=nullptr)  luz[6]->activar(); else glDisable(GL_LIGHT6);
   if(luzActiva[7] && luz[7]!=nullptr)  luz[7]->activar(); else glDisable(GL_LIGHT7);
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
   glPointSize(5.0);

   change_observer();
   ejes.draw();

   if(tapas){
      changeTapas();
      tapas=false;
   }

   if(texturas) glEnable( GL_TEXTURE_2D );
   else         glDisable( GL_TEXTURE_2D );

   if(modoV[4]){
      glShadeModel(GL_SMOOTH); // Si se comenta usa el modo FLAT
      activarLuces();
   }

   if(objeto == 0){
      // glPushMatrix();
      //    glTranslatef(+80.0,0.0,0.0);
         cubo->draw(modoD, modoV);
      // glPopMatrix();
      // glPushMatrix();
      //    glTranslatef(-80.0,0.0,0.0);
      //    tetraedro->draw(modoD, modoV);
      // glPopMatrix();
   }
   else if(objeto == 1){
      glPushMatrix();
         glTranslatef(+80.0,-40.0,0.0);
         cilindro->draw(modoD, modoV);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-80.0,-40.0,0.0);
         cono->draw(modoD, modoV);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0.0,0.0,-80.0);
         esfera->draw(modoD, modoV);
      glPopMatrix();
   }
   else if(objeto == 2){
      glPushMatrix();
         glScalef(10,10,10);
         persona->draw(modoD, modoV);
      glPopMatrix();
   }
}

void Escena::animarModeloAutomaticamente(){
   if(animarAutomatico)
      persona->andar(velocidadAnimacion);
   if(animarAutomaticoLuces)
      animarLuces();
}

void Escena::animarModeloManual(int numero, float suma){
   persona->moverGradoLibertad(numero, suma);
}

void Escena::animarLuces(){
   luz[luzS]->variarAnguloAlpha(velocidadAnimacionLuz);
}

/**
 * Opciones de interacción
 */
void Escena::opcionesInteraccion(){
   std::cout<<std::endl<<"----------------------------------"<<std::endl;
   std::cout<<"Q - Salir de cualquier modo o de la ejecución"<<std::endl;
   std::cout<<"D - Seleccionar modo dibujado"<<std::endl;
   std::cout<<"    1 - Modo inmediato"<<std::endl;
   std::cout<<"    2 - Modo diferido"<<std::endl;
   std::cout<<"O - Seleccionar modo objeto"<<std::endl;
   std::cout<<"    C - Cubo y tetraedro"<<std::endl;
   std::cout<<"    M - Cilindro, esfera y cono"<<std::endl;
   std::cout<<"    X - Modelo jerárquico"<<std::endl;
   std::cout<<"V - Seleccionar modo visualización"<<std::endl;
   std::cout<<"    P - Activar/desactivar modo puntos"<<std::endl;
   std::cout<<"    L - Activar/desactivar modo líneas"<<std::endl;
   std::cout<<"    S - Activar/desactivar modo sólido"<<std::endl;
   std::cout<<"    A - Activar/desactivar modo ajedrez"<<std::endl;
   std::cout<<"    I - Activar/desactivar modo iluminación"<<std::endl;
   std::cout<<"        0...7 - Activar/desactivar y seleccionar cada luz"<<std::endl;
   std::cout<<"        A - Activar variación ángulo alpha"<<std::endl;
   std::cout<<"        B - Activar variación ángulo beta"<<std::endl;
   std::cout<<"        > - Incrementa el ángulo"<<std::endl;
   std::cout<<"        < - Decrementa el ángulo"<<std::endl;
   std::cout<<"        P - Activar/desactivar animación automática de la luz"<<std::endl;
   std::cout<<"            + - Aumenta la velocidad de la animación"<<std::endl;
   std::cout<<"            - - Disminuye la velocidad de la animación"<<std::endl;
   std::cout<<"A - Activar/descativar animación automática de los modelos"<<std::endl;
   std::cout<<"    + - Aumenta la velocidad de la animación"<<std::endl;
   std::cout<<"    - - Disminuye la velocidad de la animación"<<std::endl;
   std::cout<<"M - Activar animación manual de los modelos"<<std::endl;
   std::cout<<"    0...n - Seleccionar el grado de libertad"<<std::endl;
   std::cout<<"    > - Aumentar velocidad manual"<<std::endl;
   std::cout<<"    < - Reducir velocidad manual"<<std::endl;
   std::cout<<"    + - Aumenta el grado de libertad"<<std::endl;
   std::cout<<"    - - Disminuye el grado de libertad"<<std::endl;
   std::cout<<"F - Activar/desactivar tapas"<<std::endl;
   std::cout<<"T - Activar/desactivar texturas"<<std::endl;
   std::cout<<std::endl<<"----------------------------------"<<std::endl;
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
      // SELECCIÓN DE MODO
      // -------------
      // Salir
      case 'Q' :
         if (modoMenu!=NADA){
            modoMenu=NADA;  
            cout<<"Saliendo del modo actual"<<endl;    
         }
         else {
            salir=true ;
         }
      break ;
      // Sel. modo dibujado
      case 'D' :
         if(modoMenu == NADA){
            modoMenu=SELDIBUJADO;
            cout<<"Modo dibujado seleccionado"<<endl;
         }
      break ;
      // Sel. objeto
      case 'O' :
         if(modoMenu == NADA){
            modoMenu=SELOBJETO; 
            cout<<"Modo objeto seleccionado"<<endl;   
         }
      break ;
      // Sel. modo visualización
      case 'V' :
         if(modoMenu == NADA){
            modoMenu=SELVISUALIZACION;
            cout<<"Modo visualización seleccionado"<<endl;   
         }
      break ;
      // Sel. modo animación auto
      case 'A' :
         if(modoMenu == NADA){
            if(!animarAutomatico){
               modoMenu=SELAUTO;
               cout<<"Animación automática activada"<<endl;   
               animarAutomatico = true;
            }
         }
         else if(modoMenu == SELAUTO){
            modoMenu = NADA;
            cout<<"Animación automática desactivada"<<endl;
            animarAutomatico = false;
         }
         else if(modoMenu == SELVISUALIZACION && !modoV[4]){
            if(modoV[3]){
               modoV[2] = true;
               modoV[3] = false;
               cout<<"Modo ajedrez desactivado"<<endl;
            }
            else{
               modoV[0] = false;
               modoV[1] = false;
               modoV[2] = false;
               modoV[3] = true;
               modoV[4] = false;
               cout<<"Modo ajedrez activado"<<endl;
            }
         }
         else if(modoMenu == SELVISUALIZACION && modoV[4]){
            angulo = 0;
            cout<<"Ángulo alpha seleccionado"<<endl;
         }
      break ;
      // Sel. modo animación manual
      // Mostrar cilindro, esfera y cono
      case 'M' :
         if(modoMenu == NADA){
            modoMenu=SELMANUAL;
            cout<<"Animación manual activada"<<endl;   
            animarAutomatico = false;
         }
         else if(modoMenu == SELOBJETO){
            objeto = 1;
            cout<<"Mostrando cilindro, esfera y cono"<<endl;
         }
      break ;
      // CAMBIAR TAPAS
      case 'F':
         if(modoMenu == NADA){
            tapas = true;
            cout<<"Alternando tapas"<<endl;
         }
      break;
      case 'T':
         if(modoMenu == NADA){
            texturas = !texturas;
            cout<<"Texturas ";
            cout<< ( (texturas) ? "activadas" : "desactivadas" ) <<endl;
         }
      break;

      // -------------
      // Subopciones
      // -------------
      // Selección de objeto
      // Cubo y tetraedro
      case 'C' :
         if(modoMenu == SELOBJETO){
            objeto = 0;
            cout<<"Mostrando cubo y tetraedro"<<endl;
         }
      break;
      // Modelo jerárquico
      case 'X' :
         if(modoMenu == SELOBJETO){
            objeto = 2;
            cout<<"Mostrando modelo jerárquico"<<endl;
         }
      break;

      // Modo visualización
      // Modo puntos
      case 'P' :
         if(modoMenu == SELVISUALIZACION){
            if(modoV[0]){
               modoV[0] = false;
               cout<<"Modo puntos desactivado"<<endl;
            }
            else if(modoV[4]){
               if(luz[luzS]->esDireccional()){
                  cout<<"Animación automática de la luz: ";
                  animarAutomaticoLuces = !animarAutomaticoLuces;
                  cout<< ( (animarAutomaticoLuces) ? "activada" : "desactivada" )<<endl;
               }
            }
            else{
               modoV[0] = true;
               modoV[3] = false;
               modoV[4] = false;
               cout<<"Modo puntos activado"<<endl;
            }
         }
      break;
      // Modo líneas
      case 'L' :
         if(modoMenu == SELVISUALIZACION){
            if(modoV[1]){
               modoV[1] = false;
               cout<<"Modo líneas desactivado"<<endl;
            }
            else{
               modoV[1] = true;
               modoV[3] = false;
               modoV[4] = false;
               cout<<"Modo líneas activado"<<endl;
            }
         }
      break;
      // Modo sólido
      case 'S' :
         if(modoMenu == SELVISUALIZACION){
            if(modoV[2]){
               modoV[2] = false;
               cout<<"Modo sólido desactivado"<<endl;
            }
            else{
               modoV[2] = true;
               modoV[3] = false;
               modoV[4] = false;
               cout<<"Modo sólido activado"<<endl;
            }
         }
      break;
      // Modo iluminación
      case 'I' :
         if(modoMenu == SELVISUALIZACION){
            modoV[0] = false;
            modoV[1] = false;
            modoV[2] = false;
            modoV[3] = false;
            modoV[4] = true;
            cout<<"Modo iluminación activado"<<endl;
         }
      break;  

      // Números
      case '0' :
         if(modoMenu == SELVISUALIZACION && modoV[4]){
            luzS = 0;
            cout<<"Luz " << luzS << " seleccionada y ";
            luzActiva[luzS] = !luzActiva[luzS];
            cout<< ( (luzActiva[luzS]) ? "activada" : "desactivada" )<<endl;
         }
         else if(modoMenu == SELMANUAL){
            manualActivado = 0;
            cout<<"Grado de libertad seleccionado: " << manualActivado <<endl;
         }
      break;
      case '1' :
         // Modo inmediato
         if(modoMenu == SELDIBUJADO){
            modoD = 1;
            cout<<"Modo inmediato seleccionado"<<endl;
         }
         else if(modoMenu == SELVISUALIZACION && modoV[4]){
            luzS = 1;
            cout<<"Luz " << luzS << " seleccionada y ";
            luzActiva[luzS] = !luzActiva[luzS];
            cout<< ( (luzActiva[luzS]) ? "activada" : "desactivada" )<<endl;
         }
         else if(modoMenu == SELMANUAL){
            manualActivado = 1;
            cout<<"Grado de libertad seleccionado: " << manualActivado <<endl;
         }
      break;
      case '2' :
         // Modo diferido
         if(modoMenu == SELDIBUJADO){
            modoD = 2;
            cout<<"Modo diferido seleccionado"<<endl;
         }
         else if(modoMenu == SELVISUALIZACION && modoV[4]){
            luzS = 2;
            cout<<"Luz " << luzS << " seleccionada y ";
            luzActiva[luzS] = !luzActiva[luzS];
            cout<< ( (luzActiva[luzS]) ? "activada" : "desactivada" )<<endl;
         }
         else if(modoMenu == SELMANUAL){
            manualActivado = 2;
            cout<<"Grado de libertad seleccionado: " << manualActivado <<endl;
         }
      break;
      case '3' :
         if(modoMenu == SELVISUALIZACION && modoV[4]){
            luzS = 3;
            cout<<"Luz " << luzS << " seleccionada y ";
            luzActiva[luzS] = !luzActiva[luzS];
            cout<< ( (luzActiva[luzS]) ? "activada" : "desactivada" )<<endl;
         }
         else if(modoMenu == SELMANUAL){
            manualActivado = 3;
            cout<<"Grado de libertad seleccionado: " << manualActivado <<endl;
         }
      break;
      case '4' :
         if(modoMenu == SELVISUALIZACION && modoV[4]){
            luzS = 4;
            cout<<"Luz " << luzS << " seleccionada y ";
            luzActiva[luzS] = !luzActiva[luzS];
            cout<< ( (luzActiva[luzS]) ? "activada" : "desactivada" )<<endl;
         }
         else if(modoMenu == SELMANUAL){
            manualActivado = 4;
            cout<<"Grado de libertad seleccionado: " << manualActivado <<endl;
         }
      break;
      case '5' :
         if(modoMenu == SELVISUALIZACION && modoV[4]){
            luzS = 5;
            cout<<"Luz " << luzS << " seleccionada y ";
            luzActiva[luzS] = !luzActiva[luzS];
            cout<< ( (luzActiva[luzS]) ? "activada" : "desactivada" )<<endl;
         }
         else if(modoMenu == SELMANUAL){
            manualActivado = 5;
            cout<<"Grado de libertad seleccionado: " << manualActivado <<endl;
         }
      break;
      case '6' :
         if(modoMenu == SELVISUALIZACION && modoV[4]){
            luzS = 6;
            cout<<"Luz " << luzS << " seleccionada y ";
            luzActiva[luzS] = !luzActiva[luzS];
            cout<< ( (luzActiva[luzS]) ? "activada" : "desactivada" )<<endl;
         }
      break;
      case '7' :
         if(modoMenu == SELVISUALIZACION && modoV[4]){
            luzS = 7;
            cout<<"Luz " << luzS << " seleccionada y ";
            luzActiva[luzS] = !luzActiva[luzS];
            cout<< ( (luzActiva[luzS]) ? "activada" : "desactivada" )<<endl;
         }
      break;

      // Ángulo beta
      case 'B' :
         if(modoV[4]){
            angulo = 1;
            cout<<"Ángulo beta seleccionado"<<endl;
         }
      break;

      // Incremento del angulo manual
      case '>' :
         if(modoV[4] && angulo!=-1 && luzS!=-1 && luz[luzS] != nullptr){
            if(luz[luzS]->esDireccional()){
               if(angulo == 0)   luz[luzS]->variarAnguloAlpha(1);
               else              luz[luzS]->variarAnguloBeta(1);
               cout<<"Incremento del ángulo ";
               cout<< ( (angulo == 0) ? "alpha" : "beta" );
               cout<<" de la luz "<<luzS<<endl;
            }
         }
         else if( modoMenu == SELMANUAL){
            cout<<"Velocidad manual aumentada"<<endl;
            velocidadManual++;
         }
      break;
      // Decrementar angulo
      case '<' :
         if(modoV[4] && angulo!=-1 && luzS!=-1 && luz[luzS] != nullptr){
            if(luz[luzS]->esDireccional()){
               if(angulo == 0)   luz[luzS]->variarAnguloAlpha(-1);
               else              luz[luzS]->variarAnguloBeta(-1);
               cout<<"Decremento del ángulo ";
               cout<< ( (angulo == 0) ? "alpha" : "beta" );
               cout<<" de la luz "<<luzS<<endl;
            }
         }
         else if( modoMenu == SELMANUAL){
            cout<<"Velocidad manual reducida"<<endl;
            velocidadManual--;
         }
      break;

      // Controles de animación
      case '+' :
         if(modoMenu == SELAUTO){
            if(animarAutomatico)
                  velocidadAnimacion++;
         }
         else if(modoMenu == SELMANUAL){
            animarModeloManual(manualActivado, velocidadManual);
         }
         else if(modoMenu == SELVISUALIZACION && modoV[4] && animarAutomaticoLuces){
            velocidadAnimacionLuz++;
         }
      break;
      case '-' :
         if(modoMenu == SELAUTO){
            if(animarAutomatico)
               if(velocidadAnimacion>1)
                  velocidadAnimacion--;
         }
         else if(modoMenu == SELMANUAL){
            animarModeloManual(manualActivado, velocidadManual);
         }
         else if(modoMenu == SELVISUALIZACION && modoV[4] && animarAutomaticoLuces){
            velocidadAnimacionLuz--;
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
