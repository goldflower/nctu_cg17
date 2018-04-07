#include <stdlib.h>
#include "../GL/glut.h"
#include <math.h>
#include <iostream>
#include <stdio.h>

# define M_PI 3.14159265358979323846
void init(void);
void display(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void idle(void);

// true時展示動畫
bool animeFlag = false;
bool initPen = true;
bool initApple = true;
void drawCube(GLfloat d, GLfloat l)
{
	
	static GLfloat cubexrot = 0.0;
	static GLfloat cubeyrot = 0.0;
	static GLfloat cubezrot = 0.0;
	glPushMatrix();
	glTranslated(0, 0.8, -2);
	glRotatef(cubexrot, 1, 0, 0);
	glRotatef(cubeyrot, 0, 1, 0);
	glRotatef(cubezrot, 0, 0, 1);
	// x-z at y=1, white
	glColor4f(1.0, 1.0, 1.0, 0.9);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glBegin(GL_QUADS);
	glVertex3f(l, l,-l - d);
	glVertex3f(-l, l,-l - d);
	glVertex3f(-l, l, l - d);
	glVertex3f(l, l, l - d);
	glEnd();


	// x-z at y=-1, red
	glColor4f(1.0, 0.0, 0.0, 0.3);
	glBegin(GL_QUADS);
	glVertex3f(l,-l, l - d);
	glVertex3f(-l,-l, l - d);
	glVertex3f(-l,-l,-l - d);
	glVertex3f(l,-l,-l - d);
	glEnd();

	// x-y at z=1, green
	glColor4f(0.0, 1.0, 0.0, 0.3);
	glBegin(GL_QUADS);
	glVertex3f(l, l, l - d);
	glVertex3f(-l, l, l - d);
	glVertex3f(-l,-l, l - d);
	glVertex3f(l,-l, l - d);
	glEnd();

	// x-y at z = -1, blue
	glColor4f(0.0, 0.0, 1.0, 0.3);
	glBegin(GL_QUADS);
	glVertex3f(l,-l,-l - d);
	glVertex3f(-l,-l,-l - d);
	glVertex3f(-l, l,-l - d);
	glVertex3f(l, l,-l - d);
	glEnd();

	// y-z at x=-1, gray
	glColor4f(0.3, 0.3, 0.3, 0.3);
	glBegin(GL_QUADS);
	glVertex3f(-l, l, l - d);
	glVertex3f(-l, l,-l - d);
	glVertex3f(-l,-l,-l - d);
	glVertex3f(-l,-l, l - d);
	glEnd();

	// y-z at x=1, w/e
	glColor4f(0.3, 0.8, 0.3, 0.3);
	glBegin(GL_QUADS);
	glVertex3f(l, l,-l - d);
	glVertex3f(l, l, l-d);
	glVertex3f(l,-l, l-d);
	glVertex3f(l,-l,-l-d);
	glEnd();

	glPopMatrix();

	cubexrot += 1;
	cubeyrot += 1;
	cubezrot += 1;
}
void drawRotPen(GLfloat x, GLfloat y, int precision)
{
	glColor4f(0.5, 0.5, 0.5, 1);
	static GLfloat penxrot = 0.0;
	static GLfloat penyrot = 0.0;
	static GLfloat penzrot = 0.0;

	GLfloat baseRadius = 0.1;
	GLfloat topRadius = 0.1;
	GLfloat height = 2;


	GLUquadricObj *cone = gluNewQuadric();
	GLUquadricObj *cylinder = gluNewQuadric();




	glPushMatrix();	// 紀錄當前global frame
					// 直覺順序:
					// 1.沿z軸(與global frame重合)筆中心移到原點
					// 2.筆沿y轉一點
					// 3.繞x軸轉,站起來
					// 4.繞y軸轉,進動
					// 5.移到指定位置
					// opengl反過來寫
	glTranslatef(x, y, 0);
	glRotatef(penyrot, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(15, 0, 1, 0);
	glTranslatef(0, 0, -height / 2);
	glPushMatrix(); // 紀錄筆的frame
	glTranslatef(0, 0, height);
	gluCylinder(cone, baseRadius, 0, height / 5, precision, precision);
	glPopMatrix();

	gluCylinder(cylinder, baseRadius, topRadius, height, precision, precision);

	glPopMatrix(); // 回到global frame

				   // 每次loop繞global frame的軸轉多少度
	penxrot += 0;
	penyrot += 1;
	penzrot += 0;
}
void drawRotApple(GLfloat x, GLfloat y, int precision)
{
	GLUquadricObj *sphere = gluNewQuadric();
	GLUquadricObj *vbranch = gluNewQuadric();
	GLUquadricObj *hbranch = gluNewQuadric();
	GLUquadricObj *disk = gluNewQuadric();

	GLfloat branchRadius = 0.05;
	GLfloat branchHeight = 0.3;
	GLfloat sphereRadius = 0.8;

	static GLfloat applexrot = 0.0;
	static GLfloat appleyrot = 0.0;
	static GLfloat applezrot = 0.0;

	//glLoadIdentity();
	glPushMatrix(); // 記錄當前global frame
					// 將sephere移到指定位置
					// 並且每次loop都會改變角度
	glTranslatef(x, y, 0);

	glRotatef(appleyrot, 0, 1, 0);
	gluSphere(sphere, sphereRadius, precision, precision);
	glPushMatrix(); // 記錄sphere local frame
					// 將cone移到指定位置
	glTranslatef(-0.5*branchHeight, sphereRadius + 0.5*branchHeight, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(45, 1, 0, 0);
	gluCylinder(hbranch, branchRadius, 0, branchHeight, precision, precision);
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	gluDisk(disk, 0, branchRadius, precision, precision);
	glPopMatrix();
	
	glPopMatrix(); // 回到spere local frame

	glPushMatrix(); // 記錄當前sphere local frame
					// 將cone移到指定位置
	glTranslatef(0, sphereRadius + branchHeight, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(vbranch, branchRadius, 0, branchHeight, precision, precision);
	glPopMatrix(); // 回到sphere local frame
	
				   // 最後補上sephere
	
	glPopMatrix(); // 回到global frame

				   // 每回合轉多少
	applexrot += 0;
	appleyrot += 1;
	applezrot += 0;
}
void drawMovePen(GLfloat x, GLfloat y, int precision)
{
	glColor4f(0.5, 0.5, 0.5, 1);

	static GLfloat penzmove = 0.0;
	if (initPen)
	{
		penzmove = 0;
		initPen = false;
	}
	GLfloat baseRadius = 0.1;
	GLfloat topRadius = 0.1;
	GLfloat height = 2;

	GLUquadricObj *cone = gluNewQuadric();
	GLUquadricObj *cylinder = gluNewQuadric();

	glPushMatrix();	// 紀錄當前global frame
	glTranslatef(penzmove, 0, 0);
	glTranslatef(x, y, 0);
	glRotatef(90, 0, 1, 0);
	glPushMatrix(); // 紀錄筆的frame
	glTranslatef(0, 0, height);
	gluCylinder(cone, baseRadius, 0, height / 5, precision, precision);
	glPopMatrix();

	gluCylinder(cylinder, baseRadius, topRadius, height, precision, precision);

	glPopMatrix(); // 回到global frame

	if (penzmove < -x - height / 2)
	{
		penzmove += 0.1;
	}
}
void drawMoveApple(GLfloat x, GLfloat y, int precision)
{
	GLUquadricObj *sphere = gluNewQuadric();
	GLUquadricObj *vbranch = gluNewQuadric();
	GLUquadricObj *hbranch = gluNewQuadric();

	GLfloat branchRadius = 0.05;
	GLfloat branchHeight = 0.3;
	GLfloat sphereRadius = 0.8;

	static GLfloat applemove = 0.0;

	if (initApple)
	{
		applemove = 0;
		initApple = false;
	}
	//glLoadIdentity();
	glPushMatrix(); // 記錄當前global frame
					// 將sephere移到指定位置
					// 並且每次loop都會改變角度
	glTranslatef(-applemove, 0, 0);
	glTranslatef(x, y, 0);
	glPushMatrix(); // 記錄當前sphere local frame
					// 將cone移到指定位置
	glTranslatef(0, sphereRadius + branchHeight, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(vbranch, branchRadius, 0, branchHeight, precision, precision);
	glPopMatrix(); // 回到sphere local frame
	glPushMatrix(); // 記錄sphere local frame
					// 將cone移到指定位置
	glTranslatef(-0.5*branchHeight, sphereRadius + 0.5*branchHeight, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(45, 1, 0, 0);
	gluCylinder(hbranch, branchRadius, 0, branchHeight, precision, precision);
	glPopMatrix(); // 回到spere local frame
				   // 最後補上sephere
	gluSphere(sphere, sphereRadius, precision, precision);
	glPopMatrix(); // 回到global frame

	if (applemove < x)
	{
		applemove += 0.1;
	}
}

void init(void) {

	GLfloat position[] = { 1.0, 1.0, 5.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);//混成的規則

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	// 開啟混成
	
	glDepthFunc(GL_LEQUAL);

}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// origin: 0 0 8; 0 0 0; 0 1 0
	gluLookAt(0.0, 0.0, 8, /* Eye pos XYZ */
		0.0, 0.0, 0.0, /* Target pos XYZ */
		0.0, 1.0, 0.0); /* Up vector */

	// do something awesome here


	// 畫的平滑程度
	GLfloat precision = 200;
	// 設定背景顏色
	glClearColor(0, 0, 0, 0);
	
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	if (!animeFlag)
	{
		drawRotPen(-2.1, -1.3, precision);
		drawRotApple(2.1, -1.3, precision);
	}
	else
	{
		
		drawMoveApple(2.1, -1.3, precision);
		drawMovePen(-2.1, -1.3, precision);
		
	}
	glEnable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	drawCube(0, 1.2);
	glEnable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);
	
	

	glFlush();
	glutSwapBuffers();

}


void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 13:
	{   //enter
		if (animeFlag)
		{
			animeFlag = false;
			initPen = true;
			initApple = true;
		}
		else
		{
			animeFlag = true;
		}
		break;
	}
	case 27:
	{   //ESC
		exit(0);
		break;
	}
	default:
	{
		break;
	}
	}
}

void idle(void)
{
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("OpenGL Assignment 1");
	glutReshapeWindow(512, 512);

	init();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}