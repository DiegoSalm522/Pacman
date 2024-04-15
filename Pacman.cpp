#include "Pacman.h"
#include <stdlib.h>
#include <GL/glut.h>
#include "RgbImage.h"
#include <iostream>
using namespace std;


Pacman::Pacman()
{
    estado = 0;
    text = ntextura;
    tmp = 0;
    points = 0;
    bufferKey = -1;
}

Pacman::~Pacman(){

}

void Pacman::draw(){

   glBindTexture(GL_TEXTURE_2D, texture[text]);

   glBegin(GL_QUADS);

   glTexCoord2f(0.0, 0.0);
   glVertex2f(Position[0], Position[1]);

   glTexCoord2f(1.0, 0.0);
   glVertex2f((Position[0] + psize), Position[1]);

   glTexCoord2f(1.0, 1.0);
   glVertex2f((Position[0] + psize), (Position[1] + psize));

   glTexCoord2f(0.0, 1.0);
   glVertex2f(Position[0], (Position[1] + psize));

   glEnd();

}

void Pacman::update(int celda){

    if(celda != 0 && bufferKey != -1){
        estado = bufferKey;
        bufferKey = -1;
    }

    tmp += 1;
    points += 1;

    if (tmp == 150){
        tmp = 0;
        if (text == ntextura){
            text = 5;
        }
        else{
            text = ntextura;
        }

    }

    switch(estado){
        case 1: //Arriba
            ntextura = 1;
            switch(celda){
                case 1:
                case 2:
                case 5:
                    estado = 0;
                    break;
                default:
                    Position[1] -= velocidad;
            }
            break;
        case 2: //Abajo
            ntextura = 0;
            switch(celda){
                case 3:
                case 4:
                case 6:
                    estado = 0;
                    break;
                default:
                    Position[1] += velocidad;

            }
            break;
        case 3: //Derecha
            ntextura = 2;
            switch(celda){
                case 2:
                case 4:
                case 8:
                    estado = 0;
                    break;
                default:
                    Position[0] += velocidad;
            }
            break;
        case 4: //Izquierda
            ntextura = 3;
            switch(celda){
                case 1:
                case 3:
                case 7:
                    estado = 0;
                    break;
                default:
                    Position[0] -= velocidad;
            }
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
    cout << Position[0] << "; Y= " << Position[1] << endl;
    cout << points << endl;
}
