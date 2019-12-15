#include "camara.h"

Camara::Camara(int tp, Tupla3f ojo, Tupla3f arriba,  Tupla3f punto, float alto, float ancho){
    tipo = tp;
    eye = ojo;
    at = punto;
    up = arriba.normalized();
    
    // Calculamos la dirección de la visión
    Vv = {at(0)-eye(0), at(1)-eye(1), at(2)-eye(2)};

    // Calculamos el eje Y y X
    // El eje X será el resultado del producto vectorial del vector visión y up
    // El eje Y será el resultado del producto vectorial del vector visión y eje x
    Vx = { Vv(1)*up(2) - Vv(2)*up(1), Vv(2)*up(0) - Vv(0)*up(2), Vv(0)*up(1) - Vv(1)*up(0) };
    Vx = Vx.normalized();
    Vy = { Vx(1)*Vv(2) - Vx(2)*Vv(1), Vx(2)*Vv(0) - Vx(0)*Vv(2), Vx(0)*Vv(1) - Vx(1)*Vv(0) };
    Vy = Vy.normalized();

    aspect = ancho/alto;
    left = alto/2;
    top = ancho/2;
    near = 50;
    far  = 2000;
    fov = atan(left/near)*(180/PI)*2;
}

void Camara::mover(float x, float y, float z){
    eye = {x,y,z};
}

void Camara::zoom(float factor){
    // Perspectiva
    // - para que si el factor es positivo se acerque
    if(fov-factor>=1 && fov-factor<=180)
        fov -= factor;

    // Ortográfica
    // Calculamos el valor de left a partir de fov
    // El valor de left, en el caso de que near fuera 1,
    // sería la tangente de fov/2
    left = tan((fov/2)*(PI/180))*near;
    top = left*aspect;
}

// Dibujar camaras

void Camara::setObserver(){
    gluLookAt( eye(0), eye(1), eye(2), 
               at(0),  at(1),  at(2), 
               up(0),  up(1),  up(2) );
}

void Camara::setProyeccion(){
    if(this->tipo == 1){
        gluPerspective(fov, aspect, near, far);
    }
    else if(this->tipo == 0){
        glOrtho(-left, left, -top, top, near, far);
    }
}

void Camara::rotarXExaminar(float angle){
    rotarAlrededor(angle, 'x');
}

void Camara::rotarYExaminar(float angle){
    rotarAlrededor(angle, 'y');
}

// **************************************
// Rotación en primera persona
// **************************************

// Rotación en primera persona de X
void Camara::rotarXFirstPerson(float angle){
    rotarFPS(angle, 'x');
}

// Rotación en primera persona de Y
void Camara::rotarYFirstPerson(float angle){
    rotarFPS(angle, 'y');
}

// Mediante matriz de rotación
void Camara::rotarFPS(float g, char eje){
    // Vectores para la transformación
    Tupla3f Vat, Vup;

    // Calculamos el vector de dirección hacia donde estamos mirando
    Vv    = {at(0)-eye(0), at(1)-eye(1), at(2)-eye(2)};

    g *= (PI/180); // Pasamos a radianes los grados

    // Calculamos la matriz
    if(eje == 'x'){
        Vat = matrizRotacion(Vy, Vv, g);
        Vup = matrizRotacion(Vy, up, g);
        Vx  = matrizRotacion(Vy, Vx, g);
    }
    else if(eje == 'y'){
        Vat = matrizRotacion(Vx, Vv, g);
        Vup = matrizRotacion(Vx, up, g);
        Vy  = matrizRotacion(Vx, Vy, g);
    }

    // Lo convertimos en el punto hacia el que mirar
    at(0) = Vat(0)+eye(0);
    at(1) = Vat(1)+eye(1);
    at(2) = Vat(2)+eye(2);

    // Actualizamos el vector up
    up = Vup;
    
}

// Mediante matriz de rotación
void Camara::rotarAlrededor(float g, char eje){
    // Vectores para la transformación
    Tupla3f Vat, Vup, V;

    // Calculamos el vector de dirección hacia donde estamos mirando
    V    = {eye(0)-at(0), eye(1)-at(1), eye(2)-at(2)};
    // V    = Vv.normalized();

    g *= (PI/180); // Pasamos a radianes los grados

    // Calculamos la matriz
    if(eje == 'x'){
        V   = matrizRotacion(Vy, V, g);
        Vup = matrizRotacion(Vy, up, g);
        Vx  = matrizRotacion(Vy, Vx, g);
    }
    else if(eje == 'y'){
        V   = matrizRotacion(Vx, V, g);
        Vup = matrizRotacion(Vx, up, g);
        Vy  = matrizRotacion(Vx, Vy, g);
    }

    // Lo convertimos en el punto hacia el que mirar
    eye(0) = at(0)+V(0);
    eye(1) = at(1)+V(1);
    eye(2) = at(2)+V(2);

    // Actualizamos el vector up
    up = Vup;
}

// Usa la matriz de rotación en torno a un eje arbitrario
Tupla3f Camara::matrizRotacion(Tupla3f eje, Tupla3f v, float g){
    Tupla3f salida;

    salida(0) = ( cos(g) + eje(0)*eje(0)*(1-cos(g)) )*v(0)        + ( eje(0)*eje(1)*(1-cos(g)) - eje(2)*sin(g) )*v(1) + ( eje(0)*eje(2)*(1-cos(g)) + eje(1)*sin(g) )*v(2);
    salida(1) = ( eje(1)*eje(0)*(1-cos(g)) + eje(2)*sin(g) )*v(0) + ( cos(g) + eje(1)*eje(1)*(1-cos(g)) )*v(1)        + ( eje(1)*eje(2)*(1-cos(g)) - eje(0)*sin(g) )*v(2);
    salida(2) = ( eje(2)*eje(0)*(1-cos(g)) - eje(1)*sin(g) )*v(0) + ( eje(2)*eje(1)*(1-cos(g)) + eje(0)*sin(g) )*v(1) + ( cos(g) + eje(2)*eje(2)*(1-cos(g)) )*v(2);

    return salida;
}