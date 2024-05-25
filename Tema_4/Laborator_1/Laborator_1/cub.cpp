#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"
#include <math.h>

static int angle = 0, angleSun = 0;

GLuint textureId1, textureId2, textureId3, textureId4, textureId5, textureId6;

GLuint incarcaTextura(const char* s)
{
	GLuint textureId = 0;
	AUX_RGBImageRec* pImagineTextura = auxDIBImageLoad(s);

	if (pImagineTextura != NULL)
	{
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, pImagineTextura->sizeX, pImagineTextura->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, pImagineTextura->data);
	}
	if (pImagineTextura)
	{
		if (pImagineTextura->data) {
			free(pImagineTextura->data);
		}
		free(pImagineTextura);
	}
	return textureId;
}

void myInit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);

	textureId1 = incarcaTextura("C:\\Users\\hoadr\\Downloads\\New Project.bmp");


	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
}



void deseneazaCub()
{
	glColor3f(1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, textureId1);
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.5f, 0.5f, -0.5f);
	}
	glEnd();

	glColor3f(0.2, 0.5, 0.0);
	glBindTexture(GL_TEXTURE_2D, textureId2);
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.0, 0.0); glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.5f, 0.5f, -0.5f);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureId3);
	glColor3f(0.6, 0.3, 1.0);
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.0, 0.0); glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.5f, 0.5f, 0.5f);
	}
	glEnd();

	glColor3f(0.5, 0.2, 0.0);
	glBindTexture(GL_TEXTURE_2D, textureId4);
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.5f, 0.5f, 0.5f);
	}
	glEnd();

	glColor3f(0.0, 0.3, 0.8);
	glBindTexture(GL_TEXTURE_2D, textureId5);
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.0, 0.0); glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.5f, 0.5f, 0.5f);
	}
	glEnd();
	glColor3f(0, 0.8, 0.3);
	glBindTexture(GL_TEXTURE_2D, textureId6);

	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.0, 0.0); glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.5f, -0.5f, 0.5f);
	}
	glEnd();
}

void CALLBACK display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0, 0.0, -4.0);
	glRotatef(angle, 1.0, 1.0, 0.0);


	deseneazaCub();


	auxSwapBuffers();
}


void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1, 10);
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
