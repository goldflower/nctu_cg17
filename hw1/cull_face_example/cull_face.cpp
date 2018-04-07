//=============================================================================
//範例檔編號2
//雖然只是一些三角形，不過要注意前後畫的順序
//記得畫圖前要清除BUFFER，不然會和以前畫的重覆疊圖
//可以用void glDepthFunc(GLenum); 調整深度測試的方法
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
	//GL_BACK、GL_FRONT
	//GL_FRONT_AND_BACK
	glFrontFace(GL_CCW);//預設是CCW，逆時針
						//GL_CW、GL_CCW
}
void Display(void)
{
	/*
	先注意init的內容
	*/
	//glColor4f(0.0f, 0.0f, 1.0f, 1.0f);// 設定輸出色為藍色
	glClear(GL_COLOR_BUFFER_BIT);//清除buffer中的資料
	glPushMatrix();

	glBegin(GL_TRIANGLES);
	//開始劃三角形，順時針
	glVertex2f(0.0f, 0.8f);
	glVertex2f(0.8f, 0.0f);
	glVertex2f(-0.8f, 0.0f);
	glEnd();

	//glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	//第二個三角形，逆時針
	glVertex2f(0.0f, 0.0f);
	glVertex2f(-0.8f, -0.8f);
	glVertex2f(0.8f, -0.8f);
	glEnd();// 結束劃三角形 

	glBegin(GL_LINE_LOOP);
	//再畫一次第一個三角形，只畫外框，因為第一個三角形不顯示
	glVertex2f(0.0f, 0.8f);
	glVertex2f(-0.8f, 0.0f);
	glVertex2f(0.8f, 0.0f);
	glEnd();// 結束

	glPopMatrix();
	glutSwapBuffers();

}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);//要求顏色RGB及雙重緩衝
	glutInitWindowPosition(100, 50); // 設定視窗位置 
	glutInitWindowSize(800, 600); // 設定視窗大小 
	glutCreateWindow("DEPTH TEST EXAMPLE"); // 設定視窗標題 
	init();//視窗建立後初始化
	glutDisplayFunc(Display);  //Callback函式
	glutMainLoop();
	return 0;
}