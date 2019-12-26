#include "aux.h"
#include "material.h"

Material::Material(){
    Tupla4f n(0.0, 0.0, 0.0, 0.0);

    this->difuso = n;
    this->especular = n;
    this->ambiente = n;
    this->brillo = 0.0;
}

Material::Material (const Material &mat){
    (*this) = mat;
}

Material::Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float mbrillo){

    this->difuso = mdifuso;
    this->especular = mespecular;
    this->ambiente = mambiente;
    this->brillo = mbrillo;
}
                
void Material::aplicar(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
}

void Material::operator=( const Material &Mat){
   this->difuso = Mat.difuso;
   this->especular = Mat.especular;
   this->ambiente = Mat.ambiente;
   this->brillo = Mat.brillo;
}