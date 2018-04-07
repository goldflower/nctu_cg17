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

void drawCube()
{
	

	// x-z at y=1, white
	glColor4f(1.0, 1.0, 1.0, 0.5);
	//glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(1.0, 1.0,-1.0);
	glVertex3f(-1.0, 1.0,-1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glEnd();


	// x-z at y=-1, red
	glColor4f(1.0, 0.0, 0.0, 0.5);
	//glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(1.0,-1.0, 1.0);
	glVertex3f(-1.0,-1.0, 1.0);
	glVertex3f(-1.0,-1.0,-1.0);
	glVertex3f(1.0,-1.0,-1.0);
	glEnd();

	// x-y at z=1, green
	glColor4f(0.0, 1.0, 0.0, 0.5);
	//glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(1.0,1.0,1.0);
	glVertex3f(-1.0,1.0,1.0);
	glVertex3f(-1.0,-1.0, 1.0);
	glVertex3f(1.0,-1.0, 1.0);
	glEnd();

	// x-y at z = -1, blue
	glColor4f(0.0, 0.0, 1.0, 0.5);
	//glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(1.0,-1.0,-1.0);
	glVertex3f(-1.0,-1.0,-1.0);
	glVertex3f(-1.0, 1.0,-1.0);
	glVertex3f(1.0, 1.0,-1.0);
	glEnd();

	// y-z at x=-1, gray
	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
	//glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f(-1.0, 1.0,1.0);
	glVertex3f(-1.0, 1.0,-1.0);
	glVertex3f(-1.0,-1.0,-1.0);
	glVertex3f(-1.0,-1.0, 1.0);
	glEnd();

	// y-z at x=1, w/e
	glColor4f(0.3f, 0.8f, 0.3f, 0.5f);
	//glColor3f(0.3f, 0.8f, 0.3f);
	glBegin(GL_QUADS);
	glVertex3f(1.0, 1.0,-1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0,-1.0, 1.0);
	glVertex3f(1.0,-1.0,-1.0);
	glEnd();
}
void init(void) {

	GLfloat position[] = { 1.0, 1.0, 5.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
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
	glClearColor(0.8, 0.8, 0.8, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);//清除buffer中的資料

	// 開啟混成
	glEnable(GL_BLEND);
	// 關深度測試
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_TEXTURE_2D);
	

	// ============== PART I: DRAW CUBE =================
	static GLfloat cubexrot = 0.0;
	static GLfloat cubeyrot = 0.0;
	static GLfloat cubezrot = 0.0;
	
	glPushMatrix();
		glTranslated(0, 1, 0);
		glRotatef(cubexrot, 1, 0, 0);
		glRotatef(cubeyrot, 0, 1, 0);
		glRotatef(cubezrot, 0, 0, 1);
		drawCube();
	glPopMatrix();
	
	cubexrot += 0.07;
	cubeyrot += 0.05;
	cubezrot += 0.1;

	
	
	// ============== PART II: DRAW PEN =================
	static GLfloat penxrot = 0.0;
	static GLfloat penyrot = 0.0;
	static GLfloat penzrot = 0.0;

	GLfloat baseRadius = 0.1;
	GLfloat topRadius = 0.1;
	GLfloat height = 2;

	// draw cone
	GLUquadricObj *cone = gluNewQuadric();
	// move cone to the top of cylinder
	GLUquadricObj *cylinder = gluNewQuadric();

	glPushMatrix();	// 紀錄當前global frame

		// 目前要創建的元素位置在global的原點
		// 先平移到指定位置後繞x轉到直立
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, 0, -height/2);
		// pen的 y軸轉一點
		glRotatef(-20, 0, 0, 1);
		// 繞筆中心轉動
		int penCenterx = -2 - (height / 2 * cos(90 - 20));
		int penCentery = -2 + (height / 2 * sin(90 - 20));
		// 筆中心移到global原點
		//glTranslatef(-penCenterx , -penCentery, 0);
		
		
		// 1.繞x把轉軸轉到global x-z平面
		//glRotatef(90, 1, 0, 0);
		// 2.繞y把轉軸轉到z軸,免做
		//glRotatef(90, 0, 0, 1);
		// 3.對z軸旋轉
		glRotatef(penyrot,0, 1, 0);
		// 2.的inverse
		//glRotatef(-90, 1, 0, 0);
		// 1.的inverse
		//glRotatef(-90, 1, 0, 0);
		//glTranslatef(penCenterx, penCentery, 0);
		//glTranslatef(2, 2, 0);
		glPushMatrix(); // 紀錄當前cylinder local frame
			// 目前要創建的元素位置在cylinder的底部中心
			// cylinder沿z軸初始化,因此cone要往z軸調整
			// 將cone移動到cylinder的頂部
			glTranslatef(0, 0, height);
			gluCylinder(cone, baseRadius, 0, height / 5, precision, precision);
		glPopMatrix();	//回到cylinder local frame
		
		// 補上cylinder
		gluCylinder(cylinder, baseRadius, topRadius, height, precision, precision);
		
	glPopMatrix(); // 回到global frame

	// 每次loop繞global frame的軸轉多少度
	penxrot += 0;
	penyrot += 1;
	penzrot += 0;
		
	// ============== PART III: DRAW APPLE =================
	
	GLUquadricObj *sphere = gluNewQuadric();
	GLUquadricObj *vbranch = gluNewQuadric();
	GLUquadricObj *hbranch = gluNewQuadric();

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
		glTranslatef(2.1, -1, 0);
		glRotatef(appleyrot, 0, 1, 0);
		glPushMatrix(); // 記錄當前sphere local frame
			// 將cone移到指定位置
			glTranslatef(0, sphereRadius+branchHeight, 0);
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

	// 每回合轉多少
	applexrot += 0;
	appleyrot += 1;
	applezrot += 0;


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