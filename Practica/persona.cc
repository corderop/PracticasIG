#include "aux.h"
#include "persona.h"

Persona::Persona(){
    piernaDer = new Pierna();
    piernaIzq = new Pierna();
    tronco = new Tronco();
    cabeza = new Esfera(40,40,1);

    cabeza->setColor(1.0, 0.0, 0.0, 0);
    cabeza->setColor(0.0, 1.0, 0.0, 1);
    cabeza->setColor(0.0, 0.0, 1.0, 2);
}

void Persona::draw(int modoD, int modoV, bool ajedrez){
    glPushMatrix();
        glScalef(20,20,20);
            tronco->draw(modoD, modoV, ajedrez);
        glPushMatrix();
            glTranslatef(0,10,0);
            glScalef(2,2,2);
            cabeza->draw(modoD, modoV, ajedrez);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(2,0,0);
            piernaIzq->draw(modoD, modoV, ajedrez);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-2,0,0);
            piernaDer->draw(modoD, modoV, ajedrez);
        glPopMatrix();
    glPopMatrix();
}