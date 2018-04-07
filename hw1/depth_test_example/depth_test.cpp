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
	glEnable(GL_DEPTH_TEST);
	//glClearDepth(2.0f);
	glDepthFunc(GL_LESS);//預設就是GL_LESS，以下說明以攝影機從z正往負看，實際情形請依攝影機觀看方向來算
	//當第一個是-0.5，第二個是-0.8，-0.5>-0.8，所以通過(顯示)
	//當第一個是-0.8，第二個是-0.5，-0.8<-0.5，所以不通過(不顯示)
	//可以調整參數來改變深度測試結果
	glEnable(GL_BLEND);//開啟混成，不然無法使用半透明
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);//混成的規則
}
void Display(void)
{
	/*
	先注意init的內容
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除buffer中的資料
	glPushMatrix();
	
	glColor4f(0.0f, 1.0f, 0.0f, 0.4f);// 設定輸出色為green 半透明 
	glBegin(GL_TRIANGLES);		// 第一個三角形前景
	glVertex3f(0.0f, 0.5f ,-0.5f);
	glVertex3f(0.5f, 0.0f ,-0.5f);
	glVertex3f(-0.5f, 0.0f ,-0.5f);
	glEnd();

	glColor4f(1.0f, 0.0f, 0.0f, 0.4f);//紅 半透明
	glBegin(GL_TRIANGLES);		// 第一個三角形後景
	glVertex3f(0.0f, 0.8f ,-0.8f);
	glVertex3f(0.8f, 0.0f ,-0.8f);
	glVertex3f(-0.8f, 0.0f ,-0.8f);
	glEnd();
	
	glColor4f(1.0f, 0.0f, 0.0f, 0.4f);//紅 半透明
	glBegin(GL_TRIANGLES);		// 第二個三角形後景
	glVertex3f(0.0f, 0.0f, -0.8f);
	glVertex3f(0.8f, -0.5f, -0.8f);
	glVertex3f(-0.8f, -0.5f, -0.8f);
	glEnd();

	glColor4f(0.0f, 1.0f, 0.0f, 0.4f);// 設定輸出色為green 半透明 
	glBegin(GL_TRIANGLES);		// 第二個三角形前景
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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);//要求顏色RGB及雙重緩衝
	glutInitWindowPosition(100, 50); // 設定視窗位置 
	glutInitWindowSize(800, 600); // 設定視窗大小 
	glutCreateWindow("DEPTH TEST EXAMPLE"); // 設定視窗標題 
	init();//視窗建立後初始化
	glutDisplayFunc(Display);  //Callback函式
	glutMainLoop();
	return 0;
}