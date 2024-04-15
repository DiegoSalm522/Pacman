#include <stdlib.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include "RgbImage.h"
#include "Pacman.h"
#include "Ghost.h"
using namespace std;

//se define la cantidad de texturas que se manejaran
#define NTextures 9
GLuint	textures[NTextures];

char* filenamePacman1 = "pacman1.bmp"; //Arriba
char* filenamePacman2 = "pacman2.bmp"; //Abajo
char* filenamePacman3 = "pacman3.bmp"; //Derecha
char* filenamePacman4 = "pacman4.bmp"; //Izquierda
char* filenamePacmanC = "pacmanC.bmp"; //Cerrado
char* filenameMaze = "maze.bmp"; //Laberinto
char* filenameGhostR = "ghostR.bmp"; //Rojo
char* filenameGhostB = "ghostB.bmp"; //Azul
char* filenameGhostY = "ghostY.bmp"; //Amarillo

Pacman pac_man;
Ghost ghost_red(208,8);
Ghost ghost_blue(8,231);
Ghost ghost_yellow(208,231);

int controlMatrix[10][10] = {
{1, 0, 5, 0, 2, 1, 0, 5, 0, 2},
{7, 0, 9, 5, 6, 6, 5, 9, 0, 8},
{3, 0, 8, 3, 2, 1, 4, 7, 0, 4},
{0, 0, 0, 1, 6, 6, 2, 0, 0, 0},
{0, 0, 9, 8, 0, 0, 7, 9, 0, 0},
{0, 0, 0, 7, 0, 0, 8, 0, 0, 0},
{1, 0, 9, 6, 2, 1, 6, 9, 0, 2},
{3, 2, 7, 5, 6, 6, 5, 8, 1, 4},
{1, 6, 4, 3, 2, 1, 4, 3, 6, 2},
{3, 0, 0, 0, 6, 6, 0, 0, 0, 4}};

int X[224], Y[248];

void loadTextureFromFile(char *filename, int id)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap( filename );

    //generate an OpenGL texture ID for this texture
    glGenTextures(1, &textures[id]);
    //bind to the new texture ID
    glBindTexture(GL_TEXTURE_2D, textures[id]);


    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0,
                     GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
    theTexMap.Reset();
}

void initMatAdy(){
    for(int i = 0; i < 224; i++){
        X[i] = -1;
    }

    for(int i = 0; i < 248; i++){
        Y[i] = -1;
    }

    X[8] = 0;
    X[22] = 1;
    X[46] = 2;
    X[71] = 3;
    X[95] = 4;
    X[120] = 5;
    X[143] = 6;
    X[167] = 7;
    X[192] = 8;
    X[208] = 9;

    Y[8] = 0;
    Y[39] = 1;
    Y[63] = 2;
    Y[87] = 3;
    Y[111] = 4;
    Y[136] = 5;
    Y[159] = 6;
    Y[183] = 7;
    Y[207] = 8;
    Y[231] = 9;
}

int getCelda(float p[2]){
    int x = int(p[0]);
    int y = int(p[1]);
    if(X[x] != -1 && Y[y] != -1){
        return controlMatrix[Y[y]][X[x]];
    }
    return 0;
}

void initPacman(){
    pac_man.texture[0] = textures[0];
    pac_man.texture[1] = textures[1];
    pac_man.texture[2] = textures[2];
    pac_man.texture[3] = textures[3];
    pac_man.texture[4] = textures[4];
    pac_man.draw();
}

void initGhost(){
    ghost_red.texture = textures[5];
    ghost_blue.texture = textures[6];
    ghost_yellow.texture = textures[7];
    ghost_red.draw();
    ghost_blue.draw();
    ghost_yellow.draw();
}

void checkCollision(){
    //Pacman
    int px = int(pac_man.Position[0]);
    int py = int(pac_man.Position[1]);
    //Ghost R
    int grx = int(ghost_red.Position[0]);
    int gry = int(ghost_red.Position[1]);
    //Ghost B
    int gbx = int(ghost_blue.Position[0]);
    int gby = int(ghost_blue.Position[1]);
    //Ghost Y
    int gyx = int(ghost_yellow.Position[0]);
    int gyy = int(ghost_yellow.Position[1]);

    if (px == grx && py == gry){exit(0);}
    if (px == gbx && py == gby){exit(0);}
    if (px == gyx && py == gyy){exit(0);}
}

/*
 * Draw the texture in the OpenGL graphics window
 */
void drawScene(void){

   pac_man.update(getCelda(pac_man.Position));
   ghost_red.update(getCelda(ghost_red.Position));
   ghost_blue.update(getCelda(ghost_blue.Position));
   ghost_yellow.update(getCelda(ghost_yellow.Position));
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //activa la textura
   glEnable(GL_TEXTURE_2D);

   pac_man.draw();
   ghost_red.draw();
   ghost_blue.draw();
   ghost_yellow.draw();

   glBindTexture(GL_TEXTURE_2D, textures[8]);

   glBegin(GL_QUADS);

   glTexCoord2f(0.0, 0.0);
   glVertex2f(0.0, 0.0);

   glTexCoord2f(0.0, 1.0);
   glVertex2f(0.0, 248.0);

   glTexCoord2f(1.0, 1.0);
   glVertex2f(224.0, 248.0);

   glTexCoord2f(1.0, 0.0);
   glVertex2f(224.0, 0.0);

   glEnd();

   glFlush();

   glDisable(GL_TEXTURE_2D);

   checkCollision();

}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 224, 248, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    loadTextureFromFile(filenamePacman1, 0);
    loadTextureFromFile(filenamePacman2, 1);
    loadTextureFromFile(filenamePacman3, 2);
    loadTextureFromFile(filenamePacman4, 3);
    loadTextureFromFile(filenamePacmanC, 4);
    loadTextureFromFile(filenameGhostR,5);
    loadTextureFromFile(filenameGhostB,6);
    loadTextureFromFile(filenameGhostY,7);
    loadTextureFromFile(filenameMaze, 8);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glShadeModel(GL_SMOOTH);
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
			break;
		default:
			break;
   }
}

void SpecialInput(int key, int x, int y){
    int celda = getCelda(pac_man.Position);
    switch(key){
        case GLUT_KEY_UP:
            switch(celda){
                case 0:
                case 1:
                case 2:
                case 5:
                    pac_man.bufferKey = 1;
                    break;
                case 3:
                case 4:
                case 6:
                case 7:
                case 8:
                case 9:
                    pac_man.estado = 1;
                    break;
            }
            break;
        case GLUT_KEY_DOWN:
            switch(celda){
                case 0:
                case 3:
                case 4:
                case 6:
                    pac_man.bufferKey = 2;
                    break;
                case 1:
                case 2:
                case 5:
                case 7:
                case 8:
                case 9:
                    pac_man.estado = 2;
                    break;
            }
            break;
        case GLUT_KEY_RIGHT:
            switch(celda){
                case 0:
                case 2:
                case 4:
                case 8:
                    pac_man.bufferKey = 3;
                    break;
                case 1:
                case 3:
                case 5:
                case 6:
                case 7:
                case 9:
                    pac_man.estado = 3;
                    break;
            }
            break;
        case GLUT_KEY_LEFT:
            switch(celda){
                case 0:
                case 1:
                case 3:
                case 7:
                    pac_man.bufferKey = 4;
                    break;
                case 2:
                case 4:
                case 5:
                case 6:
                case 8:
                case 9:
                    pac_man.estado = 4;
                    break;
            }
            break;
    }
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(269, 298);
	glutInitWindowPosition(100, 100);
    glutCreateWindow("Pacman");
    init();
    initMatAdy();
    initPacman();
    initGhost();
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialInput);
	glutMainLoop();
	return 0;
}
