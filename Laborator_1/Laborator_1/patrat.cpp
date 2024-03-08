﻿/*
Programul afiseaza un patrat pe care il translateaza pe axa x la apasarea sagetilor stanga, dreapta
*/
#include <cmath>

#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

static GLfloat x = 0,y=0,r=0;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void CALLBACK rot_z_up(AUX_EVENTREC* event) {
    r += 15;
}

void CALLBACK rot_z_down(AUX_EVENTREC* event) {
    r -= 15;
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

   glRotatef(r, 0, 0, 1);

    //glBegin(GL_QUADS);
    //{
    //    glColor3f(1.0, 0.0, 0.0);
    //    glVertex2f(100, 100);
    //    glColor3f(1.0, 1.0, 0.0);
    //    glVertex2f(150.0, 100.0);
    //    glColor3f(0.0, 0.0, 1.0);
    //    glVertex2f(150.0, 150.0);
    //    glColor3f(0.0, 1.0, 0.0);
    //    glVertex2f(100.0, 150.0);
    //}

    glBegin(GL_POLYGON);
    {
        glColor3f(1.0, 0.0, 0.0);
        for (double i = 0; i <= 360; i += 1)
            glVertex2f(50 * cos(i * 3.1415 / 180), 50 * sin(i * 3.1415 / 180));
    }

    glEnd();

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
        glOrtho(-160.0, 160.0, 160.0 * (GLfloat)h / (GLfloat)w, -160.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    }
    else {
        glOrtho(-160.0 * (GLfloat)w / (GLfloat)h, 160.0 * (GLfloat)w / (GLfloat)h, -160.0, 160.0, -10.0, 10.0);
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

    auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_z_up);
    auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEDOWN, rot_z_down);

    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}