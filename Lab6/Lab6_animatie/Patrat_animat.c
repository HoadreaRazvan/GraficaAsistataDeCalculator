/*
Programul afiseaza un cub care se roteste
*/
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

static GLfloat alpha;

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);	
}

void CALLBACK display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glRotatef(alpha, 1, 1, 1);

	glColor3f(0.0, 0.0, 0.0);

	auxWireCube(100);

	glFlush();
}

void CALLBACK IdleFunction()
{
	alpha += 1;
	display();
	Sleep(1000.0 / 60.0);
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-160.0, 160.0, -160.0 * (GLfloat)h / (GLfloat)w, 160.0 * (GLfloat)h / (GLfloat)w, -800.0, 800.0);
	}
	else {
		glOrtho(-160.0 * (GLfloat)w / (GLfloat)h, 160.0 * (GLfloat)w / (GLfloat)h, -160.0, 160.0, -800.0, 800.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
	auxInitPosition(0, 0, 800, 600);
	auxInitWindow("Un cub care se roteste");
	myInit();
	auxReshapeFunc(myReshape);
	auxIdleFunc(IdleFunction);
	auxMainLoop(display);
	return 0;
}
