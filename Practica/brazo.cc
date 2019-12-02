#include "aux.h"
#include "brazo.h"

Brazo::Brazo(){
    brazo = new Cilindro(40,1,1);

    gradoBrazo = 0;

    brazo->setColor(0.0, 1.0, 0.0, 0);
    brazo->setColor(1.0, 0.0, 0.0, 1);
    brazo->setColor(0.0, 0.0, 1.0, 2);
}

void Brazo::draw(int modoD, bool modoV[]){
    glPushMatrix();
        // Rotación en X de Brazo
        glRotatef(gradoBrazo, 1, 0, 0);
        glTranslatef(0,-6,0);
        glScalef(0.8,6,0.8);
        brazo->draw(modoD, modoV);
    glPopMatrix();
}

void Brazo::cambiarGradoBrazo(int grado){
    if(gradoBrazo+grado<=90 && gradoBrazo+grado>=-90)
        gradoBrazo += grado;
    else if(gradoBrazo+grado>90)
        gradoBrazo = 90;
    else
        gradoBrazo = -90;
}

void Brazo::animacionAndar(float velocidad){
    // Movemos los brazos
    if(rotando)
        cambiarGradoBrazo(velocidad*1);
    else
        cambiarGradoBrazo(velocidad*-1);

    // Cambiamos la dirección de los brazos si llegamos a tope
    if(gradoBrazo<=-45 || gradoBrazo>=45)
        rotando = !rotando;
}

void Brazo::setRotando(bool rot){
    rotando = rot;
}