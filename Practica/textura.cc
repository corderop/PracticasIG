#include "textura.h"

Textura::Textura(const Textura &tex){
    pimg = tex.pimg;
    textura_id = tex.textura_id;
    data = tex.data;
    width = tex.width;
    height = tex.height;
}

Textura::Textura(std::string archivo){
    pimg = new jpg::Imagen(archivo);
    width = pimg->tamX();
    height = pimg->tamY();
    data = pimg->leerPixels();

    // Creamos el id de la textura
    glGenTextures(1, &textura_id);
}

void Textura::activar(){
    // Activamos el identificador de textura activa
    glBindTexture( GL_TEXTURE_2D, textura_id );

    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
}

int Textura::ancho(){
    return width;
}
int Textura::alto(){
    return height;
}