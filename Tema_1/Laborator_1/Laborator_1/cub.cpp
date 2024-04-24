#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

static int alfaX = 0.0f, alfaY = 0.0f, alfaZ = 0.0f,l=200;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void CALLBACK RotesteXStanga()
{
    alfaX = alfaX - 10;
}

void CALLBACK RotesteXDreapta()
{
    alfaX = alfaX + 10;
}

void CALLBACK RotesteYStanga()
{
    alfaY = alfaY - 10;
}

void CALLBACK RotesteYDreapta()
{
    alfaY = alfaY + 10;
}

void CALLBACK RotesteZStanga()
{
    alfaZ = alfaZ - 10;
}

void CALLBACK RotesteZDreapta()
{
    alfaZ = alfaZ + 10;
}

void CALLBACK display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0, 0, -500.0);

    //glRotatef(30, 1.0, 1.0, 0.0);

    glRotatef(alfaX, 1.0, 0.0, 0.0);
    glRotatef(alfaY, 0.0, 1.0, 0.0);
    glRotatef(alfaZ, 0.0, 0.0, 1.0);

    glColor3f(1.0, 0.0, 0.0);

    auxWireCube(l);//cubul

    //diagonalele
    glBegin(GL_LINES);
    {
        glVertex3f(l/2, -l / 2, -l / 2);
        glVertex3f(-l / 2, l / 2, -l / 2);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glVertex3f(l / 2, -l / 2, l / 2);
        glVertex3f(l / 2, l / 2, -l / 2);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glVertex3f(-l / 2, -l / 2, l / 2);
        glVertex3f(l / 2, l / 2, l / 2);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glVertex3f(-l / 2, -l / 2, -l / 2);
        glVertex3f(-l / 2, l / 2, l / 2);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glVertex3f(l / 2, l / 2, -l / 2);
        glVertex3f(-l / 2, l / 2, l / 2);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glVertex3f(l / 2, -l / 2, l / 2);
        glVertex3f(-l / 2, -l / 2, -l / 2);
    }
    glEnd();


    glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}



int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
    auxInitPosition(0, 0, 800, 600);
    auxInitWindow("Un inceput de cub");
    myInit();
    auxKeyFunc(AUX_q, RotesteXStanga);
    auxKeyFunc(AUX_a, RotesteXDreapta);
    auxKeyFunc(AUX_w, RotesteYStanga);
    auxKeyFunc(AUX_s, RotesteYDreapta);
    auxKeyFunc(AUX_e, RotesteZStanga);
    auxKeyFunc(AUX_d, RotesteZDreapta);

    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}
