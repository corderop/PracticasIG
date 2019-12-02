#include "aux.h"
#include "tronco.h"

Tronco::Tronco(){
    cuerpo = new Cilindro(40,1,1);
    brazoDer = new Brazo();
    brazoIzq = new Brazo();

    brazoDer->setRotando(true);
    brazoIzq->setRotando(false);

    cuerpo->setColor(1.0, 0.0, 0.0, 0);
    cuerpo->setColor(0.0, 1.0, 0.0, 1);
    cuerpo->setColor(0.0, 0.0, 1.0, 2);
}

void Tronco::draw(int modoD, bool modoV[]){
    glPushMatrix();
        glPushMatrix();
            glScalef(3,8,3);
            cuerpo->draw(modoD, modoV);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(3.8,8,0);
            brazoIzq->draw(modoD, modoV);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-3.8,8,0);
            brazoDer->draw(modoD, modoV);
        glPopMatrix();
    glPopMatrix();
}

void Tronco::animacionAndar(float velocidad){
    brazoDer->animacionAndar(velocidad);
    brazoIzq->animacionAndar(velocidad);
}