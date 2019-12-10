#include "camara.h"

Camara::Camara(int tipo, Tupla3f ojo, Tupla3f arriba,  Tupla3f punto){
    tipo = tipo;
    eye = ojo;
    up = arriba.normalized();
    aspect = 1/1; // Cuadrado
    fov = 45;
    near = 50;
    far  = 2000;
    at = punto;
}

void Camara::mover(float x, float y, float z){
    eye = {x,y,z};
}

void Camara::zoom(float factor){

    // Calculamos el vector de dirección hacia donde miramos
    Tupla3f v = {at(0)-eye(0), at(1)-eye(1), at(2)-eye(2)};
    v = v.normalized();
    v = v*factor;

    // Le sumamos el movimiento en la dirección a la que miramos
    eye(0) += v(0);
    eye(1) += v(1);
    eye(2) += v(2);

    // at proviene de un vector normalizado por lo que lo sobrepasaríamos
    // Para ello lo actualizamos delante del objeto en la misma dirección
    at(0) += v(0);
    at(1) += v(1);
    at(2) += v(2);
}

// Dibujar camaras

void Camara::setObserver(){
    gluLookAt( eye(0), eye(1), eye(2), 
               at(0),  at(1),  at(2), 
               up(0),  up(1),  up(2) );
}

void Camara::setProyeccion(){
    gluPerspective(fov, aspect, near, far);
}

// **************************************
// Rotación en primera persona
// **************************************

// Rotación en primera persona de X
void Camara::rotarXFirstPerson(float angle){
    rotar(angle, 'y', 0);
    rotar(angle, 'y', 1);
}

// Rotación en primera persona de Y
void Camara::rotarYFirstPerson(float angle){
    rotar(angle, 'x', 0);
    rotar(angle, 'x', 1);
}

// Mediante matriz de rotación
void Camara::rotar(float g, char eje, int vector){
    // Vector de visión. Representa la dirección de la visión
    Tupla3f v;
    if(vector == 0){
        v = {at(0)-eye(0), at(1)-eye(1), at(2)-eye(2)};
        v = v.normalized();
    }
    else
        v = up;    
    
    Tupla3f salida;
    g *= (PI/180); // Pasamos a radianes los grados

    // Rotamos el vector de dirección mediante las 
    // matrices de rotación
    switch (eje){

        case 'x':
            salida(0) =   v(0)*1;
            salida(1) =   v(1)*cos(g) + v(2)*(-sin(g));
            salida(2) =   v(1)*sin(g) + v(2)*cos(g);
        break;

        case 'y':
            salida(0) =   v(0)*cos(g)    + v(2)*sin(g);
            salida(1) =   v(1)*1;
            salida(2) =   v(0)*(-sin(g)) + v(2)*cos(g);
        break;

    }

    // Lo convertimos en el punto hacia el que mirar
    // o en el vector up en el segundo caso
    if(vector==0){
        at(0) = salida(0)+eye(0);
        at(1) = salida(1)+eye(1);
        at(2) = salida(2)+eye(2);
    }
    else
        up = salida;
    
}