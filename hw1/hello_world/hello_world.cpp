//=============================================================================
//�d���ɽs��1
//�]���O�Ĥ@�ӽd�ҡA�ҥH�̭������֨ƨS���A���O�k�s�M�M��buffer
//hello world���K
//=============================================================================
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "../GL/glut.h"
#include <stdio.h>

void Display(void)
{
	glBegin(GL_TRIANGLES);// �}�l���T���� 
	glColor3f(1.0f, 0.0f, 0.0f);// �]�w��X�⬰���� 
	glVertex2f(0.0f, 1.0f);//(x1,y1)=(0, 1)
	glColor3f(0.0f, 1.0f, 0.0f);// �]�w��X�⬰��� 
	glVertex2f(1.0f, -0.5f);//(x2,y2)=(1.0,-0.5)
	glColor3f(0.0f, 0.0f, 1.0f);// �]�w��X�⬰�Ŧ� 
	glVertex2f(-1.0f, -0.5f);//(x3,y3)=(-1.0,-0.5)
	glEnd();// �������T���� 
	glutSwapBuffers();//�Nbuffer���ܿù�
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//�n�D�C��RGB�������w��
	glutInitWindowPosition(100, 50); // �]�w������m 
	glutInitWindowSize(800, 600); // �]�w�����j�p 
	glutCreateWindow("HELLO WORLD"); // �]�w�������D 
	glutDisplayFunc(Display);  // �I�s��� Callback�禡
	glutMainLoop();
	return 0;
}