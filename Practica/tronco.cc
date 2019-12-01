#include "aux.h"
#include "tronco.h"

Tronco::Tronco(){
    cuerpo = new Cilindro(40,1,1);
    brazoDer = new Cilindro(40,1,1);
    brazoIzq = new Cilindro(40,1,1);

    cuerpo->setColor(1.0, 0.0, 0.0, 0);
    cuerpo->setColor(0.0, 1.0, 0.0, 1);
    cuerpo->setColor(0.0, 0.0, 1.0, 2);

    brazoDer->setColor(0.0, 1.0, 0.0, 0);
    brazoDer->setColor(0.0, 1.0, 0.0, 1);
    brazoDer->setColor(0.0, 0.0, 1.0, 2);

    brazoIzq->setColor(0.0, 0.0, 1.0, 0);
    brazoIzq->setColor(0.0, 1.0, 0.0, 1);
    brazoIzq->setColor(0.0, 0.0, 1.0, 2);
}

void Tronco::draw(int modoD, int modoV, bool ajedrez){
    glPushMatrix();
        // glScalef(20,20,20);
        glPushMatrix();
            glScalef(3,8,3);
            // glTranslatef(1.5,0,0);
            cuerpo->draw(modoD, modoV, ajedrez);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(4.05,2,0);
            glScalef(0.8,6,0.8);
            brazoIzq->draw(modoD, modoV, ajedrez);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-4.05,2,0);
            glScalef(0.8,6,0.8);
            brazoDer->draw(modoD, modoV, ajedrez);
        glPopMatrix();
    glPopMatrix();
}