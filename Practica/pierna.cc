#include "aux.h"
#include "pierna.h"

Pierna::Pierna(){
    tobillo = new Cilindro(40,1,1);
    antepierna = new Cilindro(40,1,1);
    rodilla = new Esfera(40,40,1);

    gradoPierna = 0;

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

void Pierna::draw(int modoD, bool modoV[]){
    glPushMatrix();
        // Rotación en X de pierna
        glRotatef(gradoPierna, 1, 0, 0);
        glPushMatrix();
            glTranslatef(0,-4.5,0);
            glPushMatrix();
                glTranslatef(0,-3.5,0);
                glScalef(1,3,1);
                tobillo->draw(modoD, modoV);
            glPopMatrix();
                rodilla->draw(modoD, modoV);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-4,0);
            glScalef(1,4,1);
            antepierna->draw(modoD, modoV);
        glPopMatrix();
    glPopMatrix();
}

// int Pierna::getGradoPierna(){
//     return gradoPierna;
// }

void Pierna::cambiarGradoPierna(int grado){
    if(gradoPierna+grado<=90 && gradoPierna+grado>=-90)
        gradoPierna += grado;
    else if(gradoPierna+grado>90)
        gradoPierna = 90;
    else
        gradoPierna = -90;
}

void Pierna::animacionAndar(float velocidad){
    // Movemos las piernas
    if(rotando)
        cambiarGradoPierna(velocidad*1);
    else
        cambiarGradoPierna(velocidad*-1);

    // Cambiamos la dirección de las piernas si llegamos a tope
    if(gradoPierna<=-45 || gradoPierna>=45)
        rotando = !rotando;
}

void Pierna::setRotando(bool rot){
    rotando = rot;
}