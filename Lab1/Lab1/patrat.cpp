/*
Programul afiseaza un patrat pe care il translateaza pe axa x la apasarea sagetilor stanga, dreapta
*/
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

static GLfloat x = 0, y = 0, r = 0;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void CALLBACK rot_z_up(AUX_EVENTREC* event) {
    r += 5;
}

void CALLBACK rot_z_down(AUX_EVENTREC* event) {
    r -= 5;
}

void CALLBACK MutaStanga()
{
    x = x - 10;
}

void CALLBACK MutaDreapta()
{
    x = x + 10;
}

void CALLBACK MutaJos()
{
    y = y - 10;
}

void CALLBACK MutaSus()
{
    y = y + 10;
}

void CALLBACK display()
{
    glClear(GL_COLOR_BUFFER_BIT); // se curata ecranul (unde se pun culorile)

    glLoadIdentity(); //il pune in centrul ecranului (axa pe 3 coordonate)

    glTranslatef(x, y , 0.0); //deplaseaza obiecul la o coordonata data

    //daca vreau sa modific pozitia a mai multor obiecte => translatia + ceva dupa care translatia - acel ceva

    glRotatef(r, 0, 0, 1);

    // 1 2          2 1   
    // 4 3  spate   3 4  fata   sensul conteaza , nu ordinea

    glBegin(GL_QUADS);
    {
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-50, -50);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(-50.0, 50.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(50.0, 50.0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(50.0, -50.0);
    }

    //conteaza ordinea
    //glLoadIdentity(); sfera ramane nemiscata
    //glColor3f(0.2, 0.3, 0.5);
    //auxWireSphere(100);

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
    glViewport(0, 0, w, h); //cat folosim din fereastra
    glMatrixMode(GL_PROJECTION); //conversie de la 3d la 2d
    glLoadIdentity();
    if (w <= h) {//spatiul rezervat desenelor   
        glOrtho(-160.0, 160.0, 160.0 * (GLfloat)h / (GLfloat)w, -160.0 * (GLfloat)h / (GLfloat)w, -100.0, 100.0);//volum de vizualizare (ceea ce vad eu)
    }
    else {
        glOrtho(-160.0 * (GLfloat)w / (GLfloat)h, 160.0 * (GLfloat)w / (GLfloat)h, -160.0, 160.0, -100.0, 100.0);
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
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB); // un singur buffer de imagine
    auxInitPosition(0, 0, 800, 600); //fereastra locatie + dimensiune
    auxInitWindow("Un patrat"); //fereastra afisata
    myInit(); //curatam ecran



    auxKeyFunc(AUX_LEFT, MutaStanga);
    auxKeyFunc(AUX_RIGHT, MutaDreapta);
    auxKeyFunc(AUX_DOWN, MutaJos);
    auxKeyFunc(AUX_UP, MutaSus);

    auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_z_up);
    auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEDOWN, rot_z_down);

    auxReshapeFunc(myReshape); // se apeleaza myReshape cand redimensionam fereastra
    auxMainLoop(display); //bucla de evenimente (bucla infinita)
    return(0);
}
