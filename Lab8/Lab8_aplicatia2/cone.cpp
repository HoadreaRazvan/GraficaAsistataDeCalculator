/*
 * Programul demonstreaza utilizarea iluminarii in OpenGL
 * Se deseneaza un con cu material de culoarea gri. Obiectul este iluminat de o singura sursa de lumina
 */
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

GLfloat light_diffuse[] = { 1.0, 0.2, 1.0, 1.0 };

void CALLBACK changeRedDiffuse()
{
	// modifica componenta rosie a coeficientului de reflexie al materialului
	light_diffuse[0] += 0.1;
	if (light_diffuse[0] > 1.0) {
		light_diffuse[0] = 0.0;
	}
	glColor4fv(light_diffuse);
}

void CALLBACK changeGreenDiffuse()
{
	// modifica componenta verde a coeficientului de reflexie al materialului
	light_diffuse[1] += 0.1;
	if (light_diffuse[1] > 1.0) {
		light_diffuse[1] = 0.0;
	}
	glColor4fv(light_diffuse);
}

void CALLBACK changeBlueDiffuse()
{
	// modifica componenta albastra a coeficientului de reflexie al materialului
	light_diffuse[2] += 0.1;
	if (light_diffuse[2] > 1.0) {
		light_diffuse[2] = 0.0;
	}
	glColor4fv(light_diffuse);
}

void myInit()
{	
	// coeficientii de reflexie pentru reflexia ambientala si cea difuza sunt cei impliciti
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
	//GLfloat light_diffuse[] = { 1.0, 0.2, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	// pozitia sursei nu are valori implicite
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING); // activare iluminare
	glEnable(GL_LIGHT0);   // activare sursa 0

	glEnable(GL_DEPTH_TEST);
}



void CALLBACK display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0, -1.0, 0.0);
	glRotatef(250.0, 1.0, 0.0, 0.0);

	auxSolidCone(1.0, 2.0);

	glTranslatef(1.0, -4.0, 0.0);

	//GLfloat light_diffuse[] = { 1.0, 0.3, 0.1, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	auxSolidSphere(0.5);
	
	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	}
	else {
		glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);
	
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
	auxInitPosition(0, 0, 800, 600);
	auxInitWindow("Iluminarea");
	myInit();
	auxKeyFunc(AUX_R, changeRedDiffuse);
	auxKeyFunc(AUX_r, changeRedDiffuse);
	auxKeyFunc(AUX_G, changeGreenDiffuse);
	auxKeyFunc(AUX_g, changeGreenDiffuse);
	auxKeyFunc(AUX_B, changeBlueDiffuse);
	auxKeyFunc(AUX_b, changeBlueDiffuse);
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
