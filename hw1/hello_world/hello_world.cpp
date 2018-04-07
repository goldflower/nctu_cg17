//=============================================================================
//範例檔編號1
//因為是第一個範例，所以裡面有不少事沒做，像是歸零和清除buffer
//hello world嘛…
//=============================================================================
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "../GL/glut.h"
#include <stdio.h>

void Display(void)
{
	glBegin(GL_TRIANGLES);// 開始劃三角形 
	glColor3f(1.0f, 0.0f, 0.0f);// 設定輸出色為紅色 
	glVertex2f(0.0f, 1.0f);//(x1,y1)=(0, 1)
	glColor3f(0.0f, 1.0f, 0.0f);// 設定輸出色為綠色 
	glVertex2f(1.0f, -0.5f);//(x2,y2)=(1.0,-0.5)
	glColor3f(0.0f, 0.0f, 1.0f);// 設定輸出色為藍色 
	glVertex2f(-1.0f, -0.5f);//(x3,y3)=(-1.0,-0.5)
	glEnd();// 結束劃三角形 
	glutSwapBuffers();//將buffer換至螢幕
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//要求顏色RGB及雙重緩衝
	glutInitWindowPosition(100, 50); // 設定視窗位置 
	glutInitWindowSize(800, 600); // 設定視窗大小 
	glutCreateWindow("HELLO WORLD"); // 設定視窗標題 
	glutDisplayFunc(Display);  // 呼叫函數 Callback函式
	glutMainLoop();
	return 0;
}