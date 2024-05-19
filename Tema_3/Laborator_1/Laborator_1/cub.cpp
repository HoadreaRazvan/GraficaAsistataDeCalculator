#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"
#include <math.h>

static int angle = 0,angleSun=0;

void myInit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	// reflectanta speculara si exponentul de reflexie speculara nu sunt la valorile implicite (0.0)
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// valori implicite pentru intensitatea sursei LIGHT0
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


	glEnable(GL_LIGHTING); // activare iluminare
	glEnable(GL_LIGHT0);   // activare sursa 0
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
}

void deseneazaCub()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_STRIP);
	{
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	{
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
	}
	glEnd();


	glBegin(GL_TRIANGLE_STRIP);
	{
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	{
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
	}
	glEnd();


	glBegin(GL_TRIANGLE_STRIP);
	{
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	{
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	{
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	{
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	{
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	{
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	{
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	{
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
	}
	glEnd();

}

void CALLBACK display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glLoadIdentity();
	glTranslatef(0.0, 0.0, -4.0);
	glRotatef(angle, 1.0, 1.0, 0.0);
	
	GLfloat light_position[] = { sin(angleSun * 3.14 / 180), cos(angleSun * 3.14 / 180),cos(angleSun * 3.14 / 180) * sin(angleSun * 3.14 / 180) ,1 };	//GLfloat light_position[] = {0, sin(angleSun * 3.14 / 180),1 ,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	deseneazaCub();

	glTranslatef(light_position[0], light_position[1], light_position[2]);
	auxWireCube(0.2);

	glPopMatrix();
	auxSwapBuffers();
}


void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1,10);
	glMatrixMode(GL_MODELVIEW);
}

void CALLBACK IdleFunction()
{
	angle += 1;
	angleSun += 2;
	display();
	Sleep(1000 / 60);
}


int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_DOUBLE | AUX_RGB | AUX_DEPTH);
	auxInitPosition(200, 100, 800, 600);
	auxInitWindow("CUB");
	myInit();
	auxReshapeFunc(myReshape);
	auxIdleFunc(IdleFunction);
	auxMainLoop(display);
	return 0;
}
