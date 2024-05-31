#include "GLOS.h"

#include "gl.h"
#include "glu.h"
#include "glut.h"
#include "glaux.h"

#include <math.h>
#include <stdio.h>
#include <stdbool.h>

const int x = 0, y = 1, z = 2, w = 3; // used only for indexing
const int A = 0, B = 1, C = 2, D = 3; // used only for indexing

static float lightSourcePosition[4] = { -60, 50, -40, 1 };
static float modelX = 0;
static float modelY = -30;
static float modelZ = 0;
static float angle = 0;
static float unghiRoti = 0;
static float rotX = 0;
static float rotY = 0;
static float rotZ = 0;
static float viz = 1;

GLfloat punctePlanIarba[][3] = {
	{ -1500.0f, -60.0f, -1500.0f },
	{ -1500.0f, -60.0f, 1500.0f },
	{ 1500.0f, -60.0f, 1500.0f } ,
	{ 1500.0f, -60.0f, -1500.0f }
};

float coeficientiPlanIarba[4];
float matriceUmbrire[4][4];

void CALLBACK mutaSursaFata() {
	if (lightSourcePosition[z] < 100) {
		lightSourcePosition[z] += 5;
	}
}

void CALLBACK mutaSursaSpate() {
	if (lightSourcePosition[z] > -100) {
		lightSourcePosition[z] -= 5;
	}
}

void CALLBACK mutaSursaDreapta() {
	if (lightSourcePosition[x] < 100) {
		lightSourcePosition[x] += 5;
	}
}

void CALLBACK mutaSursaStanga() {
	if (lightSourcePosition[x] > -100) {
		lightSourcePosition[x] -= 5;
	}
}

void CALLBACK rotireDreapta() {
	angle -= 2;
}

void CALLBACK rotireStanga() {
	angle += 2;
}

void CALLBACK mutaStanga()
{
	modelX = modelX - 2;
}

void CALLBACK mutaDreapta()
{
	modelX = modelX + 2;
}
void CALLBACK mutaJos()
{
	modelZ = modelZ + 2;
}

void CALLBACK mutaSus()
{
	modelZ = modelZ - 2;
}
void CALLBACK inaltimeJos()
{
	modelY = modelY - 2;
}

void CALLBACK inaltimeSus()
{
	modelY = modelY + 2;
}
void CALLBACK rotireX()
{
	rotX = rotX - 2;
}

void CALLBACK rotirex()
{
	rotX = rotX + 2;
}
void CALLBACK rotireY()
{
	rotY = rotY - 2;
}

void CALLBACK rotirey()
{
	rotY = rotY + 2;
}
void CALLBACK rotireZ()
{
	rotZ = rotZ - 2;
}

void CALLBACK rotirez()
{
	rotZ = rotZ + 2;
}

void CALLBACK fViz()
{
	viz = !viz;
}



void computePlaneCoefficientsFromPoints(float points[3][3]) {
	// calculeaza 2 vectori din 3 puncte
	float v1[3]{ points[0][x] - points[1][x], points[0][y] - points[1][y], points[0][z] - points[1][z] };
	float v2[3]{ points[1][x] - points[2][x], points[1][y] - points[2][y], points[1][z] - points[2][z] };

	// produsul vectorial al celor 2 vectori => al 3lea vector cu componentele A,B,C chiar coef din ec. planului
	coeficientiPlanIarba[A] = v1[y] * v2[z] - v1[z] * v2[y];
	coeficientiPlanIarba[B] = v1[z] * v2[x] - v1[x] * v2[z];
	coeficientiPlanIarba[C] = v1[x] * v2[y] - v1[y] * v2[x];

	// determinam D - ecuatia planului in punctul random ales trebuie sa fie zero
	int randomPoint = 1; // poate fi orice punct de pe planul ierbii, asa ca alegem unul din cele 3 folosite pentru calcule
	coeficientiPlanIarba[D] =
		-(coeficientiPlanIarba[A] * points[randomPoint][x] +
			coeficientiPlanIarba[B] * points[randomPoint][y] +
			coeficientiPlanIarba[C] * points[randomPoint][z]);
}

void computeShadowMatrix(float points[3][3], float lightSourcePosition[4]) {
	// determina coef planului	
	computePlaneCoefficientsFromPoints(points);

	// temp = AxL + ByL + CzL + Dw
	float temp =
		coeficientiPlanIarba[A] * lightSourcePosition[x] +
		coeficientiPlanIarba[B] * lightSourcePosition[y] +
		coeficientiPlanIarba[C] * lightSourcePosition[z] +
		coeficientiPlanIarba[D] * lightSourcePosition[w];

	//prima coloana
	matriceUmbrire[0][0] = temp - coeficientiPlanIarba[A] * lightSourcePosition[x];
	matriceUmbrire[1][0] = 0.0f - coeficientiPlanIarba[B] * lightSourcePosition[x];
	matriceUmbrire[2][0] = 0.0f - coeficientiPlanIarba[C] * lightSourcePosition[x];
	matriceUmbrire[3][0] = 0.0f - coeficientiPlanIarba[D] * lightSourcePosition[x];
	//a 2a coloana
	matriceUmbrire[0][1] = 0.0f - coeficientiPlanIarba[A] * lightSourcePosition[y];
	matriceUmbrire[1][1] = temp - coeficientiPlanIarba[B] * lightSourcePosition[y];
	matriceUmbrire[2][1] = 0.0f - coeficientiPlanIarba[C] * lightSourcePosition[y];
	matriceUmbrire[3][1] = 0.0f - coeficientiPlanIarba[D] * lightSourcePosition[y];
	//a 3a coloana
	matriceUmbrire[0][2] = 0.0f - coeficientiPlanIarba[A] * lightSourcePosition[z];
	matriceUmbrire[1][2] = 0.0f - coeficientiPlanIarba[B] * lightSourcePosition[z];
	matriceUmbrire[2][2] = temp - coeficientiPlanIarba[C] * lightSourcePosition[z];
	matriceUmbrire[3][2] = 0.0f - coeficientiPlanIarba[D] * lightSourcePosition[z];
	//a 4a coloana
	matriceUmbrire[0][3] = 0.0f - coeficientiPlanIarba[A] * lightSourcePosition[w];
	matriceUmbrire[1][3] = 0.0f - coeficientiPlanIarba[B] * lightSourcePosition[w];
	matriceUmbrire[2][3] = 0.0f - coeficientiPlanIarba[C] * lightSourcePosition[w];
	matriceUmbrire[3][3] = temp - coeficientiPlanIarba[D] * lightSourcePosition[w];
}

void myInit(void) {
	glClearColor(0.53, 0.81, 0.92, 1.0); 

	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// sursa lumina
	float lightAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lightSourcePosition);

	// material
	float materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float materialShininess[] = { 128.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);

	// use current color set with glColor3f() to directly set the material ambient and diffuse
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);
}


void desenareTren(bool umbra)
{
	if (umbra == false) glColor3f(0.2, 0.2, 0.2);
	GLfloat vertices[][3] = {
	{ 40, -20,  10},
	{ 40, -20, -10},
	{ 40, -30,  10},
	{ 40, -30, -10},
	{-40, -20,  10},
	{-40, -20, -10},
	{-40, -30,  10},
	{-40, -30, -10}
	};

	glBegin(GL_QUADS);
	glVertex3fv(vertices[0]); glVertex3fv(vertices[2]); glVertex3fv(vertices[6]); glVertex3fv(vertices[4]);
	glVertex3fv(vertices[1]); glVertex3fv(vertices[5]); glVertex3fv(vertices[7]); glVertex3fv(vertices[3]);
	glVertex3fv(vertices[0]); glVertex3fv(vertices[4]); glVertex3fv(vertices[5]); glVertex3fv(vertices[1]);
	glVertex3fv(vertices[2]); glVertex3fv(vertices[3]); glVertex3fv(vertices[7]); glVertex3fv(vertices[6]);
	glVertex3fv(vertices[0]); glVertex3fv(vertices[1]); glVertex3fv(vertices[3]); glVertex3fv(vertices[2]);
	glVertex3fv(vertices[4]); glVertex3fv(vertices[6]); glVertex3fv(vertices[7]); glVertex3fv(vertices[5]);
	glEnd();

	if (umbra == false) glColor3f(0.3, 0.3, 0.3);
	GLfloat vertices1[][3] = {
		{  40, -15,  15},
		{  40, -15, -15},
		{  40, -20,  15},
		{  40, -20, -15},
		{ -35, -15,  15},
		{ -35, -15, -15},
		{ -35, -20,  15},
		{ -35, -20, -15}
	};

	glBegin(GL_QUADS);
	glVertex3fv(vertices1[0]); glVertex3fv(vertices1[2]); glVertex3fv(vertices1[6]); glVertex3fv(vertices1[4]);
	glVertex3fv(vertices1[1]); glVertex3fv(vertices1[5]); glVertex3fv(vertices1[7]); glVertex3fv(vertices1[3]);
	glVertex3fv(vertices1[0]); glVertex3fv(vertices1[4]); glVertex3fv(vertices1[5]); glVertex3fv(vertices1[1]);
	glVertex3fv(vertices1[2]); glVertex3fv(vertices1[3]); glVertex3fv(vertices1[7]); glVertex3fv(vertices1[6]);
	glVertex3fv(vertices1[0]); glVertex3fv(vertices1[1]); glVertex3fv(vertices1[3]); glVertex3fv(vertices1[2]);
	glVertex3fv(vertices1[4]); glVertex3fv(vertices1[6]); glVertex3fv(vertices1[7]); glVertex3fv(vertices1[5]);
	glEnd();

	if (umbra == false) glColor3f(0.2, 0.2, 0.2);
	GLfloat vertices2[][3] = {
		{ -35, -10,  10},
		{ -35, -10, -10},
		{ -35, -20,  10},
		{ -35, -20, -10},
		{ -40, -10,  10},
		{ -40, -10, -10},
		{ -40, -20,  10},
		{ -40, -20, -10}
	};

	glBegin(GL_QUADS);
	glVertex3fv(vertices2[0]); glVertex3fv(vertices2[2]); glVertex3fv(vertices2[6]); glVertex3fv(vertices2[4]);
	glVertex3fv(vertices2[1]); glVertex3fv(vertices2[5]); glVertex3fv(vertices2[7]); glVertex3fv(vertices2[3]);
	glVertex3fv(vertices2[0]); glVertex3fv(vertices2[4]); glVertex3fv(vertices2[5]); glVertex3fv(vertices2[1]);
	glVertex3fv(vertices2[2]); glVertex3fv(vertices2[3]); glVertex3fv(vertices2[7]); glVertex3fv(vertices2[6]);
	glVertex3fv(vertices2[0]); glVertex3fv(vertices2[1]); glVertex3fv(vertices2[3]); glVertex3fv(vertices2[2]);
	glVertex3fv(vertices2[4]); glVertex3fv(vertices2[6]); glVertex3fv(vertices2[7]); glVertex3fv(vertices2[5]);
	glEnd();

	if (umbra == false) glColor3f(0.4, 0.4, 0.4);
	GLfloat vertices3[][3] = {
	{ -30,  10,  15},
	{ -30,  10, -15},
	{ -30, -15,  15},
	{ -30, -15, -15},
	{ -35,  10,  15},
	{ -35,  10, -15},
	{ -35, -15,  15},
	{ -35, -15, -15}
	};

	glBegin(GL_QUADS);
	glVertex3fv(vertices3[0]); glVertex3fv(vertices3[2]); glVertex3fv(vertices3[6]); glVertex3fv(vertices3[4]);
	glVertex3fv(vertices3[1]); glVertex3fv(vertices3[5]); glVertex3fv(vertices3[7]); glVertex3fv(vertices3[3]);
	glVertex3fv(vertices3[0]); glVertex3fv(vertices3[4]); glVertex3fv(vertices3[5]); glVertex3fv(vertices3[1]);
	glVertex3fv(vertices3[2]); glVertex3fv(vertices3[3]); glVertex3fv(vertices3[7]); glVertex3fv(vertices3[6]);
	glVertex3fv(vertices3[0]); glVertex3fv(vertices3[1]); glVertex3fv(vertices3[3]); glVertex3fv(vertices3[2]);
	glVertex3fv(vertices3[4]); glVertex3fv(vertices3[6]); glVertex3fv(vertices3[7]); glVertex3fv(vertices3[5]);
	glEnd();

	GLfloat vertices4[][3] = {
		{ -10,  10,  15},
		{ -10,  10, -15},
		{ -10, -15,  15},
		{ -10, -15, -15},
		{ -15,  10,  15},
		{ -15,  10, -15},
		{ -15, -15,  15},
		{ -15, -15, -15}
	};

	glBegin(GL_QUADS);
	glVertex3fv(vertices4[0]); glVertex3fv(vertices4[2]); glVertex3fv(vertices4[6]); glVertex3fv(vertices4[4]);
	glVertex3fv(vertices4[1]); glVertex3fv(vertices4[5]); glVertex3fv(vertices4[7]); glVertex3fv(vertices4[3]);
	glVertex3fv(vertices4[0]); glVertex3fv(vertices4[4]); glVertex3fv(vertices4[5]); glVertex3fv(vertices4[1]);
	glVertex3fv(vertices4[2]); glVertex3fv(vertices4[3]); glVertex3fv(vertices4[7]); glVertex3fv(vertices4[6]);
	glVertex3fv(vertices4[0]); glVertex3fv(vertices4[1]); glVertex3fv(vertices4[3]); glVertex3fv(vertices4[2]);
	glVertex3fv(vertices4[4]); glVertex3fv(vertices4[6]); glVertex3fv(vertices4[7]); glVertex3fv(vertices4[5]);
	glEnd();

	GLfloat vertices5[][3] = {
		{ -30,  10,  15 },
		{ -30,  10,  10 },
		{ -30, -15,  15 },
		{ -30, -15,  10 },
		{ -10,  10,  15 },
		{ -10,  10,  10 },
		{ -10, -15,  15 },
		{ -10, -15,  10 }
	};

	glBegin(GL_QUADS);
	glVertex3fv(vertices5[0]); glVertex3fv(vertices5[2]); glVertex3fv(vertices5[6]); glVertex3fv(vertices5[4]);
	glVertex3fv(vertices5[1]); glVertex3fv(vertices5[5]); glVertex3fv(vertices5[7]); glVertex3fv(vertices5[3]);
	glVertex3fv(vertices5[0]); glVertex3fv(vertices5[4]); glVertex3fv(vertices5[5]); glVertex3fv(vertices5[1]);
	glVertex3fv(vertices5[2]); glVertex3fv(vertices5[3]); glVertex3fv(vertices5[7]); glVertex3fv(vertices5[6]);
	glVertex3fv(vertices5[0]); glVertex3fv(vertices5[1]); glVertex3fv(vertices5[3]); glVertex3fv(vertices5[2]);
	glVertex3fv(vertices5[4]); glVertex3fv(vertices5[6]); glVertex3fv(vertices5[7]); glVertex3fv(vertices5[5]);
	glEnd();

	GLfloat vertices6[][3] = {
		{ -30,  10, -15 },
		{ -30,  10, -10 },
		{ -30, -15, -15 },
		{ -30, -15, -10 },
		{ -10,  10, -15 },
		{ -10,  10, -10 },
		{ -10, -15, -15 },
		{ -10, -15, -10 }
	};

	glBegin(GL_QUADS);
	glVertex3fv(vertices6[0]); glVertex3fv(vertices6[2]); glVertex3fv(vertices6[6]); glVertex3fv(vertices6[4]);
	glVertex3fv(vertices6[1]); glVertex3fv(vertices6[5]); glVertex3fv(vertices6[7]); glVertex3fv(vertices6[3]);
	glVertex3fv(vertices6[0]); glVertex3fv(vertices6[4]); glVertex3fv(vertices6[5]); glVertex3fv(vertices6[1]);
	glVertex3fv(vertices6[2]); glVertex3fv(vertices6[3]); glVertex3fv(vertices6[7]); glVertex3fv(vertices6[6]);
	glVertex3fv(vertices6[0]); glVertex3fv(vertices6[1]); glVertex3fv(vertices6[3]); glVertex3fv(vertices6[2]);
	glVertex3fv(vertices6[4]); glVertex3fv(vertices6[6]); glVertex3fv(vertices6[7]); glVertex3fv(vertices6[5]);
	glEnd();

	if (umbra == false) glColor3f(0.5, 0.5, 0.5);
	GLfloat vertices7[][3] = {
		{ -30,  30, -15 },
		{ -30,  30, -10 },
		{ -30,  10, -15 },
		{ -30,  10, -10 },
		{ -35,  30, -15 },
		{ -35,  30, -10 },
		{ -35,  10, -15 },
		{ -35,  10, -10 }
	};

	glBegin(GL_QUADS);
	glVertex3fv(vertices7[0]); glVertex3fv(vertices7[2]); glVertex3fv(vertices7[6]); glVertex3fv(vertices7[4]);
	glVertex3fv(vertices7[1]); glVertex3fv(vertices7[5]); glVertex3fv(vertices7[7]); glVertex3fv(vertices7[3]);
	glVertex3fv(vertices7[0]); glVertex3fv(vertices7[4]); glVertex3fv(vertices7[5]); glVertex3fv(vertices7[1]);
	glVertex3fv(vertices7[2]); glVertex3fv(vertices7[3]); glVertex3fv(vertices7[7]); glVertex3fv(vertices7[6]);
	glVertex3fv(vertices7[0]); glVertex3fv(vertices7[1]); glVertex3fv(vertices7[3]); glVertex3fv(vertices7[2]);
	glVertex3fv(vertices7[4]); glVertex3fv(vertices7[6]); glVertex3fv(vertices7[7]); glVertex3fv(vertices7[5]);
	glEnd();

	GLfloat vertices8[][3] = {
		{ -30,  30,  15 },
		{ -30,  30,  10 },
		{ -30,  10,  15 },
		{ -30,  10,  10 },
		{ -35,  30,  15 },
		{ -35,  30,  10 },
		{ -35,  10,  15 },
		{ -35,  10,  10 }
	};

	glBegin(GL_QUADS);
	glVertex3fv(vertices8[0]); glVertex3fv(vertices8[2]); glVertex3fv(vertices8[6]); glVertex3fv(vertices8[4]);
	glVertex3fv(vertices8[1]); glVertex3fv(vertices8[5]); glVertex3fv(vertices8[7]); glVertex3fv(vertices8[3]);
	glVertex3fv(vertices8[0]); glVertex3fv(vertices8[4]); glVertex3fv(vertices8[5]); glVertex3fv(vertices8[1]);
	glVertex3fv(vertices8[2]); glVertex3fv(vertices8[3]); glVertex3fv(vertices8[7]); glVertex3fv(vertices8[6]);
	glVertex3fv(vertices8[0]); glVertex3fv(vertices8[1]); glVertex3fv(vertices8[3]); glVertex3fv(vertices8[2]);
	glVertex3fv(vertices8[4]); glVertex3fv(vertices8[6]); glVertex3fv(vertices8[7]); glVertex3fv(vertices8[5]);
	glEnd();

	GLfloat vertices9[][3] = {
		{ -10,  30,  15 },
		{ -10,  30,  10 },
		{ -10,  10,  15 },
		{ -10,  10,  10 },
		{ -15,  30,  15 },
		{ -15,  30,  10 },
		{ -15,  10,  15 },
		{ -15,  10,  10 }
	};

	glBegin(GL_QUADS);
	glVertex3fv(vertices9[0]); glVertex3fv(vertices9[2]); glVertex3fv(vertices9[6]); glVertex3fv(vertices9[4]);
	glVertex3fv(vertices9[1]); glVertex3fv(vertices9[5]); glVertex3fv(vertices9[7]); glVertex3fv(vertices9[3]);
	glVertex3fv(vertices9[0]); glVertex3fv(vertices9[4]); glVertex3fv(vertices9[5]); glVertex3fv(vertices9[1]);
	glVertex3fv(vertices9[2]); glVertex3fv(vertices9[3]); glVertex3fv(vertices9[7]); glVertex3fv(vertices9[6]);
	glVertex3fv(vertices9[0]); glVertex3fv(vertices9[1]); glVertex3fv(vertices9[3]); glVertex3fv(vertices9[2]);
	glVertex3fv(vertices9[4]); glVertex3fv(vertices9[6]); glVertex3fv(vertices9[7]); glVertex3fv(vertices9[5]);
	glEnd();

	GLfloat vertices10[][3] = {
		{ -10,  30,  -15 },
		{ -10,  30,  -10 },
		{ -10,  10,  -15 },
		{ -10,  10,  -10 },
		{ -15,  30,  -15 },
		{ -15,  30,  -10 },
		{ -15,  10,  -15 },
		{ -15,  10,  -10 }
	};

	glBegin(GL_QUADS);
	glVertex3fv(vertices10[0]); glVertex3fv(vertices10[2]); glVertex3fv(vertices10[6]); glVertex3fv(vertices10[4]);
	glVertex3fv(vertices10[1]); glVertex3fv(vertices10[5]); glVertex3fv(vertices10[7]); glVertex3fv(vertices10[3]);
	glVertex3fv(vertices10[0]); glVertex3fv(vertices10[4]); glVertex3fv(vertices10[5]); glVertex3fv(vertices10[1]);
	glVertex3fv(vertices10[2]); glVertex3fv(vertices10[3]); glVertex3fv(vertices10[7]); glVertex3fv(vertices10[6]);
	glVertex3fv(vertices10[0]); glVertex3fv(vertices10[1]); glVertex3fv(vertices10[3]); glVertex3fv(vertices10[2]);
	glVertex3fv(vertices10[4]); glVertex3fv(vertices10[6]); glVertex3fv(vertices10[7]); glVertex3fv(vertices10[5]);
	glEnd();

	if (umbra == false) glColor3f(0.6, 0.6, 0.6);
	GLfloat vertices11[][3] = {
		{ -15,  35,  -10 },
		{ -15,  35,   10 },
		{ -10,  30,  -15 },
		{ -10,  30,   15 },
		{ -30,  35,  -10 },
		{ -30,  35,   10 },
		{ -35,  30,  -15 },
		{ -35,  30,   15 }
	};

	glBegin(GL_QUADS);
	glVertex3fv(vertices11[0]); glVertex3fv(vertices11[2]); glVertex3fv(vertices11[6]); glVertex3fv(vertices11[4]);
	glVertex3fv(vertices11[1]); glVertex3fv(vertices11[5]); glVertex3fv(vertices11[7]); glVertex3fv(vertices11[3]);
	glVertex3fv(vertices11[0]); glVertex3fv(vertices11[4]); glVertex3fv(vertices11[5]); glVertex3fv(vertices11[1]);
	glVertex3fv(vertices11[2]); glVertex3fv(vertices11[3]); glVertex3fv(vertices11[7]); glVertex3fv(vertices11[6]);
	glVertex3fv(vertices11[0]); glVertex3fv(vertices11[1]); glVertex3fv(vertices11[3]); glVertex3fv(vertices11[2]);
	glVertex3fv(vertices11[4]); glVertex3fv(vertices11[6]); glVertex3fv(vertices11[7]); glVertex3fv(vertices11[5]);
	glEnd();

	if (umbra == false) glColor3f(0.8, 0.8, 0.8);
	GLUquadric* cilindru = gluNewQuadric();
	gluQuadricDrawStyle(cilindru, GLU_FILL);
	glRotatef(270, 0, 1, 0);
	glTranslatef(0, -5, -30);
	gluCylinder(cilindru, 10, 10, 40, 20, 20);
	gluDisk(cilindru, 0, 10, 20, 20);
	glTranslatef(0, 5, 30);
	glRotatef(-270, 0, 1, 0);
	gluDeleteQuadric(cilindru);

	if (umbra == false) glColor3f(0.4, 0.2, 0.1);
	glTranslatef(-27, -30, 15);
	glRotatef(unghiRoti, 0, 0, 1);
	auxSolidTorus(3, 7);
	glBegin(GL_LINES);
	for (int i = 0; i <= 360; i += 45) {
		float x = 7 * cos(i * 3.14 / 180);
		float y = 7 * sin(i * 3.14 / 180);
		glVertex3f(0, 0, 0);
		glVertex3f(x, y, 0);
	}
	glEnd();
	glRotatef(-unghiRoti, 0, 0, 1);
	glTranslatef(27, 30, -15);

	glTranslatef(-5, -30, 15);
	glRotatef(unghiRoti, 0, 0, 1);
	auxSolidTorus(3, 7);
	glBegin(GL_LINES);
	for (int i = 0; i <= 360; i += 45) {
		float x = 7 * cos(i * 3.14 / 180);
		float y = 7 * sin(i * 3.14 / 180);
		glVertex3f(0, 0, 0);
		glVertex3f(x, y, 0);
	}
	glEnd();
	glRotatef(-unghiRoti, 0, 0, 1);
	glTranslatef(5, 30, -15);

	glTranslatef(27, -30, 15);
	glRotatef(unghiRoti, 0, 0, 1);
	auxSolidTorus(3, 7);
	glBegin(GL_LINES);
	for (int i = 0; i <= 360; i += 45) {
		float x = 7 * cos(i * 3.14 / 180);
		float y = 7 * sin(i * 3.14 / 180);
		glVertex3f(0, 0, 0);
		glVertex3f(x, y, 0);
	}
	glEnd();
	glRotatef(-unghiRoti, 0, 0, 1);
	glTranslatef(-27, 30, -15);

	glTranslatef(-27, -30, -15);
	glRotatef(unghiRoti, 0, 0, 1);
	auxSolidTorus(3, 7);
	glBegin(GL_LINES);
	for (int i = 0; i <= 360; i += 45) {
		float x = 7 * cos(i * 3.14 / 180);
		float y = 7 * sin(i * 3.14 / 180);
		glVertex3f(0, 0, 0);
		glVertex3f(x, y, 0);
	}
	glEnd();
	glRotatef(-unghiRoti, 0, 0, 1);
	glTranslatef(27, 30, 15);

	glTranslatef(-5, -30, -15);
	glRotatef(unghiRoti, 0, 0, 1);
	auxSolidTorus(3, 7);
	glBegin(GL_LINES);
	for (int i = 0; i <= 360; i += 45) {
		float x = 7 * cos(i * 3.14 / 180);
		float y = 7 * sin(i * 3.14 / 180);
		glVertex3f(0, 0, 0);
		glVertex3f(x, y, 0);
	}
	glEnd();
	glRotatef(-unghiRoti, 0, 0, 1);
	glTranslatef(5, 30, 15);

	glTranslatef(27, -30, -15);
	glRotatef(unghiRoti, 0, 0, 1);
	auxSolidTorus(3, 7);
	glBegin(GL_LINES);
	for (int i = 0; i <= 360; i += 45) {
		float x = 7 * cos(i * 3.14 / 180);
		float y = 7 * sin(i * 3.14 / 180);
		glVertex3f(0, 0, 0);
		glVertex3f(x, y, 0);
	}
	glEnd();
	glRotatef(-unghiRoti, 0, 0, 1);
	glTranslatef(-27, 30, 15);
}


void desenareModel(bool umbra) {
	if (umbra) {
		glColor3f(0, 0.15, 0.05);
	}

	glPushMatrix();
	glTranslatef(modelX, modelY, modelZ);
	glRotatef(angle, 0, 1, 0);
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
	glRotatef(rotZ, 0, 0, 1);

	glTranslatef(0, 20, 0);
	desenareTren(umbra);
	glTranslatef(0, -20, 0);

	glPopMatrix();
}

void desenareIarba() {
	glPushMatrix();
	glColor3f(0, 0.3, 0);
	glTranslatef(0, -0.1, 0);
	glBegin(GL_QUADS);
	{
		glNormal3f(0, 1, 0);
		for (int i = 0; i < 4; i++) {
			glVertex3fv(punctePlanIarba[i]);
		}
	}
	glEnd();
	glPopMatrix();
}

void deseneazaLumina()
{
	glPushMatrix();
	glTranslatef(lightSourcePosition[x], lightSourcePosition[y], lightSourcePosition[z]);
	glColor3f(1.0, 0.9, 0);
	auxSolidSphere(3);
	glPopMatrix();
}

void CALLBACK display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0, 0, -150);
	glRotatef(15, 1, 0, 0);

	if (viz) 
		gluLookAt(0.0, 0.0, 9.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else 
		gluLookAt(0.0, 0.0, -9.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	


	computeShadowMatrix(punctePlanIarba, lightSourcePosition);

	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, lightSourcePosition);
	desenareIarba();
	desenareModel(false);
	glPopMatrix();

	//deseneaza umbra
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glMultMatrixf((GLfloat*)matriceUmbrire); // se inmulteste matricea curenta cu matricea de umbrire
	desenareModel(true);
	glPopMatrix();
	deseneazaLumina();

	glEnable(GL_LIGHTING);

	auxSwapBuffers();
}
void CALLBACK IdleFunction()
{
	unghiRoti -= 2;
	display();
	Sleep(1000 / 60);
}
void CALLBACK myReshape(GLsizei w, GLsizei h) {
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0 * (GLfloat)w / (GLfloat)h, 0.5, 300.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	auxInitDisplayMode(AUX_DOUBLE | AUX_DEPTH24 | AUX_RGB);
	auxInitPosition(10, 10, 1200, 800);
	auxKeyFunc(AUX_RIGHT, mutaDreapta);
	auxKeyFunc(AUX_LEFT, mutaStanga);
	auxKeyFunc(AUX_UP, mutaSus);
	auxKeyFunc(AUX_DOWN, mutaJos);
	auxKeyFunc(AUX_o, inaltimeSus);
	auxKeyFunc(AUX_l, inaltimeJos);
	auxKeyFunc(AUX_O, inaltimeSus);
	auxKeyFunc(AUX_L, inaltimeJos);
	auxKeyFunc(AUX_i, rotireX);
	auxKeyFunc(AUX_k, rotirex);
	auxKeyFunc(AUX_I, rotireX);
	auxKeyFunc(AUX_K, rotirex);
	auxKeyFunc(AUX_u, rotireY);
	auxKeyFunc(AUX_j, rotirey);
	auxKeyFunc(AUX_U, rotireY);
	auxKeyFunc(AUX_J, rotirey);
	auxKeyFunc(AUX_y, rotireZ);
	auxKeyFunc(AUX_h, rotirez);
	auxKeyFunc(AUX_Y, rotireZ);
	auxKeyFunc(AUX_H, rotirez);
	auxKeyFunc(AUX_f, fViz);
	auxKeyFunc(AUX_F, fViz);

	auxKeyFunc(AUX_w, mutaSursaSpate);
	auxKeyFunc(AUX_s, mutaSursaFata);
	auxKeyFunc(AUX_d, mutaSursaDreapta);
	auxKeyFunc(AUX_a, mutaSursaStanga);
	auxKeyFunc(AUX_W, mutaSursaSpate);
	auxKeyFunc(AUX_S, mutaSursaFata);
	auxKeyFunc(AUX_D, mutaSursaDreapta);
	auxKeyFunc(AUX_A, mutaSursaStanga);
	auxInitWindow("Umbra");
	myInit();
	auxReshapeFunc(myReshape);
	auxIdleFunc(IdleFunction);
	auxMainLoop(display);
	return 0;
}