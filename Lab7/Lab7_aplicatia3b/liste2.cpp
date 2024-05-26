/*
 *	Programul demonstreaza utilizarea functiilor glGenList() si glPushAttrib().
 *  Programul arata ca matricea de vizualizare si culoarea sunt restaurate inainte de desenarea liniei.
 */
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

GLuint listName;

void myInit()
{
	GLfloat color_vector[3] = { 1.0, 0.0, 0.0 };

	listName = glGenLists(1);
	glNewList(listName, GL_COMPILE);
	{
		glTranslatef(1.5, 0.0, 0.0);
		glPushAttrib(GL_CURRENT_BIT);
		glColor3fv(color_vector);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);
			glVertex2f(1.0, 0.0);
		}
		glEnd();
		glTranslatef(1.5, 0.0, 0.0);
		glPopAttrib();
	}
	glEndList();
}

void drawLine()
{
	glBegin(GL_LINES);
	{
		glVertex2f(0.0, 0.5);
		glVertex2f(15.0, 0.5);
	}
	glEnd();
}

void CALLBACK display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();	
		
	glPushMatrix();
	GLfloat new_color[3] = { 0.0, 1.0, 0.0 };
	glColor3fv(new_color);
	for (int i = 0; i < 3; i++) {
		glCallList(listName);
	}
	glPopMatrix();

	glTranslatef(0.0, 0.2, 0.0);
	drawLine();
	glTranslatef(0.0, -0.2, 0.0);
	drawLine();

	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		gluOrtho2D(0.0, 2.0, -0.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w);
	}
	else {
		gluOrtho2D(0.0, 2.0 * (GLfloat)w / (GLfloat)h, -0.5, 1.5);
	}
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
	auxInitPosition(0, 0, 800, 100);
	auxInitWindow("Liste de display");
	myInit();
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
