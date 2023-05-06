#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>

#define SCREENWIDTH 1600
#define SCREENHEIGHT 900
#define PI 3.1415926535897932384626433832795
#define FPS 60
#define cloudSpeed 0.5
#define lightSpeed 10
#define gravity 50

//base shapes
void drawRectangle(int x, int y, int w, int h);
void rectangle(int x, int y, int w, int h);
void oval(int x, int y, float rX, float rY);
void circle(int x, int y, float r);
void halfCircle(float x, float y, float r);
void lines(float x1, float y1, float x2, float y2);
void triangle(float x, float y, float l);

//forming objects 
void sky();
void ground();
void mountain();
void clouds(int xPosition);
void background();
void redApple(int x, int y);
void greenApple(int x, int y);
void drawTable(int x, int y);
void appleStall(int x, int y);
void guard(float x, float y);
void person(int x, int y, int w);
void pinnochio(float x, float y, float width, float height, float speedX, float speedY, float scaleX, float scaleY, float nose_length);
void light(int x, int y, int w, int h);
void drawLightShadow(int x, int y, int w, int h);

void display();
void initGL();
void timer(int);

float cloudXposition = 0.0;
int cloudState = 1;
float lightYposition = 1600;
float pinnoYposition = 1600;
float scale_x = -1 ;
float scale_y = 1 ;
int timer1 = 0;

bool lightReachGround = false;
bool pinnoReachGround = false;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
    glutCreateWindow("CG Project");

    glutDisplayFunc(display);
    glutTimerFunc(1000, timer, 0);

    initGL();
    
    //Start the main loop
    glutMainLoop();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(10.0);
    glLineWidth(4.0);

    background();
    appleStall(350, 100);
    //person(1350, 200, 150);
    light(700, lightYposition, 250, 800);
    if (lightReachGround != false) {
        drawLightShadow(700, lightYposition, 250, 800);
    }
    //glScalef(-1.0, 1.0, 1.0);
    pinnochio(-750, pinnoYposition, 100.0f, 50.0f, 0, 0, scale_x, scale_y, 0);

    glEnd();
    glFlush();
    glutSwapBuffers();
}

void initGL() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCREENWIDTH, 0, SCREENHEIGHT);
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);

    switch (cloudState) {
        case 1: 
            if (cloudXposition <= (1600 - SCREENWIDTH * 6 / 7)) {
                cloudXposition += cloudSpeed;
            }
            else {
                cloudState = 2;
            }
            break;
        case 2: 
            if (cloudXposition >= -(SCREENWIDTH / 6)) {
                cloudXposition -= cloudSpeed;
            }
            else {
                cloudState = 1;
            }
            break;
        default:
            break;
    }

    if (pinnoReachGround == false && lightReachGround == false && lightYposition > 500) {
        lightYposition -= lightSpeed;
    }
    if (pinnoReachGround == false && lightReachGround == false && lightYposition == 500)
    {
        lightYposition = 500;
        lightReachGround = true;
    }

    if (lightReachGround != false && pinnoYposition >= 350) {
        pinnoYposition -= gravity;
    }
    if (pinnoYposition == 350)
    {
        pinnoReachGround = true;
    }
    if (lightReachGround != false && pinnoReachGround != false && timer1 < 100) {
        timer1 += 1;
    }

    if (timer1 == 100) {
        lightReachGround = false;
    }

    if (pinnoReachGround != false && lightReachGround == false && lightYposition < 1600) {
        lightYposition += lightSpeed;
    }
    if (pinnoReachGround != false && lightReachGround == false && lightYposition == 1600)
    {
        lightYposition = 1600;
    }

}

void drawRectangle(int x, int y, int w, int h) {
    int w1 = x + w;
    int h1 = y + h;
    glBegin(GL_POLYGON);
    glVertex2d(x, y);
    glVertex2d(w1, y);
    glVertex2d(w1, h1);
    glVertex2d(x, h1);
    glEnd();
}

void rectangle(int x, int y, int w, int h) {
    int w2 = w / 2;
    int h2 = h / 2;
    glBegin(GL_QUADS);
    glVertex2i(x - w2, y - h2);
    glVertex2i(x - w2, y + h2);
    glVertex2i(x + w2, y + h2);
    glVertex2i(x + w2, y - h2);
    glEnd();
}

void oval(int x, int y, float rX, float rY) {
    float x1 = (float)x;
    float y1 = (float)y;
    float n = 50;
    float inc = (2 * PI) / n;
    glBegin(GL_POLYGON);
    for (float theta = 0.0; theta <= 2 * PI; theta += inc) {
        glVertex2f(rX * cos(theta) + x1, rY * sin(theta) + y1);
    }
    glEnd();
}

void circle(int x, int y, float r) {
    float x1 = (float)x;
    float y1 = (float)y;
    float n = 50;
    float inc = (2 * PI) / n;
    glBegin(GL_POLYGON);
    for (float theta = 0.0; theta <= 2 * PI; theta += inc) {
        glVertex2d(r * cos(theta) + x1, r * sin(theta) + y1);
    }
    glEnd();
}

void halfCircle(float x, float y, float r) {
    float n = 50;
    float inc = PI / n;
    glBegin(GL_POLYGON);
    for (float theta = 0.0; theta <= PI; theta += inc) {
        glVertex2d(r * cos(theta) + x, r * sin(theta) + y);
    }
    glEnd();
}

void lines(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

void triangle(float x, float y, float l) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x - l, y);
    glVertex2f(x + l, y);
    glVertex2f(x, y + l);
    glEnd();
}

void sky() {
    glColor3ub(135, 206, 235);
    rectangle(SCREENWIDTH / 2, SCREENHEIGHT * 6 / 10, SCREENWIDTH, SCREENHEIGHT * 4 / 5);
}

void ground() {
    glColor3ub(124, 252, 0);
    rectangle(SCREENWIDTH / 2, SCREENHEIGHT / 10, SCREENWIDTH, SCREENHEIGHT / 5);
}

void mountain() {
    glColor3ub(35, 144, 79);
    triangle(SCREENWIDTH * 3 / 7, SCREENHEIGHT / 6, SCREENHEIGHT / 2);
    glColor3ub(30, 196, 100);
    triangle(SCREENWIDTH / 8, SCREENHEIGHT / 6, SCREENHEIGHT / 2);
    glColor3ub(30, 196, 100);
    triangle(SCREENWIDTH * 7 / 8, SCREENHEIGHT / 6, SCREENHEIGHT / 2);
}

void clouds(int xPosition) {
    glColor3ub(236, 240, 241);
    circle(xPosition + (SCREENWIDTH / 6), SCREENHEIGHT * 3 / 4, 50);
    circle(xPosition + (SCREENWIDTH / 6 + 60), SCREENHEIGHT * 3 / 4 + 20, 70);
    circle(xPosition + (SCREENWIDTH / 6 + 120), SCREENHEIGHT * 3 / 4, 45);

    circle(xPosition + (SCREENWIDTH * 3 / 6), SCREENHEIGHT * 6 / 7, 50);
    circle(xPosition + (SCREENWIDTH * 3 / 6 + 60), SCREENHEIGHT * 6 / 7 + 20, 70);
    circle(xPosition + (SCREENWIDTH * 3 / 6 + 120), SCREENHEIGHT * 6 / 7, 45);

    circle(xPosition + (SCREENWIDTH * 5 / 6), SCREENHEIGHT * 5 / 7, 50);
    circle(xPosition + (SCREENWIDTH * 5 / 6 + 60), SCREENHEIGHT * 5 / 7 + 20, 70);
    circle(xPosition + (SCREENWIDTH * 5 / 6 + 120), SCREENHEIGHT * 5 / 7, 45);
}

void background() {
    sky();
    mountain();
    ground();
    clouds(cloudXposition);
}

void redApple(int x, int y) {
    glColor3ub(255, 0, 0);
    circle(x, y, 30);
    glColor3ub(150, 75, 0);
    rectangle(x, y + 23, 10, 30);
}

void greenApple(int x, int y) {
    glColor3ub(0, 255, 0);
    circle(x, y, 30);
    glColor3ub(150, 75, 0);
    rectangle(x, y + 23, 10, 30);
}

void drawTable(int x, int y) {
    //table base
    glColor3ub(150, 75, 0);
    rectangle(x, y + 100, 350, 150);

    //banner holder(left)
    glColor3ub(128, 128, 128);
    rectangle(x - 160, y + 250, 20, 150);

    //banner holder(right)
    glColor3ub(128, 128, 128);
    rectangle(x + 160, y + 250, 20, 150);

    //banner
    glColor3ub(255, 255, 255);
    rectangle(x, y + 350, 400, 50);
}

void appleStall(int x, int y) {
    drawTable(x, y);
    redApple(x - 115, y + 200);
    redApple(x - 50, y + 200);
    greenApple(x + 50, y + 200);
    greenApple(x + 115, y + 200);
}

void guard(float x, float y) {
    glColor3ub(244, 182, 108);
    rectangle(x, y - 70.0, 180.0, 130.0);
    rectangle(x, y - 70.0, 220.0, 50.0);
    rectangle(x, y - 140.0, 80.0, 20.0);
    rectangle(x, y - 280.0, 200.0, 40.0);

    glColor3ub(64, 64, 64);
    halfCircle(x, y + 12.0, 100.0);
    rectangle(x - 90, y - 220.0, 30.0, 130.0);
    rectangle(x + 90, y - 220.0, 30.0, 130.0);

    glColor3ub(54, 54, 54);
    rectangle(x, y, 300.0, 40.0);

    glColor3ub(25, 25, 25);
    circle(x - 40, y - 60, 25.0);
    circle(x + 40, y - 60, 25.0);
    lines(x - 90.0, y - 45.0, x - 60.0, y - 60.0);
    lines(x + 60.0, y - 60.0, x + 90.0, y - 45.0);
    lines(x - 40.0, y - 60.0, x + 40.0, y - 60.0);

    glColor3ub(212, 23, 23);
    lines(x - 40.0, y - 105.0, x + 40.0, y - 105.0);

    glColor3ub(255, 255, 255);
    rectangle(x, y - 235.0, 120.0, 170.0);

    glColor3ub(54, 54, 54);
    rectangle(x - 60, y - 235.0, 40.0, 170.0);
    rectangle(x + 60, y - 235.0, 40.0, 170.0);

    glColor3ub(173, 0, 0);
    rectangle(x, y - 225.0, 30.0, 150.0);
}

void person(int x, int y, int w) {
    int h = 1.2 * w;

    //head
    glColor3ub(255, 219, 172);
    drawRectangle(x, y + h, w, 0.5 * h);

    //eyes & mouth
    glColor3ub(0, 0, 0);
    drawRectangle(x + w / 14, y + 1.3 * h, w / 8, w / 10);
    drawRectangle(x + (w * 2) / 4, y + 1.3 * h, w / 8, w / 10);
    drawRectangle(x + w / 5, y + 1.1 * h, w / 4, w / 10);

    //smile
    drawRectangle(x + w / 2.4, y + 1.12 * h, w / 10, w / 10);

    //hair
    glColor3ub(80, 80, 80);
    drawRectangle(x - w / 6, y + 1.5 * h, w + w / 6, 0.15 * h);
    drawRectangle(x + w / 1.1, y + 1.03 * h, w / 6, 0.6 * h);

    //body
    glColor3ub(255, 255, 255);
    drawRectangle(x, y, w, h);
    glColor3ub(80, 180, 255);
    drawRectangle(x, y, w / 3, h);
    drawRectangle(x + (w - w / 3), y, w / 3, h);

    //left hand
    glColor3ub(255, 219, 172);
    drawRectangle(x + w * 1.01, y, w / 4, h);
    glColor3ub(80, 180, 255);
    drawRectangle(x + w * 1.01, y + h / 3, w / 4, (h * 2) / 3);

    //right hand
    glColor3ub(255, 219, 172);
    drawRectangle(x - (w / 4) * 1.01, y, w / 4, h);
    glColor3ub(80, 180, 255);
    drawRectangle(x - (w / 4) * 1.01, y + h / 3, w / 4, (h * 2) / 3);

    //legs
    glColor3ub(165, 42, 42);
    drawRectangle(x + w / 6, y - h / 2, w / 4, h / 2);
    drawRectangle(x + (w * 2) / 3, y - h / 2, w / 4, h / 2);
}

void pinnochio(float x, float y, float width, float height, float speedX, float speedY, float scaleX, float scaleY, float nose_length) 
{
    //hat
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.2f, 0.2f);
    glVertex2i(scaleX * (x + 5) + speedX, scaleY * (y + 100) + speedY);
    glVertex2i(scaleX * (x + 20) + speedX, scaleY * (y + 100) + speedY);
    glVertex2i(scaleX * (x + 20) + speedX, scaleY * (y + 80) + speedY);
    glVertex2i(scaleX * (x + 5) + speedX, scaleY * (y + 80) + speedY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.2f, 0.2f);
    glVertex2i(scaleX * (x + 20) + speedX, scaleY * (y + 80) + speedY);
    glVertex2i(scaleX * (x + 60) + speedX, scaleY * (y + 80) + speedY);
    glVertex2i(scaleX * (x + 60) + speedX, scaleY * (y + 60) + speedY);
    glVertex2i(scaleX * (x + 20) + speedX, scaleY * (y + 60) + speedY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.5f);
    glVertex2i(scaleX * (x + 40) + speedX, scaleY * (y + 60) + speedY);
    glVertex2i(scaleX * (x + 80) + speedX, scaleY * (y + 60) + speedY);
    glVertex2i(scaleX * (x + 80) + speedX, scaleY * (y + 40) + speedY);
    glVertex2i(scaleX * (x + 40) + speedX, scaleY * (y + 40) + speedY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2i(scaleX * (x + 20) + speedX, scaleY * (y + 40) + speedY);
    glVertex2i(scaleX * (x + 100) + speedX, scaleY * (y + 40) + speedY);
    glVertex2i(scaleX * (x + 100) + speedX, scaleY * (y + 20) + speedY);
    glVertex2i(scaleX * (x + 20) + speedX, scaleY * (y + 20) + speedY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.5f);
    glVertex2i(scaleX * (x)+speedX, scaleY * (y)+speedY);
    glVertex2i(scaleX * (x + 120) + speedX, scaleY * (y)+speedY);
    glVertex2i(scaleX * (x + 120) + speedX, scaleY * (y + 20) + speedY);
    glVertex2i(scaleX * (x)+speedX, scaleY * (y + 20) + speedY);
    glEnd();

    //face
    glBegin(GL_POLYGON);
    glColor3f(0.95f, 0.75f, 0.6f);
    glVertex2i(scaleX * (x + 100) + speedX, scaleY * (y - 80) + speedY);
    glVertex2i(scaleX * (x)+speedX, scaleY * (y - 80) + speedY);
    glVertex2i(scaleX * (x)+speedX, scaleY * (y - 100) + speedY);
    glVertex2i(scaleX * (x + 100) + speedX, scaleY * (y - 100) + speedY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.95f, 0.75f, 0.6f);
    glVertex2i(scaleX * (x + 120) + speedX, scaleY * (y)+speedY);
    glVertex2i(scaleX * (x)+speedX, scaleY * (y)+speedY);
    glVertex2i(scaleX * (x)+speedX, scaleY * (y - 80) + speedY);
    glVertex2i(scaleX * (x + 120) + speedX, scaleY * (y - 80) + speedY);
    glEnd();

    //hair
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(scaleX * (x + 120) + speedX, scaleY * (y - 0) + speedY);
    glVertex2i(scaleX * (x + 0) + speedX, scaleY * (y - 0) + speedY);
    glVertex2i(scaleX * (x + 0) + speedX, scaleY * (y - 20) + speedY);
    glVertex2i(scaleX * (x + 120) + speedX, scaleY * (y - 20) + speedY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(scaleX * (x + 100) + speedX, scaleY * (y - 20) + speedY);
    glVertex2i(scaleX * (x + 120) + speedX, scaleY * (y - 20) + speedY);
    glVertex2i(scaleX * (x + 120) + speedX, scaleY * (y - 40) + speedY);
    glVertex2i(scaleX * (x + 100) + speedX, scaleY * (y - 40) + speedY);
    glEnd();

    //nose
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex2i(scaleX * (x - 40 + nose_length) + speedX, scaleY * (y - 80) + speedY);
    glVertex2i(scaleX * (x + 40) + speedX, scaleY * (y - 80) + speedY);
    glVertex2i(scaleX * (x + 40) + speedX, scaleY * (y - 60) + speedY);
    glVertex2i(scaleX * (x - 40 + nose_length) + speedX, scaleY * (y - 60) + speedY);
    glEnd();

    //eyes
    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2i(scaleX * (x + 10) + speedX, scaleY * (y - 30) + speedY);
    glVertex2i(scaleX * (x + 40) + speedX, scaleY * (y - 30) + speedY);
    glVertex2i(scaleX * (x + 40) + speedX, scaleY * (y - 50) + speedY);
    glVertex2i(scaleX * (x + 10) + speedX, scaleY * (y - 50) + speedY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2i(scaleX * (x + 50) + speedX, scaleY * (y - 30) + speedY);
    glVertex2i(scaleX * (x + 80) + speedX, scaleY * (y - 30) + speedY);
    glVertex2i(scaleX * (x + 80) + speedX, scaleY * (y - 50) + speedY);
    glVertex2i(scaleX * (x + 50) + speedX, scaleY * (y - 50) + speedY);
    glEnd();

    //eyeball
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.75f, 0.9f);
    glVertex2i(scaleX * (x + 50) + speedX, scaleY * (y - 35) + speedY);
    glVertex2i(scaleX * (x + 70) + speedX, scaleY * (y - 35) + speedY);
    glVertex2i(scaleX * (x + 70) + speedX, scaleY * (y - 50) + speedY);
    glVertex2i(scaleX * (x + 50) + speedX, scaleY * (y - 50) + speedY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.75f, 0.9f);
    glVertex2i(scaleX * (x + 10) + speedX, scaleY * (y - 35) + speedY);
    glVertex2i(scaleX * (x + 30) + speedX, scaleY * (y - 35) + speedY);
    glVertex2i(scaleX * (x + 30) + speedX, scaleY * (y - 50) + speedY);
    glVertex2i(scaleX * (x + 10) + speedX, scaleY * (y - 50) + speedY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2i(scaleX * (x + 50) + speedX, scaleY * (y - 40) + speedY);
    glVertex2i(scaleX * (x + 60) + speedX, scaleY * (y - 40) + speedY);
    glVertex2i(scaleX * (x + 60) + speedX, scaleY * (y - 50) + speedY);
    glVertex2i(scaleX * (x + 50) + speedX, scaleY * (y - 50) + speedY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2i(scaleX * (x + 10) + speedX, scaleY * (y - 40) + speedY);
    glVertex2i(scaleX * (x + 20) + speedX, scaleY * (y - 40) + speedY);
    glVertex2i(scaleX * (x + 20) + speedX, scaleY * (y - 50) + speedY);
    glVertex2i(scaleX * (x + 10) + speedX, scaleY * (y - 50) + speedY);
    glEnd();

    //body
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.5f);
    glVertex2i(scaleX * (x + 100) + speedX, scaleY * (y - 100) + speedY);
    glVertex2i(scaleX * x + speedX, scaleY * (y - 100) + speedY);
    glVertex2i(scaleX * x + speedX, scaleY * (y - 180) + speedY);
    glVertex2i(scaleX * (x + 100) + speedX, scaleY * (y - 180) + speedY);
    glEnd();

    //pants
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.2f, 0.2f);
    glVertex2i(scaleX * (x + 100) + speedX, scaleY * (y - 130) + speedY);
    glVertex2i(scaleX * x + speedX, scaleY * (y - 130) + speedY);
    glVertex2i(scaleX * x + speedX, scaleY * (y - 180) + speedY);
    glVertex2i(scaleX * (x + 100) + speedX, scaleY * (y - 180) + speedY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.2f, 0.2f);
    glVertex2i(scaleX * (x + 35) + speedX, scaleY * (y - 100) + speedY);
    glVertex2i(scaleX * (x + 15) + speedX, scaleY * (y - 100) + speedY);
    glVertex2i(scaleX * (x + 15) + speedX, scaleY * (y - 180) + speedY);
    glVertex2i(scaleX * (x + 35) + speedX, scaleY * (y - 180) + speedY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.2f, 0.2f);
    glVertex2i(scaleX * (x + 70) + speedX, scaleY * (y - 100) + speedY);
    glVertex2i(scaleX * (x + 50) + speedX, scaleY * (y - 100) + speedY);
    glVertex2i(scaleX * (x + 50) + speedX, scaleY * (y - 180) + speedY);
    glVertex2i(scaleX * (x + 70) + speedX, scaleY * (y - 180) + speedY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.2f, 0.2f);
    glVertex2i(scaleX * x + speedX, scaleY * (y - 180) + speedY);
    glVertex2i(scaleX * (x + 100) + speedX, scaleY * (y - 180) + speedY);
    glVertex2i(scaleX * (x + 100) + speedX, scaleY * (y - 200) + speedY);
    glVertex2i(scaleX * x + speedX, scaleY * (y - 200) + speedY);
    glEnd();

    //vest
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2i(scaleX * (x + 75) + speedX, scaleY * (y - 100) + speedY);
    glVertex2i(scaleX * (x + 100) + speedX, scaleY * (y - 100) + speedY);
    glVertex2i(scaleX * (x + 100) + speedX, scaleY * (y - 180) + speedY);
    glVertex2i(scaleX * (x + 75) + speedX, scaleY * (y - 180) + speedY);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2i(scaleX * x + speedX, scaleY * (y - 100) + speedY);
    glVertex2i(scaleX * (x + 100 - 90) + speedX, scaleY * (y - 100) + speedY);
    glVertex2i(scaleX * (x + 100 - 90) + speedX, scaleY * (y - 180) + speedY);
    glVertex2i(scaleX * x + speedX, scaleY * (y - 180) + speedY);
    glEnd();
}

void light(int x, int y, int w, int h) {
    glColor3ub(255, 255, 224);
    rectangle(x, y, w, h);
}

void drawLightShadow(int x, int y, int w, int h) {
    glColor3ub(255, 201, 100);
    oval(x, y - (h / 2), w / 2, 50);
}
