#ifndef PACMAN_H
#define PACMAN_H

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

class Pacman {
public:
    Pacman();
    ~Pacman();
    void draw();
    void update(int celda);
    GLuint texture[4];
    int estado;
    int text;
    int tmp;
    int points;
    int bufferKey;
    float Position[2] = {8.0,8.0};
private:
    float psize = 11;
    float velocidad = 0.08;
    int ntextura = 2;
};

#endif // PACMAN_H
