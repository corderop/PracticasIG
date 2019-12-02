#include "aux.h"
#include "persona.h"

Persona::Persona(){
    piernaDer = new Pierna();
    piernaIzq = new Pierna();
    tronco = new Tronco();
    cabeza = new Esfera(40,40,1);

    orientacion = 0;
    avance = 0;
    piernaDer->setRotando(false);
    piernaIzq->setRotando(true);

    cabeza->setColor(1.0, 0.0, 0.0, 0);
    cabeza->setColor(0.0, 1.0, 0.0, 1);
    cabeza->setColor(0.0, 0.0, 1.0, 2);
}

void Persona::draw(int modoD, bool modoV[]){
    glPushMatrix();
        glTranslatef(avance*cos(orientacion*M_PI/180),0,-avance*sin(orientacion*M_PI/180));
        glRotatef(orientacion, 0, 1, 0);
        glRotatef(90, 0, 1, 0);

        // Persona
        tronco->draw(modoD, modoV);
        glPushMatrix();
            glTranslatef(0,10,0);
            glScalef(2,2,2);
            cabeza->draw(modoD, modoV);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(2,0,0);
            piernaIzq->draw(modoD, modoV);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-2,0,0);
            piernaDer->draw(modoD, modoV);
        glPopMatrix();
    glPopMatrix();
}

void Persona::rotar(int grados){
    orientacion = (orientacion+grados)%360;
}

void Persona::avanzar(float mod){
    avance += mod;
}

void Persona::andar(float velocidad=1){
    piernaDer->animacionAndar(velocidad);
    piernaIzq->animacionAndar(velocidad);
    tronco->animacionAndar(velocidad);
    avanzar(velocidad*0.1);
}