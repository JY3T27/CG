#include <windows.h>
#include <stdlib.h>
#include <GL\gl.h>
#include <gl\glu.h>
#include <GL\glut.h>

#define SCREENWIDTH 500
#define SCREENHEIGHT 500

void rectangle(int x, int y, int w, int h) {
	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	glVertex2d(x + w, y);
	glVertex2d(x + w, y + h);
	glVertex2d(x, y + h);
	glEnd();
}

void person(int x, int y, int w) {
	int h = 1.2 * w;
	
	//head
	glColor3ub(255, 219, 172);
	rectangle(x, y + h, w, 0.5 * h);

	//eyes & mouth
	glColor3ub(0, 0, 0);
	rectangle(x + w / 14, y + 1.3 * h, w / 8, w / 10);
	rectangle(x + (w * 2) / 4, y + 1.3 * h, w / 8, w / 10);
	rectangle(x + w / 5, y + 1.1 * h, w / 4, w / 10);
	//smile
	rectangle(x + w / 2.4, y + 1.12 * h, w / 10, w / 10);

	//hair
	glColor3ub(80, 80, 80);
	rectangle(x - w / 6, y + 1.5 * h, w + w / 6, 0.15 * h);
	rectangle(x + w / 1.1, y + 1.03 * h, w / 6, 0.6 * h);

	//body
	glColor3ub(255, 255, 255);
	rectangle(x, y, w, h);
	glColor3ub(80, 180, 255);
	rectangle(x, y, w / 3, h);
	rectangle(x + (w - w / 3), y, w / 3, h);

	//left hand
	glColor3ub(255, 219, 172);
	rectangle(x + w * 1.01, y, w / 4, h);
	glColor3ub(80, 180, 255);
	rectangle(x + w * 1.01, y + h / 3, w / 4, (h * 2) / 3);
	//right hand
	glColor3ub(255, 219, 172);
	rectangle(x - (w / 4) * 1.01, y, w / 4, h);
	glColor3ub(80, 180, 255);
	rectangle(x - (w / 4) * 1.01, y + h / 3, w / 4, (h * 2) / 3);

	//legs
	glColor3ub(165, 42, 42);
	rectangle(x + w / 6, y - h / 2, w / 4, h / 2);
	rectangle(x + (w * 2) / 3, y - h / 2, w / 4, h / 2);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	person(125, 140, 150);

	glFlush();
}

void initGL() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREENWIDTH, 0, SCREENHEIGHT);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
	glutCreateWindow("Normal Person");
	glutDisplayFunc(display);

	initGL();
	glutMainLoop();
}
