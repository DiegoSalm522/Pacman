#include "Ghost.h"
#include <stdlib.h>
#include <GL/glut.h>
#include "RgbImage.h"
#include <iostream>
using namespace std;


Ghost::Ghost(int x, int y)
{
    Position[0] = x;
    Position[1] = y;
    direccion = 0;
    valor = -1;
    lastCelda = -1;
}

Ghost::~Ghost(){

}

void Ghost::draw(){

   glBindTexture(GL_TEXTURE_2D, texture);

   glBegin(GL_QUADS);

   glTexCoord2f(0.0, 0.0);
   glVertex2f(Position[0] + psize, Position[1] + psize);

   glTexCoord2f(1.0, 0.0);
   glVertex2f((Position[0]), Position[1] + psize);

   glTexCoord2f(1.0, 1.0);
   glVertex2f((Position[0]), (Position[1]));

   glTexCoord2f(0.0, 1.0);
   glVertex2f(Position[0] + psize, (Position[1]));

   glEnd();

}

void Ghost::update(int celda){
    if (direccion == 0){
        switch(celda){
            case 2:
                valor = rand() % 2;
                if(valor == 0)
                    direccion = 2;
                else if (valor == 1)
                    direccion = 4;
                break;
            case 3:
                valor = rand() % 2;
                if(valor == 0)
                    direccion = 1;
                else if (valor == 1)
                    direccion = 3;
                break;
            case 4:
                valor = rand() % 2;
                if(valor == 0)
                    direccion = 1;
                else if (valor == 1)
                    direccion = 4;
                break;
        }
        lastCelda = celda;
    }

    if (celda != 0 && celda != lastCelda && direccion != 0){
        switch(celda){
            case 1:
                if(direccion == 1)
                    direccion = 3;
                else if(direccion == 4)
                    direccion = 2;
                break;
            case 2:
                if(direccion == 1)
                    direccion = 4;
                else if(direccion == 3)
                    direccion = 2;
                break;
            case 3:
                if(direccion == 2)
                    direccion = 3;
                else if(direccion == 4)
                    direccion = 1;
                break;
            case 4:
                if(direccion == 2)
                    direccion = 4;
                else if(direccion == 3)
                    direccion = 1;
                break;
            case 5:
                if(direccion == 1){
                    valor = rand() % 2;
                    if(valor == 0)
                        direccion = 3;
                    else if (valor == 1)
                        direccion = 4;
                }
                else if(direccion == 3){
                    valor = rand() % 2;
                    if(valor == 0)
                        direccion = 2;
                    else if (valor == 1)
                        direccion = 3;
                }
                else if(direccion == 4){
                    valor = rand() % 2;
                    if(valor == 0)
                        direccion = 2;
                    else if (valor == 1)
                        direccion = 4;
                }
                break;
            case 6:
                if(direccion == 2){
                    valor = rand() % 2;
                    if(valor == 0)
                        direccion = 3;
                    else if (valor == 1)
                        direccion = 4;
                }
                else if(direccion == 3){
                    valor = rand() % 2;
                    if(valor == 0)
                        direccion = 1;
                    else if (valor == 1)
                        direccion = 3;
                }
                else if(direccion == 4){
                    valor = rand() % 2;
                    if(valor == 0)
                        direccion = 1;
                    else if (valor == 1)
                        direccion = 4;
                }
                break;
            case 7:
                if(direccion == 1){
                    valor = rand() % 2;
                    if(valor == 0)
                        direccion = 1;
                    else if (valor == 1)
                        direccion = 3;
                }
                else if(direccion == 2){
                    valor = rand() % 2;
                    if(valor == 0)
                        direccion = 2;
                    else if (valor == 1)
                        direccion = 3;
                }
                else if(direccion == 4){
                    valor = rand() % 2;
                    if(valor == 0)
                        direccion = 1;
                    else if (valor == 1)
                        direccion = 2;
                }
                break;
            case 8:
                if(direccion == 1){
                    valor = rand() % 2;
                    if(valor == 0)
                        direccion = 1;
                    else if (valor == 1)
                        direccion = 4;
                }
                else if(direccion == 2){
                    valor = rand() % 2;
                    if(valor == 0)
                        direccion = 2;
                    else if (valor == 1)
                        direccion = 4;
                }
                else if(direccion == 3){
                    valor = rand() % 2;
                    if(valor == 0)
                        direccion = 1;
                    else if (valor == 1)
                        direccion = 2;
                }
                break;
            case 9:
                if(direccion == 1){
                    valor = rand() % 3;
                    if(valor == 0)
                        direccion = 1;
                    else if (valor == 1)
                        direccion = 3;
                    else if (valor == 2)
                        direccion = 4;
                }
                else if(direccion == 2){
                    valor = rand() % 3;
                    if(valor == 0)
                        direccion = 2;
                    else if (valor == 1)
                        direccion = 3;
                    else if (valor == 2)
                        direccion = 4;

                }
                else if(direccion == 3){
                    valor = rand() % 3;
                    if(valor == 0)
                        direccion = 1;
                    else if (valor == 1)
                        direccion = 2;
                    else if (valor == 2)
                        direccion = 3;
                }
                else if(direccion == 4){
                    valor = rand() % 3;
                    if(valor == 0)
                        direccion = 1;
                    else if (valor == 1)
                        direccion = 2;
                    else if (valor == 2)
                        direccion = 4;
                }
                break;
        }
        lastCelda = celda;
    }

    switch(direccion){
        case 1:
            Position[1] -= velocidad;
            break;
        case 2:
            Position[1] += velocidad;
            break;
        case 3:
            Position[0] += velocidad;
            break;
        case 4:
            Position[0] -= velocidad;
            break;
    }

    if(int(Position[1]) == 111){
        if(Position[0] < 1){
            Position[0] = 220;
        }
        else if (Position[0] > 220){
            Position[0] = 1;
        }
    }
}
