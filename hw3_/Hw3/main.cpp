#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> /* offsetof */
#include "../GL/glew.h"
#include "../GL/glut.h"
#include "../shader_lib/shader.h"
#include <iostream>
#include "glm/glm.h"
#include <vector>

extern "C"
{
#include "glm_helper.h"
}

void init(void);
void display(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void idle(void);

GLMmodel *apple;
GLfloat light_pos[] = { 10.0, 10.0, 0.0 };
GLuint flat_VBO;
GLuint phong_VBO;
GLuint phong_program;
GLuint shader_program;
int shaderID = 0;
float eyex = 0.0;
float eyey = 0.0;

GLuint model_loc;
GLuint view_loc;
GLuint proj_loc;
GLuint light_loc;

int rot_y = 0;
int shader_selector = 0;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("OpenGL HW3 - 0556171");
	glutReshapeWindow(512, 512);

	glewInit();

	init();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	glmDelete(apple);
	return 0;
}

struct userDefineVertex
{
	float vertex[3];
	float textCoord[2];
	float norm[3];
	float faceNorm[3];
};

void init(void) {

	apple = glmReadOBJ("Model/apple.obj");

	glmUnitize(apple);
	glmFacetNormals(apple);
	glmVertexNormals(apple, 90.0, GL_FALSE);
	

	
	//print_model_info(apple);
	// initialize
	GLuint flat_vert = createShader("Shaders/flat.vs", "vertex");
	GLuint flat_frag = createShader("Shaders/flat.frag", "fragment");
	shader_program = createProgram(flat_vert, flat_frag);
	// flat part
	glGenBuffers(1, &flat_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, flat_VBO);
	int objSize = 0;
	std::vector<float> T;
	GLMgroup *g = apple->groups;
	while (g)
	{
		int groupSize = 0;
		for (int i = 0; i < g->numtriangles; i++)
		{
			userDefineVertex v;
			// get the triangle indicies
			// these triangle use the same material
			int triangleIndex = g->triangles[i];
			// get vindices of triangle of group g

			for (int j = 0; j < 3; j++)
			{
				GLuint vIndex = apple->triangles[triangleIndex].vindices[j] * 3;
				T.push_back(apple->vertices[vIndex]);
				T.push_back(apple->vertices[vIndex + 1]);
				T.push_back(apple->vertices[vIndex + 2]);

				GLuint tIndex = apple->triangles[triangleIndex].tindices[j] * 2;
				T.push_back(apple->texcoords[tIndex]);
				T.push_back(apple->texcoords[tIndex + 1]);
				

				GLuint nIndex = apple->triangles[triangleIndex].nindices[j] * 3;
				T.push_back(apple->normals[nIndex]);
				T.push_back(apple->normals[nIndex + 1]);
				T.push_back(apple->normals[nIndex + 2]);

				GLuint fIndex = apple->triangles[triangleIndex].findex * 3;
				T.push_back(apple->facetnorms[fIndex]);
				T.push_back(apple->facetnorms[fIndex + 1]);
				T.push_back(apple->facetnorms[fIndex + 2]);
				

				objSize += 11 * sizeof(float);
			}
		}
		g = g->next;
	}
	glBufferData(GL_ARRAY_BUFFER, objSize, T.data(), GL_STATIC_DRAW);

	//userDefineVertex s;
	//positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(userDefineVertex), (GLvoid*)offsetof(userDefineVertex, vertex));
	glEnableVertexAttribArray(0);
	//textures
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(userDefineVertex), (GLvoid*)offsetof(userDefineVertex, textCoord));
	glEnableVertexAttribArray(1);
	//normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(userDefineVertex), (GLvoid*)offsetof(userDefineVertex, norm));
	glEnableVertexAttribArray(2);
	// face normals
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(userDefineVertex), (GLvoid*)offsetof(userDefineVertex, faceNorm));
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void display(void)
{
	glClearColor(0.5f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1e-2, 1e2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyex, eyey, 3.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
	// write here
	glEnable(GL_DEPTH_TEST);


	// =========get model, view, projection matricies=======
	// 1.get projection matrix
	GLfloat projection[16];
	glGetFloatv(GL_PROJECTION_MATRIX, projection);
	// 2.get view matrix, the transform correspond to the global coord
	GLfloat view[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, view);
	// 3. get model matrix, the transform correspond to the local coord
	//	  note that we always operate objects at the origin
	//	  so we use glLoadIdentity() to make sure the object is now at the origin
	GLfloat model[16];
	glLoadIdentity();
	glRotatef(rot_y, 0, 1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, model);
	rot_y += 1;

	glBindTexture(GL_TEXTURE_2D, apple->textures[0].id);
	glEnable(GL_TEXTURE_2D);
	
	glUseProgram(shader_program);

	// Get the uniform locations
	model_loc = glGetUniformLocation(shader_program, "model");
	view_loc = glGetUniformLocation(shader_program, "view");
	proj_loc = glGetUniformLocation(shader_program, "projection");
	light_loc = glGetUniformLocation(shader_program, "light");

	glUniformMatrix4fv(model_loc, 1, GL_FALSE, model);
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, view);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, projection);
	glUniform3f(light_loc, light_pos[0], light_pos[1], light_pos[2]);
	
	
	GLMgroup *g = apple->groups;
	// g->triangles
	int tmp = 0;
	while (g)
	{
		// get all material properties of this group
		// and put into fragment shader
		int materialIndex = g->material;
		GLuint map_diffuse_id = apple->materials[materialIndex].map_diffuse;
		GLuint tex_id = apple->textures[map_diffuse_id].id;
		GLint texure_loc = glGetUniformLocation(shader_program, "samplerTexture");
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, tex_id);
		glUniform1i(texure_loc, 0);

		GLfloat *ambient = apple->materials[materialIndex].ambient;
		GLfloat *diffuese = apple->materials[materialIndex].diffuse;
		GLfloat *specular = apple->materials[materialIndex].specular;
		GLMtexture texture = apple->textures[apple->materials[materialIndex].map_diffuse];
		GLfloat shininess = apple->materials[materialIndex].shininess;
		GLuint shader_selector_loc = glGetUniformLocation(shader_program, "shader_selector");
		GLuint ambient_loc = glGetUniformLocation(shader_program, "ambient_coe");
		GLuint diffuse_loc = glGetUniformLocation(shader_program, "diffuse_coe");
		GLuint specular_loc = glGetUniformLocation(shader_program, "specular_coe");
		GLuint shininess_loc = glGetUniformLocation(shader_program, "shininess");
		GLuint texture_loc = glGetUniformLocation(shader_program, "texture");
		glUniform4f(ambient_loc, ambient[0], ambient[1], ambient[2], ambient[3]);
		glUniform4f(diffuse_loc, diffuese[0], diffuese[1], diffuese[2], diffuese[3]);
		glUniform4f(specular_loc, specular[0], specular[1], specular[2], specular[3]);
		glUniform1f(shininess_loc, shininess);
		glUniform1i(shader_selector_loc, shader_selector);
		glDrawArrays(GL_TRIANGLES, tmp, 3*g->numtriangles);
		glBindTexture(GL_TEXTURE_2D, NULL);
		tmp = 3 * g->numtriangles + 3;
		g = g->next;
	}
	
	glBindTexture(GL_TEXTURE_2D, NULL);
	glUseProgram(0);

	glutSwapBuffers();

}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
	{	//ESC
		exit(0);
		break;
	}
	case 13:
	{	//ENTER
		shader_selector = (shader_selector + 1) % 3;
		break;
	}
	case 'd':
	{
		eyex += 0.1;
		break;
	}
	case 'a':
	{
		eyex -= 0.1;
		break;
	}
	case 'w':
	{
		eyey += 0.1;
		break;
	}
	case 's':
	{
		eyey -= 0.1;
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