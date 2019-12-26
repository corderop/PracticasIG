#include "aux.h"
#include "escena.h"
#include "malla.h"

// ***************************************
// INICIALIZACIÓN Y FUNCIONES AUXILIARES
// ***************************************

Escena::Escena()
{
	auxConstructor();

	crearObjetos();

	// Luces
    luz[0] = new LuzPosicional({0,0,0}, GL_LIGHT0, {1.0,1.0,1.0,0.5}, {1.0,1.0,1.0,0.5}, {1.0,1.0,1.0,0.5});
    luz[1] = new LuzDireccional({0,0}, GL_LIGHT1, {1.0,1.0,1.0,0.5}, {1.0,1.0,1.0,0.5}, {1.0,1.0,1.0,0.5});

    // Camaras
    camaras[0] = new Camara(1, {0,0,600}, {0,1,0}, {0,0,0}, 50, 50);
    camaras[1] = new Camara(0, {0,0,600}, {0,1,0}, {0,0,0}, 300, 300);
    camaras[2] = new Camara(1, {600,0,0}, {0,1,0}, {0,0,0}, 50, 50);
    camaras[3] = new Camara(1, {2000,2000,+2000}, {0,1,0}, {0,0,0}, 50, 50);

    cuadro->modificarCoordenadas(-80,80,0);
    cilindro->modificarCoordenadas(80,60,0);
    esfera->modificarCoordenadas(0,80,0);
    peon1->modificarCoordenadas(-80,-80,0);
    ply->modificarCoordenadas(80,-80,0);
    cubo->modificarCoordenadas(0,-80,0);

	setColor();
	setTexturas();
    setMateriales();
	setCoordTexturas();
}

void Escena::auxConstructor(){
	opcionesInteraccion();

    ejes.changeAxisSize( 5000 );

    objeto = 0;  // Ninguno seleccionado
    modoD = 1;    // Modo inmediato por defecto
    luzS = 0;
    angulo = -1;
	camS = 3;
    
    luz[0] = nullptr;
    luz[1] = nullptr;
    luz[2] = nullptr;
    luz[3] = nullptr;
    luz[4] = nullptr;
    luz[5] = nullptr;
    luz[6] = nullptr;
    luz[7] = nullptr;

	// Luces activadas por defecto
    luzActiva[0] = true;
    luzActiva[1] = true;
    luzActiva[2] = true;
    luzActiva[3] = true;
    luzActiva[4] = true;
    luzActiva[5] = true;
    luzActiva[6] = true;
    luzActiva[7] = true;

	// Modo sólido activado por defecto
    modoV[0] = false;
    modoV[1] = false;
    modoV[2] = true;    // Modo solido por defecto
    modoV[3] = false;
    modoV[4] = false;
    modoV[5] = false;
}

void Escena::crearObjetos(){
	// Creación de objetos no escena
    cubo = new Cubo(40);
    cuadro = new Cuadro(40);
    tetraedro = new Tetraedro();
    cilindro = new Cilindro(40,40,20);
    cono = new Cono(40, 40, 20);
    esfera = new Esfera(40, 40, 20);
    peon1 = new ObjRevolucion("plys/peon.ply", 40, true, true);
    ply = new ObjPLY("plys/ant.ply");
    persona = new Persona();

	// OBJETOS ESCENA
	suelo = new Cuadro(40);
	// Muros
    muro1 = new Cubo(40);
    muro2 = new Cubo(40);
    // Aceras
    acera1 = new Cubo(40);
    acera2 = new Cubo(40);
    acera3 = new Cubo(40);
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
    persona->setColorSombrero(1.0,0.0,0.0);
    persona->setColor(0.0, 0.0, 0.0, 2);
    persona->setColor(0.0, 1.0, 0.0, 1);

	// Escena
	suelo->setColor(100.0/255, 100.0/255, 100.0/255, 0);
	muro1->setColor(255.0/255, 0.0, 0.0, 0);
	muro2->setColor(255.0/255, 0.0, 0.0, 0);
    acera1->setColor(150.0/255, 150.0/255, 100.0/255, 0);
    acera2->setColor(150.0/255, 150.0/255, 100.0/255, 0);
    acera3->setColor(150.0/255, 150.0/255, 100.0/255, 0);
}

void Escena::setMateriales(){
	// Creación de materiales
	Tupla4f col1(0.61424, 0.04136, 0.04136, 1.0);
    Tupla4f col2(0.727811, 0.626959, 0.626959, 1.0);
    Tupla4f col3(0.1745, 0.01175, 0.01175, 1.0);
    Material ruby(col1, col2, col3, 0.6*128);

    col1 = Tupla4f(0.07568, 0.61424, 0.07568, 1.0);
    col2 = Tupla4f(0.633, 0.727811, 0.633, 1.0);
    col3 = Tupla4f(0.0215, 0.1745, 0.0215, 1.0);
    Material esmeralda(col1, col2, col3, 0.6*128);

    col1 = Tupla4f(0.75164, 0.60648, 0.22648, 1.0);
    col2 = Tupla4f(0.628281, 0.555802, 0.366065, 1.0);
    col3 = Tupla4f(0.24725, 0.1995, 0.0745, 1.0);
    Material gold(col1, col2, col3, 0.4*128);

    col1 = Tupla4f(1.0, 0.829, 0.829, 0.922);
    col2 = Tupla4f(0.296648, 0.296648, 0.296648, 0.922);
    col3 = Tupla4f(0.25, 0.20725, 0.20725, 0.922);
    Material skin(col1, col2, col3, 11.264);

    col1 = Tupla4f(0.5,0.5,0.5,1.0);
    col2 = Tupla4f(0.7,0.7,0.7,1.0);
    col3 = Tupla4f(0.05,0.05,0.05,1.0);
    Material white(col1, col2, col3, 10.0);

	// Asignación de materiales
	cubo->setMaterial(white);
	cuadro->setMaterial(white);
	tetraedro->setMaterial(esmeralda);
	cilindro->setMaterial(esmeralda);
	cono->setMaterial(ruby);
	esfera->setMaterial(gold);
	peon1->setMaterial(esmeralda);
	ply->setMaterial(ruby);
	persona->setMaterialPiel(skin);
    persona->setMaterialCamiseta(ruby);
    persona->setMaterialPantalones(esmeralda);
    persona->setMaterialSombrero(ruby);
}

void Escena::setTexturas(){
	// Creamos una textura
	Textura tex("texturas/wall.jpg");
	Textura tex2("texturas/text-madera.jpg");

	cubo->setTexturas(tex);
	cubo->calcular_texturas();
	cuadro->setTexturas(tex2);
	cuadro->calcular_texturas();

	// ESCENA
	Textura tex3("texturas/road.jpg");
    suelo->setTexturas(tex3);

	muro1->setTexturas(tex);
	muro2->setTexturas(tex);
}

void Escena::setCoordTexturas(){
	std::vector<Tupla2f> aux;

	// suelo
    aux.resize(4);
    aux[0] = {0,0};
    aux[1] = {5,0};
    aux[2] = {5,2};
    aux[3] = {0,2};
    suelo->setCoordenadasTexturas(aux);

	// muro1
	aux.clear();
	aux.resize(16);
	// Cara de la derecha
	aux[3] = {0,0};
    aux[2] = {0,1};
    aux[6] = {10,1};
    aux[7] = {10,0};
	// Cara de la izquierda
	aux[0] = {0,0};
    aux[1] = {0,1};
    aux[5] = {10,1};
    aux[4] = {10,0};
	// Cara de enfrente
	aux[9]  = {1,0};
    aux[10] = {1,0.4};
	// Cara de atrás
	// aux[15] = {0,0};
	aux[14] = {11,0.4};
	aux[13] = {11,0};
	// aux[12] = {0.4,0};
	// Cara de arriba
	aux[8] = {0,0};
	aux[11] = {0,0.4};
	aux[15] = {10,0.4};
	aux[12] = {10,0};
    muro1->setCoordenadasTexturas(aux);
	muro2->setCoordenadasTexturas(aux);
}


void Escena::setPuntoRotacion(Malla3D *ptr){
   camaras[camS]->setAt(ptr->getCoordenadas());
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

	change_projection();
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

	if(x_sel!=-1 && y_sel!=-1)
		dibujaSeleccion();

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiamos de nuevo

	setColor();

	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DITHER);
	glDisable(GL_LIGHTING);	// Se desactiva para mostrar los ejes en sólido
	glShadeModel(GL_FLAT);

	// Por si se actualiza la cámara
	change_projection();
	change_observer(); 

	// Se dibujan los ejes
	ejes.draw();

	// Cambia las tapas si se solicita
	if(tapas){
		changeTapas();
		tapas=false;
	}

	// Activa el modo iluminación
	if(modoV[4]){
		glShadeModel(GL_SMOOTH); // Si se comenta usa el modo FLAT
		activarLuces();			 // Enciende las luces activas
	}

	// Se dibujan los objetos
	dibujarObjetos();
}

void Escena::dibujarObjetos(){
   	if(objeto == 0){
		// Cara de alante
      glPushMatrix();
         // Fila cono, cilindro, esfera
         glPushMatrix();
            glTranslatef(0.0,80.0,0.0);
            glPushMatrix();
               glTranslatef(-80.0, 0.0, 0.0);
               cuadro->draw(modoD, modoV);
            glPopMatrix();
            glPushMatrix();
               glTranslatef(80.0, -20.0, 0.0);        
               cilindro->draw(modoD, modoV);
            glPopMatrix(); 
            esfera->draw(modoD, modoV);
         glPopMatrix();
         
         // Modelo en el medio
         glPushMatrix();
            glScalef(3,3,3);
            persona->draw(modoD, modoV);
         glPopMatrix();

         glPushMatrix();
            glTranslatef(0.0,-80.0,0.0);
            glPushMatrix();
               glTranslatef(-80.0, 0.0, 0.0);
               glScalef(20.0,20.0,20.0);
               peon1->draw(modoD, modoV);
            glPopMatrix();
            glPushMatrix();
               glTranslatef(80.0,0.0,0.0);
               glScalef(2.5,2.5,2.5);
               ply->draw(modoD, modoV);
            glPopMatrix();
            cubo->draw(modoD, modoV);
         glPopMatrix();
      glPopMatrix();
	}
	else if(objeto == 2){
        // Suelo
		glPushMatrix();
            glScalef(20.0,1.0,60.0);
            glRotatef(-90, 1.0, 0.0, 0.0);
			suelo->draw(modoD, modoV);
		glPopMatrix();
        // Muros
		glPushMatrix();
			glTranslatef(0.0,100.0,0.0);
			glScalef(2.0, 5.0, 60.0);
			glPushMatrix();
				glTranslatef(-310.0,0.0,0.0);
				muro1->draw(modoD, modoV);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(310.0,0.0,0.0);
				muro2->draw(modoD, modoV);
			glPopMatrix();
		glPopMatrix();
        // Aceras
        glPushMatrix();
            glPushMatrix();
                glTranslatef(0.0,20.0,0.0);
                glScalef(4.5,1.0,35.0);
                acera1->draw(modoD, modoV);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(490.0, 20.0,0.0);
                glScalef(4.5,1.0,60.0);
                acera2->draw(modoD, modoV);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-490.0, 20.0,0.0);
                glScalef(4.5,1.0,60.0);
                acera3->draw(modoD, modoV);
            glPopMatrix();
        glPopMatrix();
        // Modelo
        glPushMatrix();
            glTranslatef(0.0,176.0,650.0);
            glScalef(17.0, 17.0, 17.0);
            persona->draw(modoD, modoV);
        glPopMatrix();
	}
}

void Escena::dibujaSeleccion(){
	glDisable(GL_DITHER); // Luz y texturas desactivadas por defecto
	glDisable(GL_LIGHTING);

	// Guarda los modo de dibujado y lo establece en sólido
	int modoD_c = modoD;
	bool modoV_c[6] = {modoV[0],modoV[1],modoV[2],modoV[3],modoV[4],modoV[5]};

	modoD = 1; // modo inmediato
	modoV[0] = false;
	modoV[1] = false;
	modoV[2] = true;    // Modo solido
	modoV[3] = false;
	modoV[4] = false;
	modoV[5] = false;

	// Cambia los colores
		cubo->setColor(0.1, 0.0, 0.0, 0);
		cuadro->setColor(0.2, 0.0, 0.0, 0);
	cilindro->setColor(0.3, 0.0, 0.0, 0);
		esfera->setColor(0.4, 0.0, 0.0, 0);
		peon1->setColor(0.5, 0.0, 0.0, 0);
			ply->setColor(0.6, 0.0, 0.0, 0);
		persona->setColor(0.7, 0.0, 0.0, 0);

	// Dibuja
	dibujarObjetos();

    setColor();

	// Obtenemos el objeto seleccionado
	obtenerObjetoSeleccionado();

	// Restauramos los valores para el dibujado normal
	modoD = modoD_c;
	modoV[0] = modoV_c[0];
	modoV[1] = modoV_c[1];
	modoV[2] = modoV_c[2];
	modoV[3] = modoV_c[3];
	modoV[4] = modoV_c[4];
	modoV[5] = modoV_c[5];

	x_sel = y_sel = -1;
}

void Escena::obtenerObjetoSeleccionado(){
	GLfloat r[3];
	GLint   viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);

	glReadPixels(x_sel, viewport[3]-y_sel, 1, 1, GL_RGB, GL_FLOAT, (void *)r);

	// Redondeados para evitar errores con float
	if(round(r[0]*10)/10 == 0.1){
		if(obj_selec != 1){
			obj_selec = 1;
			setPuntoRotacion(cubo);
            posicionObjeto = cubo->getCoordenadas();
            cubo->setColor(1.0,1.0,0.0, 0);
		}
		else{
			obj_selec = 0;
			camaras[camS]->restaurarPrevioAt();
		}
	}
	else if(round(r[0]*10)/10 == 0.2){
		if(obj_selec != 2){
			obj_selec = 2;
			setPuntoRotacion(cuadro);
            posicionObjeto = cuadro->getCoordenadas();
            cuadro->setColor(1.0,1.0,0.0, 0);
		}
		else{
			obj_selec = 0;
			camaras[camS]->restaurarPrevioAt();
		}
	}
	else if(round(r[0]*10)/10 == 0.3){
		if(obj_selec != 3){
			obj_selec = 3;
			setPuntoRotacion(cilindro);
            posicionObjeto = cilindro->getCoordenadas();
            cilindro->setColor(1.0,1.0,0.0, 0);
		}
		else{
			obj_selec = 0;
			camaras[camS]->restaurarPrevioAt();
		}
	}
	else if(round(r[0]*10)/10 == 0.4){
		if(obj_selec != 4){
			obj_selec = 4;
			setPuntoRotacion(esfera);
            posicionObjeto = esfera->getCoordenadas();
            esfera->setColor(1.0,1.0,0.0, 0);
		}
		else{
			obj_selec = 0;
			camaras[camS]->restaurarPrevioAt();
		}
	}
	else if(round(r[0]*10)/10 == 0.5){
		if(obj_selec != 5){
			obj_selec = 5;
            posicionObjeto = peon1->getCoordenadas();
			setPuntoRotacion(peon1);
            peon1->setColor(1.0,1.0,0.0, 0);
		}
		else{
			obj_selec = 0;
			camaras[camS]->restaurarPrevioAt();
		}
	}
	else if(round(r[0]*10)/10 == 0.6){
		if(obj_selec != 6){
			obj_selec = 6;
			setPuntoRotacion(ply);
            posicionObjeto = ply->getCoordenadas();
            ply->setColor(1.0,1.0,0.0, 0);
		}
		else{
			obj_selec = 0;
			camaras[camS]->restaurarPrevioAt();
		}
	}
	else if(round(r[0]*10)/10 == 0.7){
		if(obj_selec != 7){
			obj_selec = 7;
            posicionObjeto = persona->getCoordenadas();
			camaras[camS]->setAt(persona->getCoordenadas());
            persona->setColor(1.0,1.0,0.0, 0);
		}
		else{
			obj_selec = 0;
			camaras[camS]->restaurarPrevioAt();
		}
	}
}

// ******************************************************************
// ANIMACIÓN
// ******************************************************************

void Escena::animarModeloAutomaticamente(){
	if(animarAutomatico){
        posicionAnimacion += velocidadAnimacion;
        if(posicionAnimacion > 700){
            rotacionAnimacion += velocidadAnimacion;
            if(rotacionAnimacion < 180)
                persona->rotar(velocidadAnimacion);
            else{
                persona->setRotacion180();
                rotacionAnimacion = 0;
                posicionAnimacion = 0;
            }
        }
        else
		    persona->andar(velocidadAnimacion);
    }
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

// *****************************************************************************
// INTERACCIÓN CON EL RATÓN
// ***************************************************************************** 
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
		if(obj_selec == 0){
			camaras[camS]->rotarXFirstPerson((x-x_actual)*0.1);
			camaras[camS]->rotarYFirstPerson((y-y_actual)*0.1);
		}
		else{
			camaras[camS]->rotarXExaminar(-(x-x_actual)*0.1);
			camaras[camS]->rotarYExaminar(-(y-y_actual)*0.1);
		}
		x_actual = x;
		y_actual = y;
	break;
	}
}

// ***********************************************************
// Interacción con el teclado
// ***********************************************************
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
            change_projection();
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
            if(obj_selec != 0 && camaras[camS] != nullptr)
                camaras[camS]->setAt(posicionObjeto);
            
            change_observer();
            change_projection();
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

            if(obj_selec != 0 && camaras[camS] != nullptr)
                camaras[camS]->setAt(posicionObjeto);

            change_observer();
            change_projection();
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

            if(obj_selec != 0 && camaras[camS] != nullptr)
                camaras[camS]->setAt(posicionObjeto);

            change_observer();
            change_projection();
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

            if(obj_selec != 0 && camaras[camS] != nullptr)
                camaras[camS]->setAt(posicionObjeto);

            change_observer();
            change_projection();
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

            if(obj_selec != 0 && camaras[camS] != nullptr)
                camaras[camS]->setAt(posicionObjeto);

            change_observer();
            change_projection();
         }
      break;
      case '6' :
         if(modoMenu == SELVISUALIZACION && modoV[4]){
            luzS = 6;
            cout<<"Luz " << luzS << " seleccionada y ";
            luzActiva[luzS] = !luzActiva[luzS];
            cout<< ( (luzActiva[luzS]) ? "activada" : "desactivada" )<<endl;
         }
         else if(modoMenu == SELMANUAL){
            manualActivado = 6;
            cout<<"Grado de libertad seleccionado: " << manualActivado <<endl;
         }
         else if(modoMenu == SELCAMARAS){
            camS = 6;

            if(obj_selec != 0 && camaras[camS] != nullptr)
                camaras[camS]->setAt(posicionObjeto);

            change_observer();
            change_projection();
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

            if(obj_selec != 0 && camaras[camS] != nullptr)
                camaras[camS]->setAt(posicionObjeto);

            change_observer();
            change_projection();
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
         camaras[camS]->rotarXExaminar(-1);
         break;
	   case GLUT_KEY_RIGHT:
         camaras[camS]->rotarXExaminar(+1);
         break;
	   case GLUT_KEY_UP:
         camaras[camS]->rotarYExaminar(+1);
         break;
	   case GLUT_KEY_DOWN:
         camaras[camS]->rotarYExaminar(-1);
         break;
	   case GLUT_KEY_PAGE_UP:
         camaras[camS]->zoom(1);
         break;
	   case GLUT_KEY_PAGE_DOWN:
         camaras[camS]->zoom(-1);
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

void Escena::change_projection()
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   if(camaras[camS]!=nullptr)  
      camaras[camS]->setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection();
   glViewport( 0, 0, newWidth, newHeight);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   if(camaras[camS]!=nullptr)
      camaras[camS]->setObserver();
}


