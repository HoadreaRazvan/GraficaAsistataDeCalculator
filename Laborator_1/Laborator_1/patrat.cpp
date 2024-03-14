/*
Programul afiseaza un patrat pe care il translateaza pe axa x la apasarea sagetilor stanga, dreapta
*/
#include <cmath>

#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

static GLfloat x = 0, y = 0, r = 0;

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

void CALLBACK cerc()
{
    glBegin(GL_POLYGON);
    {
        glColor3f(1.0, 0.0, 0.0);
        for (double i = 0; i <= 360; i += 1)
            glVertex2f(50 * sin(i * 3.1415 / 180), 50 * cos(i * 3.1415 / 180));
    }
    glEnd();
}

void CALLBACK paralelipiped()
{
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (double i = 0; i <= 360; i += 90) {

            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(50 * cos(i * 3.1415 / 180), 30 * sin(i * 3.1415 / 180));
            glColor3f(1.0, 1.0, 0.0);
            glVertex2f(0 + 50 * cos(i * 3.1415 / 180) * 1.0, 100 + 30 * sin(i * 3.1415 / 180) * 1.0);
        }
    }
    glEnd();
}

void CALLBACK cilindru()
{
    glBegin(GL_TRIANGLE_STRIP);
    {
        for (double i = 0; i <= 360; i += 1) {

            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(50 * cos(i * 3.1415 / 180), 30 * sin(i * 3.1415 / 180));
            glColor3f(1.0, 1.0, 0.0);
            glVertex2f(0 + 50 * cos(i * 3.1415 / 180) * 1.0, 100 + 30 * sin(i * 3.1415 / 180) * 1.0);
        }
    }
    glEnd();
}

void CALLBACK sfera()
{
    //m1
    GLfloat r = 160, rr = 0;
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 360; i += 1)
    {
        rr = 0;

        for (int j = -r / 2; j <= r / 2; j += r * 0.2) {
            if (j == -r / 2)
                glColor3f(1.0, 0.0, 0.0);
            else
                if (j == r / 2)
                    glColor3f(1.0, 1.0, 0.0);

            glVertex2f(j + rr * 0.3 * cos(i * 3.1415 / 180), rr * sin(i * 3.1415 / 180));

            //rr = sin(i * 3.1415 / 180 ...     ); ?
            rr += 10;
        }

        //m2 cerc rotate

    }
    glEnd();
}

void CALLBACK test()
{
    glBegin(GL_LINE_STRIP);
    for(int ii=50,jj=10;ii>=10 && jj<=50 ;ii--,jj++)
    {
        glColor3f(1.0, 0.0, 0.0);
        for (double i = 0; i <= 360; i += 1)
            glVertex2f(ii * sin(i * 3.1415 / 180), jj * cos(i * 3.1415 / 180));
    }
    glEnd();

    //glBegin(GL_LINE_STRIP);
    //{
    //    glColor3f(1.0, 0.0, 0.0);
    //    GLfloat angle = 90;
    //    for (double i = 0; i <= 360; i += 1)
    //    {
    //        float x_rotated = 20 * sin(i * 3.1415 / 180) * cos(angle * 3.14159f / 180) - 50 * cos(i * 3.1415 / 180) * sin(angle * 3.14159f / 180);
    //        float y_rotated = 20 * sin(i * 3.1415 / 180) * sin(angle * 3.14159f / 180) + 50 * cos(i * 3.1415 / 180) * cos(angle * 3.14159f / 180);
    //        glVertex2f(x_rotated, y_rotated);
    //    }
    //}
    //glEnd();

    //glBegin(GL_LINE_STRIP);
    //{                       
    //    glColor3f(0.0, 1.0, 1.0);
    //    for (double i = 0; i <= 360; i += 1)
    //    {
    //        for (double j = 0; j <= 360; j += 1) {


    //            GLfloat angle = j;
    //            float x_rotated = 20 * sin(i * 3.1415 / 180) * cos(angle * 3.14159f / 180) - 50 * cos(i * 3.1415 / 180) * sin(angle * 3.14159f / 180);
    //            float y_rotated = 20 * sin(i * 3.1415 / 180) * sin(angle * 3.14159f / 180) + 50 * cos(i * 3.1415 / 180) * cos(angle * 3.14159f / 180);
    //            glVertex2f(x_rotated, y_rotated);
    //        }
    //    }
    //}
    //glEnd();
}


void CALLBACK display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glRotatef(r, 0, 0, 1);

    test();

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
