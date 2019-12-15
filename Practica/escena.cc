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

    objeto = 0;  // Ninguno seleccionado
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
    modoV[5] = false;

    // Creamos una textura
    Textura tex("texturas/wall.jpg");
    Textura tex2("texturas/text-madera.jpg");

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

    Tupla4f col13(0.5,0.5,0.5,1.0);
    Tupla4f col14(0.7,0.7,0.7,1.0);
    Tupla4f col15(0.05,0.05,0.05,1.0);
    Material white(col13, col14, col15, 10.0);

    // Cubo y tetraedro
    cubo = new Cubo(40);
    cubo->setColor(1.0, 1.0, 1.0, 0);
    cubo->setColor(0.0, 1.0, 0.0, 1);
    cubo->setColor(0.0, 0.0, 1.0, 2);
    cubo->setMaterial(white);
    cubo->setTexturas(tex);
    cubo->calcular_texturas();

    cuadro = new Cuadro(40);
    cuadro->setColor(1.0, 1.0, 1.0, 0);
    cuadro->setColor(0.0, 1.0, 0.0, 1);
    cuadro->setColor(0.0, 0.0, 1.0, 2);
    cuadro->setMaterial(white);
    cuadro->setTexturas(tex2);
    cuadro->calcular_texturas();

    tetraedro = new Tetraedro();
    tetraedro->setColor(0.0, 0.0, 1.0, 0);
    tetraedro->setColor(1.0, 0.0, 0.0, 1);
    tetraedro->setColor(0.0, 0.0, 0.0, 2);
    tetraedro->setMaterial(esmeralda);
    
    // Cilindro, cono y esfera
    cilindro = new Cilindro(40,40,20);
    cilindro->setColor(1.0, 0.0, 0.0, 0);
    cilindro->setColor(0.0, 1.0, 0.0, 1);
    cilindro->setColor(0.0, 0.0, 0.0, 2);
    cilindro->setMaterial(esmeralda);

    cono = new Cono(40, 40, 20);
    cono->setColor(1.0, 0.0, 0.0, 0);
    cono->setColor(0.0, 1.0, 0.0, 1);
    cono->setColor(0.0, 0.0, 0.0, 2);
    cono->setMaterial(ruby);

    esfera = new Esfera(40, 40, 20);
    esfera->setColor(0.0, 0.0, 0.0, 0);
    esfera->setColor(1.0, 0.0, 0.0, 1);
    esfera->setColor(0.0, 1.0, 0.0, 2);
    esfera->setMaterial(gold);

    // P3
    peon1 = new ObjRevolucion("plys/peon.ply", 40, true, true);
    peon1->setColor(1.0, 0.0, 1.0, 0);
    peon1->setColor(0.0, 1.0, 0.0, 1);
    peon1->setColor(0.0, 0.0, 1.0, 2);
    peon1->setMaterial(esmeralda);

    ply = new ObjPLY("plys/ant.ply");
    ply->setColor(0.0, 0.0, 1.0, 0);
    ply->setColor(0.0, 1.0, 0.0, 1);
    ply->setColor(0.0, 0.0, 1.0, 2);
    ply->setMaterial(ruby);

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

    // Camaras
    camaras[0] = new Camara(1, {0,0,600}, {0,1,0}, {0,0,0}, 50, 50);
    camaras[1] = new Camara(0, {0,0,600}, {0,1,0}, {0,0,0}, 300, 300);
    camaras[2] = new Camara(1, {600,0,0}, {0,1,0}, {0,0,0}, 500, 500);
    camaras[3] = new Camara(1, {600,600,+600}, {0,1,0}, {0,0,0}, 3000, 3000);
    camS = 0;
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

   if(x_sel!=-1 && y_sel!=-1)
      dibujaSeleccion();

   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glEnable(GL_CULL_FACE);
   glEnable(GL_NORMALIZE);
   glEnable(GL_DITHER);
   glDisable(GL_LIGHTING);
   glShadeModel(GL_FLAT);

   change_projection(1);
   change_observer();

   ejes.draw();

   if(tapas){
      changeTapas();
      tapas=false;
   }

   if(modoV[4]){
      glShadeModel(GL_SMOOTH); // Si se comenta usa el modo FLAT
      activarLuces();
   }

   if(objeto == 0){
      dibujarEscena();
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

void Escena::dibujarEscena(){
   // Cara de alante
   glPushMatrix();
      // Fila cono, cilindro, esfera
      glPushMatrix();
         glTranslatef(0.0,80.0,0.0);
         glPushMatrix();
            glTranslatef(-80.0, 0.0, 0.0);
            cuadro->modificarCoordenadas(-80,80,0);
            cuadro->draw(modoD, modoV);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(80.0, -20.0, 0.0);
            cilindro->modificarCoordenadas(80,60,0);
            cilindro->draw(modoD, modoV);
         glPopMatrix();
         esfera->modificarCoordenadas(0,80,0);
         esfera->draw(modoD, modoV);
      glPopMatrix();
      
      // Modelo en el medio
      glPushMatrix();
         glScalef(3,3,3);
         persona->modificarCoordenadas(0,0,0);
         persona->draw(modoD, modoV);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(0.0,-80.0,0.0);
         glPushMatrix();
            glTranslatef(-80.0, 0.0, 0.0);
            glScalef(20.0,20.0,20.0);
            peon1->modificarCoordenadas(-80,-80,0);
            peon1->draw(modoD, modoV);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(80.0,0.0,0.0);
            glScalef(2.5,2.5,2.5);
            ply->modificarCoordenadas(80,-80,0);
            ply->draw(modoD, modoV);
         glPopMatrix();
         cubo->modificarCoordenadas(0,-80,0);
         cubo->draw(modoD, modoV);
      glPopMatrix();

   glPopMatrix();
}

void Escena::setPuntoRotacion(Malla3D *ptr){
   camaras[camS]->setAt(ptr->getCoordenadas());
}

void Escena::dibujaSeleccion(){
   glDisable(GL_DITHER); // Luz y texturas desactivadas por defecto
   glDisable(GL_LIGHTING);

   int modoD_c = modoD;
   bool modoV_c[6] = {modoV[0],modoV[1],modoV[2],modoV[3],modoV[4],modoV[5]};

   modoD = 1; // modo inmediato
   modoV[0] = false;
   modoV[1] = false;
   modoV[2] = true;    // Modo solido
   modoV[3] = false;
   modoV[4] = false;
   modoV[5] = false;

       cubo->setColor(0.1, 0.0, 0.0, 0);
     cuadro->setColor(0.2, 0.0, 0.0, 0);
   cilindro->setColor(0.3, 0.0, 0.0, 0);
     esfera->setColor(0.4, 0.0, 0.0, 0);
      peon1->setColor(0.5, 0.0, 0.0, 0);
        ply->setColor(0.6, 0.0, 0.0, 0);
    persona->setColor(0.7, 0.0, 0.0, 0);

   dibujarEscena();

   GLfloat r[3];
   GLint   viewport[4];
   glGetIntegerv(GL_VIEWPORT,viewport);

   glReadPixels(x_sel, viewport[3]-y_sel, 1, 1, GL_RGB, GL_FLOAT, (void *)r);

   // Redondeados para evitar errores con float
   if(round(r[0]*10)/10 == 0.1){
      if(obj_selec != 1){
         obj_selec = 1;
         setPuntoRotacion(cubo);
      }
      else{
         obj_selec = 0;
         camaras[camS]->setAt({0,0,0});
      }
   }
   else if(round(r[0]*10)/10 == 0.2){
      if(obj_selec != 2){
         obj_selec = 2;
         setPuntoRotacion(cuadro);
      }
      else{
         obj_selec = 0;
         camaras[camS]->setAt({0,0,0});
      }
   }
   else if(round(r[0]*10)/10 == 0.3){
      if(obj_selec != 3){
         obj_selec = 3;
         setPuntoRotacion(cilindro);
      }
      else{
         obj_selec = 0;
         camaras[camS]->setAt({0,0,0});
      }
   }
   else if(round(r[0]*10)/10 == 0.4){
      if(obj_selec != 4){
         obj_selec = 4;
         setPuntoRotacion(esfera);
      }
      else{
         obj_selec = 0;
         camaras[camS]->setAt({0,0,0});
      }
   }
   else if(round(r[0]*10)/10 == 0.5){
      if(obj_selec != 5){
         obj_selec = 5;
         setPuntoRotacion(peon1);
      }
      else{
         obj_selec = 0;
         camaras[camS]->setAt({0,0,0});
      }
   }
   else if(round(r[0]*10)/10 == 0.6){
      if(obj_selec != 6){
         obj_selec = 6;
         setPuntoRotacion(ply);
      }
      else{
         obj_selec = 0;
         camaras[camS]->setAt({0,0,0});
      }
   }
   else if(round(r[0]*10)/10 == 0.7){
      if(obj_selec != 7){
         obj_selec = 7;
         camaras[camS]->setAt(persona->getCoordenadas());
      }
      else{
         obj_selec = 0;
         camaras[camS]->setAt({0,0,0});
      }
   }

   // Restauramos los valores para el dibujado normal
   modoD = modoD_c;
   modoV[0] = modoV_c[0];
   modoV[1] = modoV_c[1];
   modoV[2] = modoV_c[2];    // Modo solido
   modoV[3] = modoV_c[3];
   modoV[4] = modoV_c[4];
   modoV[5] = modoV_c[5];

   setColor();
   x_sel = y_sel = -1;
}

void Escena::setColor(){
   cubo->setColor(1.0, 1.0, 1.0, 0);
   cubo->setColor(0.0, 1.0, 0.0, 1);
   cubo->setColor(0.0, 0.0, 1.0, 2);

   cuadro->setColor(1.0, 1.0, 1.0, 0);
   cuadro->setColor(0.0, 1.0, 0.0, 1);
   cuadro->setColor(0.0, 0.0, 1.0, 2);

   tetraedro->setColor(0.0, 0.0, 1.0, 0);
   tetraedro->setColor(1.0, 0.0, 0.0, 1);
   tetraedro->setColor(0.0, 0.0, 0.0, 2);

   cilindro->setColor(1.0, 0.0, 0.0, 0);
   cilindro->setColor(0.0, 1.0, 0.0, 1);
   cilindro->setColor(0.0, 0.0, 0.0, 2);

   cono->setColor(1.0, 0.0, 0.0, 0);
   cono->setColor(0.0, 1.0, 0.0, 1);
   cono->setColor(0.0, 0.0, 0.0, 2);

   esfera->setColor(0.0, 0.0, 0.0, 0);
   esfera->setColor(1.0, 0.0, 0.0, 1);
   esfera->setColor(0.0, 1.0, 0.0, 2);

   peon1->setColor(1.0, 0.0, 1.0, 0);
   peon1->setColor(0.0, 1.0, 0.0, 1);
   peon1->setColor(0.0, 0.0, 1.0, 2);

   ply->setColor(0.0, 0.0, 1.0, 0);
   ply->setColor(0.0, 1.0, 0.0, 1);
   ply->setColor(0.0, 0.0, 1.0, 2);
   
   persona->setColorPiel(236.0/256, 188.0/256, 180.0/256);
   persona->setColorCamiseta(0,0,1.0);
   persona->setColorPantalones(1.0,0,0);
   persona->setColor(0.0, 0.0, 0.0, 2);
   persona->setColor(0.0, 1.0, 0.0, 1);
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
   if(luz[luzS]->esDireccional())
      luz[luzS]->variarAnguloAlpha(velocidadAnimacionLuz);
   else{
      luz[luzS]->variarPosicion(velocidadAnimacionLuz, 0, 0);
   }
}

// INTERACCIÓN CON EL RATÓN
void Escena::clickRaton( int boton, int estado, int x, int y){
   // Se pulsa el boton derecho
   if( boton == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN){
      pulsado = 1;
      x_actual = x;
      y_actual = y;
   }
   else if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
      x_sel = x;
      y_sel = y;
   }
   else if(boton == 3 && estado == GLUT_UP){
      camaras[camS]->zoom(1);
   }
   else if(boton == 4 && estado == GLUT_UP){
      camaras[camS]->zoom(-1);
   }
   else{
      pulsado = 0;
   }
}

void Escena::ratonMovido( int x, int y){
   switch (pulsado)
   {
   case 1:
      camaras[camS]->rotarXFirstPerson((x-x_actual)*0.1);
      camaras[camS]->rotarYFirstPerson((y-y_actual)*0.1);
      x_actual = x;
      y_actual = y;
      break;
   
   case 2:
      
      break;
   }
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
   std::cout<<"    H - Cubo y tetraedro"<<std::endl;
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
   std::cout<<"C - Activar selección de camaras"<<std::endl;
   std::cout<<"    0...7 - Seleccionar el grado de libertad"<<std::endl;
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
      case 'Z' :
         setPuntoRotacion(peon1);
      break;
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
               modoV[5] = false;
               cout<<"Modo ajedrez activado"<<endl;
            }
         }
         else if(modoMenu == SELVISUALIZACION && modoV[4]){
            angulo = 0;
            cout<<"Ángulo alpha seleccionado"<<endl;
         }
      break ;
      case 'C':
         if(modoMenu == NADA){
            modoMenu = SELCAMARAS;
            cout<<"Modo selección de cámara activado"<<endl;
         }
      break;
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
            modoV[5] = !modoV[5];
            cout<<"Texturas ";
            cout<< ( (modoV[5]) ? "activadas" : "desactivadas" ) <<endl;
         }
      break;

      // -------------
      // Subopciones
      // -------------
      // Selección de objeto
      // Cubo y tetraedro
      case 'H' :
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
               cout<<"Animación automática de la luz: ";
               animarAutomaticoLuces = !animarAutomaticoLuces;
               cout<< ( (animarAutomaticoLuces) ? "activada" : "desactivada" )<<endl;
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
         else if(modoMenu == SELCAMARAS){
            camS = 0;
            change_observer();
            change_projection(1);
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
         else if(modoMenu == SELCAMARAS){
            camS = 1;
            change_observer();
            change_projection(1);
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
         else if(modoMenu == SELCAMARAS){
            camS = 2;
            change_observer();
            change_projection(1);
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
         else if(modoMenu == SELCAMARAS){
            camS = 3;
            change_observer();
            change_projection(1);
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
         else if(modoMenu == SELCAMARAS){
            camS = 4;
            change_observer();
            change_projection(1);
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
         else if(modoMenu == SELCAMARAS){
            camS = 5;
            change_observer();
            change_projection(1);
         }
      break;
      case '6' :
         if(modoMenu == SELVISUALIZACION && modoV[4]){
            luzS = 6;
            cout<<"Luz " << luzS << " seleccionada y ";
            luzActiva[luzS] = !luzActiva[luzS];
            cout<< ( (luzActiva[luzS]) ? "activada" : "desactivada" )<<endl;
         }
         else if(modoMenu == SELCAMARAS){
            camS = 6;
            change_observer();
            change_projection(1);
         }
      break;
      case '7' :
         if(modoMenu == SELVISUALIZACION && modoV[4]){
            luzS = 7;
            cout<<"Luz " << luzS << " seleccionada y ";
            luzActiva[luzS] = !luzActiva[luzS];
            cout<< ( (luzActiva[luzS]) ? "activada" : "desactivada" )<<endl;
         }
         else if(modoMenu == SELCAMARAS){
            camS = 7;
            change_observer();
            change_projection(1);
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
            velocidadManual[manualActivado]++;
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
            velocidadManual[manualActivado]--;
         }
      break;

      // Controles de animación
      case '+' :
         if(modoMenu == SELAUTO){
            if(animarAutomatico)
                  velocidadAnimacion++;
         }
         else if(modoMenu == SELMANUAL){
            animarModeloManual(manualActivado, velocidadManual[manualActivado]);
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
            animarModeloManual(manualActivado, -velocidadManual[manualActivado]);
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
         if(camS == 7) Observer_angle_y-- ;
         else camaras[camS]->rotarXExaminar(-1);
         break;
	   case GLUT_KEY_RIGHT:
         if(camS == 7) Observer_angle_y++ ;
         else camaras[camS]->rotarXExaminar(+1);
         break;
	   case GLUT_KEY_UP:
         if(camS == 7) Observer_angle_x-- ;
         else camaras[camS]->rotarYExaminar(+1);
         break;
	   case GLUT_KEY_DOWN:
         if(camS == 7) Observer_angle_x++ ;
         else camaras[camS]->rotarYExaminar(-1);
         break;
	   case GLUT_KEY_PAGE_UP:
         if(camS == 7) Observer_distance *=1.2 ;
         else camaras[camS]->zoom(1);
         break;
	   case GLUT_KEY_PAGE_DOWN:
         if(camS == 7) Observer_distance /= 1.2 ;
         else camaras[camS]->zoom(-1);
         break;
	}

	// std::cout << Observer_distance << std::endl;
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
   if(camS == 7)  glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
   else if(camaras[camS]!=nullptr)  
      camaras[camS]->setProyeccion();
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
   if(camS == 7) {
      glTranslatef( 0.0, 0.0, -Observer_distance );
      glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
      glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
   }
   if(camaras[camS]!=nullptr)
      camaras[camS]->setObserver();
}
