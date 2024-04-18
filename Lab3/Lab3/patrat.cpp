/*
Programul afiseaza un patrat pe care il translateaza pe axa x la apasarea sagetilor stanga, dreapta
*/
#include <cmath>

#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

static GLfloat x = 0, y = 0, rx = 0, ry = 0, rz = 0;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void CALLBACK rot_x_up() {
    rx += 15;
}

void CALLBACK rot_x_down() {
    rx -= 15;
}

void CALLBACK rot_y_up() {
    ry += 15;
}

void CALLBACK rot_y_down() {
    ry -= 15;
}

void CALLBACK rot_z_up() {
    rz += 15;
}

void CALLBACK rot_z_down() {
    rz -= 15;
}


void CALLBACK MutaStanga()
{
    x = x - 10;
}

void CALLBACK MutaDreapta()
{
    x = x + 10;
}

void CALLBACK MutaSus()
{
    y = y + 10;
}

void CALLBACK MutaJos()
{
    y = y - 10;
}


void CALLBACK display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(x, y, 0.0);

    glRotatef(rx,1,0,0);
    glRotatef(ry,0,1,0);
    glRotatef(rz,0,0,1);



    glColor3f(1.0, 0.0, 0.0); 
    GLUquadricObj* a = gluNewQuadric(); 
    gluQuadricDrawStyle(a, GLU_LINE); 
    gluQuadricNormals(a, GLU_SMOOTH);
    gluQuadricTexture(a, GL_TRUE);
    gluQuadricOrientation(a, GLU_OUTSIDE);

    gluCylinder(a, 50, 0, 100, 20, 20);
    //gluDisk(a, 20, 90, 360, 10);
    //gluPartialDisk(a, 20, 90, 360, 10, 135, 270);
    //gluSphere(a,100,360,20);

    gluDeleteQuadric(a);



    glFlush();
}

#define ISOTROPIC
#ifdef ISOTROPIC
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) {
        return;
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        glOrtho(-160.0, 160.0, 160.0 * (GLfloat)h / (GLfloat)w, -160.0 * (GLfloat)h / (GLfloat)w, -1000.0, 1000.0);
    }
    else {
        glOrtho(-160.0 * (GLfloat)w / (GLfloat)h, 160.0 * (GLfloat)w / (GLfloat)h, -160.0, 160.0, -1000.0, 1000.0);
    }
    glMatrixMode(GL_MODELVIEW);
}
#else
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;			//transformare anizotropica, forma se modifica functie de forma(dimens) viewportului
    glViewport(0, 0, w, h);	//daca w>h stabilim ca baza inaltime, si stab unit logica de dimens in fct de h(h/320, 320 lungime lat patrat)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-160.0, 160.0, -160.0, 160.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}
#endif

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
    auxInitPosition(500, 300, 1500, 1000);
    auxInitWindow("Un patrat");
    myInit();
    auxKeyFunc(AUX_LEFT, MutaStanga);
    auxKeyFunc(AUX_RIGHT, MutaDreapta);

    auxKeyFunc(AUX_UP, MutaSus);
    auxKeyFunc(AUX_DOWN, MutaJos);

    auxKeyFunc(AUX_q, rot_x_up);
    auxKeyFunc(AUX_a, rot_x_down);
    auxKeyFunc(AUX_w, rot_y_up);
    auxKeyFunc(AUX_s, rot_y_down);
    auxKeyFunc(AUX_e, rot_z_up);
    auxKeyFunc(AUX_d, rot_z_down);


    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}
