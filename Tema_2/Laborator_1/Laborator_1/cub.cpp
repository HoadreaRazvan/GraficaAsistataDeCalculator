/*
 Eliminarea fetelor functie de orientare. Se va afisa fara activarea eliminarii fetelor.
 Cu orientarea directa implicita se vor schimba fetele care se elimina cele fata sau cele spate
 cu functia glCullFace. Se va activa sau se va dezactiva testul de adancime
 */
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

int r = 0;

void myInit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_SMOOTH);
}

void cub()
{
	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
	}
	glEnd();


	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
	}
	glEnd();


	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
	}
	glEnd();

}

void CALLBACK display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -4.0);
	glRotatef(r, 1, 1, 1);


	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineStipple(1, 1);
	glEnable(GL_LINE_STIPPLE);

	glColor3f(1, 0, 0);
	cub();


	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineStipple(1, 0xFFFF);
	glEnable(GL_LINE);

	glColor3f(1, 1, 0);
	cub();

	glFlush();
}

void CALLBACK IdleFunction()
{
	r = (r + 15) % 360;
	display();
	Sleep(24000.0 / 60.0);
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
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH);
	auxInitPosition(0, 0, 800, 600);
	auxInitWindow("CUB");
	myInit();
	auxReshapeFunc(myReshape);
	auxIdleFunc(IdleFunction);
	auxMainLoop(display);


	return 0;
}
