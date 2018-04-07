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




	// �e�����Ƶ{��
	GLfloat precision = 200;
	// �]�w�I���C��
	glClearColor(0.8, 0.8, 0.8, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);//�M��buffer�������

	// �}�ҲV��
	glEnable(GL_BLEND);
	// ���`�״���
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

	glPushMatrix();	// ������eglobal frame

		// �ثe�n�Ыت�������m�bglobal�����I
		// ����������w��m��¶x��쪽��
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, 0, -height/2);
		// pen�� y�b��@�I
		glRotatef(-20, 0, 0, 1);
		// ¶���������
		int penCenterx = -2 - (height / 2 * cos(90 - 20));
		int penCentery = -2 + (height / 2 * sin(90 - 20));
		// �����߲���global���I
		//glTranslatef(-penCenterx , -penCentery, 0);
		
		
		// 1.¶x����b���global x-z����
		//glRotatef(90, 1, 0, 0);
		// 2.¶y����b���z�b,�K��
		//glRotatef(90, 0, 0, 1);
		// 3.��z�b����
		glRotatef(penyrot,0, 1, 0);
		// 2.��inverse
		//glRotatef(-90, 1, 0, 0);
		// 1.��inverse
		//glRotatef(-90, 1, 0, 0);
		//glTranslatef(penCenterx, penCentery, 0);
		//glTranslatef(2, 2, 0);
		glPushMatrix(); // ������ecylinder local frame
			// �ثe�n�Ыت�������m�bcylinder����������
			// cylinder�uz�b��l��,�]��cone�n��z�b�վ�
			// �Ncone���ʨ�cylinder������
			glTranslatef(0, 0, height);
			gluCylinder(cone, baseRadius, 0, height / 5, precision, precision);
		glPopMatrix();	//�^��cylinder local frame
		
		// �ɤWcylinder
		gluCylinder(cylinder, baseRadius, topRadius, height, precision, precision);
		
	glPopMatrix(); // �^��global frame

	// �C��loop¶global frame���b��h�֫�
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
	glPushMatrix(); // �O����eglobal frame
		// �Nsephere������w��m
		// �åB�C��loop���|���ܨ���
		glTranslatef(2.1, -1, 0);
		glRotatef(appleyrot, 0, 1, 0);
		glPushMatrix(); // �O����esphere local frame
			// �Ncone������w��m
			glTranslatef(0, sphereRadius+branchHeight, 0);
			glRotatef(90, 1, 0, 0);
			gluCylinder(vbranch, branchRadius, 0, branchHeight, precision, precision);
		glPopMatrix(); // �^��sphere local frame
		glPushMatrix(); // �O��sphere local frame
			// �Ncone������w��m
			glTranslatef(-0.5*branchHeight, sphereRadius + 0.5*branchHeight, 0);
			glRotatef(90, 0, 1, 0);
			glRotatef(45, 1, 0, 0);
			gluCylinder(hbranch, branchRadius, 0, branchHeight, precision, precision);
		glPopMatrix(); // �^��spere local frame
		// �̫�ɤWsephere
		gluSphere(sphere, sphereRadius, precision, precision);
	glPopMatrix(); // �^��global frame

	// �C�^�X��h��
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