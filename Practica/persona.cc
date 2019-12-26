#include "aux.h"
#include "persona.h"

Persona::Persona(){
    piernaDer = new Pierna();
    piernaIzq = new Pierna();
    tronco = new Tronco();
    cabeza = new Esfera(40,40,1);
    sombrero = new Sombrero();

    orientacion = 90;
    avance = 0;
    piernaDer->setRotando(false);
    piernaIzq->setRotando(true);
}

void Persona::draw(int modoD, bool modoV[]){
    glPushMatrix();
        glTranslatef(c(0) + avance*cos(orientacion*M_PI/180),0,c(2) + (-avance*sin(orientacion*M_PI/180)));
        c(0) += avance*cos(orientacion*M_PI/180);
        c(2) += -avance*sin(orientacion*M_PI/180);
        avance = 0;
        glRotatef(orientacion, 0, 1, 0);
        glRotatef(90, 0, 1, 0);
        // Persona
        sombrero->draw(modoD, modoV);
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
    avance = mod;
}

void Persona::setRotacion180(){
    if(abs(90-orientacion) < abs(270-orientacion))
        orientacion = 90;
    else
        orientacion = 270;
    
}

void Persona::moverGradoLibertad(int numero, float cambio){

    switch(numero) {
        case 0:
            rotar((int)cambio);
            break;
        case 1:
            avanzar(cambio);
            break;
        case 2:
            piernaDer->cambiarGradoPierna(cambio);
            break;
        case 3:
            piernaIzq->cambiarGradoPierna(cambio);
            break;
        case 4:
            // Brazo der
            tronco->moverBrazo(0, cambio);
            break;
        case 5:
            // Brazo izq
            tronco->moverBrazo(1, cambio);
            break;
        case 6:
            sombrero->cambiarAlturaSombrero(cambio);
            break;
    }
}

void Persona::andar(float velocidad=1){
    piernaDer->animacionAndar(velocidad);
    piernaIzq->animacionAndar(velocidad);
    tronco->animacionAndar(velocidad);
    sombrero->animacionAndar(velocidad);
    avanzar(velocidad*0.1);
}

// Selección de colores
void Persona::setColor(float R, float G, float B, int tipo){
    piernaIzq->setColor(R,G,B,tipo);
    piernaDer->setColor(R,G,B,tipo);
    tronco->setColor(R,G,B,tipo);
    cabeza->setColor(R,G,B,tipo);
    sombrero->setColor(R,G,B,tipo);
}

void Persona::setColorPiel(float R, float G, float B){
    cabeza->setColor(R, G, B, 0);
    piernaIzq->setColorRodilla(R, G, B, 0);
    piernaIzq->setColorTobillo(R, G, B, 0);
    piernaDer->setColorRodilla(R, G, B, 0);
    piernaDer->setColorTobillo(R, G, B, 0);
    tronco->setColorBrazos(R, G, B, 0);
}

void Persona::setColorPantalones(float R, float G, float B){
    piernaIzq->setColorAntepierna(R, G, B, 0);
    piernaDer->setColorAntepierna(R, G, B, 0);
}

void Persona::setColorCamiseta(float R, float G, float B){
    tronco->setColorCuerpo(R, G, B, 0);
}

void Persona::setColorSombrero(float R, float G, float B){
    sombrero->setColor(R,G,B,0);
}

// Selección de material
void Persona::setMaterial(Material & mat){
    piernaDer->setMaterial(mat);
    piernaIzq->setMaterial(mat);
    tronco->setMaterial(mat);
    cabeza->setMaterial(mat);
    sombrero->setMaterial(mat);
}

void Persona::setMaterialPiel(Material & mat){
    cabeza->setMaterial(mat);
    piernaIzq->setMaterialRodilla(mat);
    piernaIzq->setMaterialTobillo(mat);
    piernaDer->setMaterialRodilla(mat);
    piernaDer->setMaterialTobillo(mat);
    tronco->setMaterialBrazos(mat);
}

void Persona::setMaterialPantalones(Material & mat){
    piernaIzq->setMaterialAntepierna(mat);
    piernaDer->setMaterialAntepierna(mat);
}

void Persona::setMaterialCamiseta(Material & mat){
    tronco->setMaterialCuerpo(mat);
}

void Persona::setMaterialSombrero(Material & mat){
    sombrero->setMaterial(mat);
}

// Cambio de tapas
void Persona::cambiarTapas(){
    piernaDer->cambiarTapas();
    piernaIzq->cambiarTapas();
    tronco->cambiarTapas();
    cabeza->cambiarTapas();
    sombrero->cambiarTapas();
}

void Persona::modificarCoordenadas(int x_p, int y_p, int z_p){
    c(0) = x_p;
    c(1) = y_p;
    c(2) = z_p;
}
