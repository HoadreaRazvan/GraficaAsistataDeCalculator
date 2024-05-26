/*
 *  Decuparea obiectelor dupa plane de decupare
 */
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

static GLfloat rx = 0, ry = 0, rz = 0;


void CALLBACK rot_x_up() {
	rx += 15;
}

void CALLBACK rot_x_down() {
	rx -= 15;
}

void CALLBACK rot_y_up() {
	ry += 15;
}

void CALLBACK rot_y_down() {
	ry -= 15;
}

void CALLBACK rot_z_up() {
	rz += 15;
}

void CALLBACK rot_z_down() {
	rz -= 15;
}

void initLights()
{
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat position[] = { 0.0, 0.0, 2.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void CALLBACK display()
{	// se definesc coeficientii A, B, C, D din ecuatia planuluide decupare GL_CLIP_PLANE0, ecuatia: x=1
	//GLdouble eqn0[4] = { 1.0, 0.0, 0.0, 1.0 };
	GLdouble eqn0[4] = { 0.0, -1.0, 0.0, 0.0 };
	// se definesc coeficientii A, B, C, D din ecuatia planului de decupare GL_CLIP_PLANE1, ecuatia: -x=1
	GLdouble eqn1[4] = { -1.0, 0.0, 0.0, 1.0 };
	// se definesc coeficientii A, B, C, D din ecuatia planului de decupare GL_CLIP_PLANE2, ecuatia: y=1
	GLdouble eqn2[4] = { 0.0, 1.0, 0.0, 1.0 };
	// se definesc coeficientii A, B, C, D din ecuatia planului de decupare GL_CLIP_PLANE3, ecuatia: -y=1
	GLdouble eqn3[4] = { 0.0, -1.0, 0.0, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(rx, 1, 0, 0);
	glRotatef(ry, 0, 1, 0);
	glRotatef(rz, 0, 0, 1);

	/*    se defineste planul de decupare  GL_CLIP_PLANE0    */
	glClipPlane(GL_CLIP_PLANE0, eqn0);
	/*    se activeaza planul de decupare  GL_CLIP_PLANE0    */
	glEnable(GL_CLIP_PLANE0);

	//glClipPlane(GL_CLIP_PLANE1, eqn1);
	//glEnable(GL_CLIP_PLANE1);

	//glClipPlane(GL_CLIP_PLANE2, eqn2);
	//glEnable(GL_CLIP_PLANE2);

	//glClipPlane(GL_CLIP_PLANE3, eqn3);
	//glEnable(GL_CLIP_PLANE3);

	glRotatef(90.0, 1.0, 1.0, 0.0);
	auxSolidSphere(2.0);
	glPopMatrix();
	glFlush();
}

void myInit() {
	initLights();
	glEnable(GL_DEPTH_TEST);
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH);
	auxInitPosition(0, 0, 800, 600);
	auxInitWindow("Plane de decupare");
	myInit();

	auxKeyFunc(AUX_q, rot_x_up);
	auxKeyFunc(AUX_a, rot_x_down);
	auxKeyFunc(AUX_w, rot_y_up);
	auxKeyFunc(AUX_s, rot_y_down);
	auxKeyFunc(AUX_e, rot_z_up);
	auxKeyFunc(AUX_d, rot_z_down);

	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
