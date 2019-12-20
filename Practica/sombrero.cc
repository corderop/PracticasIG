#include "aux.h"
#include "sombrero.h"

Sombrero::Sombrero(){
    arriba = new Cilindro(40,1,1);
    abajo = new Cilindro(40,1,1);

    altura = ALT_MIN;
}

void Sombrero::draw(int modoD, bool modoV[]){
    glPushMatrix();
        glTranslatef(0.0, altura, 0.0);
        glPushMatrix();
            glScalef(1.7, 3.2, 1.7);
            arriba->draw(modoD, modoV);
            glScalef(1.8, 0.1, 1.8);
            abajo->draw(modoD, modoV);
        glPopMatrix();
    glPopMatrix();
}

void Sombrero::cambiarAlturaSombrero(float suma){
    float aux = altura+(suma*0.08);

    if(aux <= ALT_MAX && aux >= ALT_MIN)
        altura = aux;
}

void Sombrero::animacionAndar(float velocidad){

    if(subiendo && altura+velocidad*0.08 <= ALT_MAX)
        cambiarAlturaSombrero(velocidad);
    else if(subiendo){
        subiendo = false;
        cambiarAlturaSombrero(-velocidad);
    }    
    else if(!subiendo && altura-velocidad*0.08 >= ALT_MIN)
        cambiarAlturaSombrero(-velocidad);
    else if(!subiendo){
        subiendo = true;
        cambiarAlturaSombrero(velocidad);
    }
    
}

// Modificación de colores
void Sombrero::setColor(float R, float G, float B, int tipo){
    arriba->setColor(R,G,B,tipo);
    abajo->setColor(R,G,B,tipo);
}

// Modificación de colores
void Sombrero::setMaterial(Material &mat){
    arriba->setMaterial(mat);
    abajo->setMaterial(mat);
}

// Modificación de tapas
void Sombrero::cambiarTapas(){
    arriba->cambiarTapas();
    abajo->cambiarTapas();
}