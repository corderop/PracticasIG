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

void Tronco::moverBrazo(int numero, float cambio){
    if(numero==0)
        brazoDer->cambiarGradoBrazo(cambio);
    else
        brazoIzq->cambiarGradoBrazo(cambio);
    
}

void Tronco::setColor(float R, float G, float B, int tipo){
    cuerpo->setColor(R,G,B,tipo);
    brazoIzq->setColor(R,G,B,tipo);
    brazoDer->setColor(R,G,B,tipo);
}

void Tronco::setColorCuerpo(float R, float G, float B, int tipo){
    cuerpo->setColor(R,G,B,tipo);
}

void Tronco::setColorBrazos(float R, float G, float B, int tipo){
    brazoIzq->setColor(R,G,B,tipo);
    brazoDer->setColor(R,G,B,tipo);
}

// Selección de material
void Tronco::setMaterial(Material &mat){
    cuerpo->setMaterial(mat);
    brazoIzq->setMaterial(mat);
    brazoDer->setMaterial(mat);
}

void Tronco::setMaterialCuerpo(Material &mat){
    cuerpo->setMaterial(mat);
}

void Tronco::setMaterialBrazos(Material &mat){
    brazoDer->setMaterial(mat);
    brazoIzq->setMaterial(mat);
}

void Tronco::cambiarTapas(){
    cuerpo->cambiarTapas();
    brazoDer->cambiarTapas();
    brazoIzq->cambiarTapas();
}