#include "aux.h"
#include "pierna.h"

Pierna::Pierna(){
    tobillo = new Cilindro(40,1,1);
    antepierna = new Cilindro(40,1,1);
    rodilla = new Esfera(40,40,1);

    gradoPierna = 0;
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

void Pierna::cambiarGradoPierna(int grado){
    // No permite que sobrepasar un límite de grados
    // para no hacer movimientos antinaturales de una pierna
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

// Modificación de colores
void Pierna::setColor(float R, float G, float B, int tipo){
    tobillo->setColor(R,G,B,tipo);
    antepierna->setColor(R,G,B,tipo);
    rodilla->setColor(R,G,B,tipo);
}

void Pierna::setColorTobillo(float R, float G, float B, int tipo){
    tobillo->setColor(R,G,B,tipo);
}
void Pierna::setColorAntepierna(float R, float G, float B, int tipo){
    antepierna->setColor(R,G,B,tipo);
}
void Pierna::setColorRodilla(float R, float G, float B, int tipo){
    rodilla->setColor(R,G,B,tipo);
}

// Modificación de colores
void Pierna::setMaterial(Material &mat){
    tobillo->setMaterial(mat);
    antepierna->setMaterial(mat);
}

void Pierna::setMaterialTobillo(Material &mat){
    tobillo->setMaterial(mat);
}

void Pierna::setMaterialAntepierna(Material &mat){
    antepierna->setMaterial(mat);
}

void Pierna::setMaterialRodilla(Material &mat){
    rodilla->setMaterial(mat);
}

// Modificación de tapas
void Pierna::cambiarTapas(){
    tobillo->cambiarTapas();
    antepierna->cambiarTapas();
    rodilla->cambiarTapas();
}