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
	glEnable(GL_DEPTH_TEST);
	//glClearDepth(2.0f);
	glDepthFunc(GL_LESS);//�w�]�N�OGL_LESS�A�H�U�����H��v���qz�����t�ݡA��ڱ��νШ���v���[�ݤ�V�Ӻ�
	//��Ĥ@�ӬO-0.5�A�ĤG�ӬO-0.8�A-0.5>-0.8�A�ҥH�q�L(���)
	//��Ĥ@�ӬO-0.8�A�ĤG�ӬO-0.5�A-0.8<-0.5�A�ҥH���q�L(�����)
	//�i�H�վ�Ѽƨӧ��ܲ`�״��յ��G
	glEnable(GL_BLEND);//�}�ҲV���A���M�L�k�ϥΥb�z��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);//�V�����W�h
}
void Display(void)
{
	/*
	���`�Ninit�����e
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�M��buffer�������
	glPushMatrix();
	
	glColor4f(0.0f, 1.0f, 0.0f, 0.4f);// �]�w��X�⬰green �b�z�� 
	glBegin(GL_TRIANGLES);		// �Ĥ@�ӤT���Ϋe��
	glVertex3f(0.0f, 0.5f ,-0.5f);
	glVertex3f(0.5f, 0.0f ,-0.5f);
	glVertex3f(-0.5f, 0.0f ,-0.5f);
	glEnd();

	glColor4f(1.0f, 0.0f, 0.0f, 0.4f);//�� �b�z��
	glBegin(GL_TRIANGLES);		// �Ĥ@�ӤT���Ϋᴺ
	glVertex3f(0.0f, 0.8f ,-0.8f);
	glVertex3f(0.8f, 0.0f ,-0.8f);
	glVertex3f(-0.8f, 0.0f ,-0.8f);
	glEnd();
	
	glColor4f(1.0f, 0.0f, 0.0f, 0.4f);//�� �b�z��
	glBegin(GL_TRIANGLES);		// �ĤG�ӤT���Ϋᴺ
	glVertex3f(0.0f, 0.0f, -0.8f);
	glVertex3f(0.8f, -0.5f, -0.8f);
	glVertex3f(-0.8f, -0.5f, -0.8f);
	glEnd();

	glColor4f(0.0f, 1.0f, 0.0f, 0.4f);// �]�w��X�⬰green �b�z�� 
	glBegin(GL_TRIANGLES);		// �ĤG�ӤT���Ϋe��
	glVertex3f(0.0f, 0.0f, -0.5f);
	glVertex3f(0.5f, -0.8f, -0.5f);
	glVertex3f(-0.5f, -0.8f, -0.5f);
	glEnd();

	
	
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