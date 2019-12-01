#include "aux.h"
#include "pierna.h"

Pierna::Pierna(){
    tobillo = new Cilindro(40,1,1);
    antepierna = new Cilindro(40,1,1);
    rodilla = new Esfera(40,40,1);

    tobillo->setColor(1.0, 0.0, 0.0, 0);
    tobillo->setColor(0.0, 1.0, 0.0, 1);
    tobillo->setColor(0.0, 0.0, 1.0, 2);

    antepierna->setColor(0.0, 1.0, 0.0, 0);
    antepierna->setColor(0.0, 1.0, 0.0, 1);
    antepierna->setColor(0.0, 0.0, 1.0, 2);

    rodilla->setColor(0.0, 0.0, 1.0, 0);
    rodilla->setColor(0.0, 1.0, 0.0, 1);
    rodilla->setColor(0.0, 0.0, 1.0, 2);
}

void Pierna::draw(int modoD, int modoV, bool ajedrez){
    glPushMatrix();
        // glScalef(20,20,20);
        // Rotación en X de pierna
        glPushMatrix();
            glTranslatef(0,-4.5,0);
            // Rotación en X de rodilla
            glPushMatrix();
                glTranslatef(0,-3.5,0);
                glScalef(1,3,1);
                tobillo->draw(modoD, modoV, ajedrez);
            glPopMatrix();
                rodilla->draw(modoD, modoV, ajedrez);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-4,0);
            glScalef(1,4,1);
            antepierna->draw(modoD, modoV, ajedrez);
        glPopMatrix();
    glPopMatrix();
}