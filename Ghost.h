#ifndef GHOST_H
#define GHOST_H
#include <string>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std; // Add this line

class Ghost {
public:
    Ghost(int x, int y);
    ~Ghost();
    void draw();
    void update(int celda);
    GLuint texture;
    int direccion;
    int valor;
    int lastCelda;
    float Position[2];
    int lastStates[2] = {0,0};
private:
    float psize = 11;
    float velocidad = 0.05;
};

#endif // GHOST_H
