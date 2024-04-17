/*
 Eliminarea fetelor functie de orientare. Se va afisa fara activarea eliminarii fetelor.
 Cu orientarea directa implicita se vor schimba fetele care se elimina cele fata sau cele spate
 cu functia glCullFace. Se va activa sau se va dezactiva testul de adancime
 */
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

void myInit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_SMOOTH);
}

void CALLBACK display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0, 0.0, -4.0);

	glColor3f(1.0, 0.0, 0.0);
	glRotatef(30, 1.0, 1.0, 0.0);

	
	glEnable(GL_CULL_FACE); //activeaza eliminarea fetelor
	glCullFace(GL_BACK); //sunt eliminate fetele spate
	//inlocuiti cu GL_FRONT pentru fete fata
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	glBegin(GL_QUAD_STRIP); {
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
	}
	glEnd();


	glColor3f(1.0f, 0.0f, 0.0f);
	auxWireSphere(0.7);


	auxSwapBuffers();
	//glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 3.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_DOUBLE | AUX_RGB | AUX_DEPTH);
	auxInitPosition(0, 0, 800, 600);
	auxInitWindow("CUB");
	myInit();
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
