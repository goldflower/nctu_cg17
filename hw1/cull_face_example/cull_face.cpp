//=============================================================================
//�d���ɽs��2
//���M�u�O�@�ǤT���ΡA���L�n�`�N�e��e������
//�O�o�e�ϫe�n�M��BUFFER�A���M�|�M�H�e�e�������|��
//�i�H��void glDepthFunc(GLenum); �վ�`�״��ժ���k
//=============================================================================
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "../GL/glut.h"
#include <stdio.h>

void init(void)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//GL_BACK�BGL_FRONT
	//GL_FRONT_AND_BACK
	glFrontFace(GL_CCW);//�w�]�OCCW�A�f�ɰw
						//GL_CW�BGL_CCW
}
void Display(void)
{
	/*
	���`�Ninit�����e
	*/
	//glColor4f(0.0f, 0.0f, 1.0f, 1.0f);// �]�w��X�⬰�Ŧ�
	glClear(GL_COLOR_BUFFER_BIT);//�M��buffer�������
	glPushMatrix();

	glBegin(GL_TRIANGLES);
	//�}�l���T���ΡA���ɰw
	glVertex2f(0.0f, 0.8f);
	glVertex2f(0.8f, 0.0f);
	glVertex2f(-0.8f, 0.0f);
	glEnd();

	//glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	//�ĤG�ӤT���ΡA�f�ɰw
	glVertex2f(0.0f, 0.0f);
	glVertex2f(-0.8f, -0.8f);
	glVertex2f(0.8f, -0.8f);
	glEnd();// �������T���� 

	glBegin(GL_LINE_LOOP);
	//�A�e�@���Ĥ@�ӤT���ΡA�u�e�~�ءA�]���Ĥ@�ӤT���Τ����
	glVertex2f(0.0f, 0.8f);
	glVertex2f(-0.8f, 0.0f);
	glVertex2f(0.8f, 0.0f);
	glEnd();// ����

	glPopMatrix();
	glutSwapBuffers();

}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);//�n�D�C��RGB�������w��
	glutInitWindowPosition(100, 50); // �]�w������m 
	glutInitWindowSize(800, 600); // �]�w�����j�p 
	glutCreateWindow("DEPTH TEST EXAMPLE"); // �]�w�������D 
	init();//�����إ߫��l��
	glutDisplayFunc(Display);  //Callback�禡
	glutMainLoop();
	return 0;
}