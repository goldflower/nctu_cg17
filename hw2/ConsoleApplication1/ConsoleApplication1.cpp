// This program provides a simple example of reflection,
// using the stencil buffer.

#include <gl\glut.h>
#include <iostream.h>

const unsigned char ESC = 27;

// Window properties
const int INIT_WINDOW_SIZE = 300;
int current_width = INIT_WINDOW_SIZE;
int current_height = INIT_WINDOW_SIZE;
GLfloat WIN_SIZE = 5.0;

// Centre of mirror
double cmx = -0.5;
double cmy = 0.0;
double cmz = 4.0;

// Mouse position, normalized to [0,1].
double xm = 0.0;
double ym = 0.0;

// Idle function value
double angle = 0.0;

void scene() {
	glPushMatrix();

	// Use xm and ym to position the scene.
	glTranslatef(2.0 * xm, -2.0 * ym, 0.0);

	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glColor3f(0.8f, 0.7f, 0.2f);
	glutSolidCone(1.0, 1.5, 5, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 0.0, 1.0);
	glColor3f(0.0, 0.2f, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glTranslatef(1.0, 1.0, -3.0);
	glColor3f(0.0, 1.0, 0.3f);
	glRotatef(angle, 1.0, 1.0, 0.0);
	glutWireOctahedron();
	glPopMatrix();
}

void mirror(bool p) {
	// The mirror is a rectangle normal to the X axis.
	if (p)
		glBegin(GL_QUADS);		// Draw whole mirror
	else
		glBegin(GL_LINE_LOOP);	// Draw frame of mirror only
	glVertex3f(cmx, cmy - 0.5, cmz - 2.0);
	glVertex3f(cmx, cmy - 0.5, cmz + 2.0);
	glVertex3f(cmx, cmy + 0.5, cmz + 2.0);
	glVertex3f(cmx, cmy + 0.5, cmz - 2.0);
	glEnd();
}

void display(void) {
	// Display callback function..
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -7.0);

	// Store the mirror shape in the stencil buffer.
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	mirror(true);

	// Clear the colour buffer before displaying the scene.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the mirror frame.
	glColor3f(0.7f, 0.7f, 0.7f);
	mirror(false);

	// Draw the scene outside the mirror.
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glStencilFunc(GL_NOTEQUAL, 1, 1);
	scene();

	// Draw the reflected scene in the mirror.
	glStencilFunc(GL_EQUAL, 1, 1);
	glTranslatef(cmx, cmy, cmz);		// Move to centre of mirror.
	glScalef(-1.0, 1.0, 1.0);			// Reflect in X axis.
	glTranslatef(-cmx, -cmy, -cmz);		// Move back again.
	scene();

	glutSwapBuffers();
}

void drag(int x, int y) {
	// Use mouse values to move the scenery around.
	xm = double(x) / current_width;
	ym = double(y) / current_height;
	glutPostRedisplay();
}

void spin(void) {
	// The idle function rotates the octahedron.
	if (angle > 360.0)
		angle = angle - 360.0;
	angle += 1;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	// Press ESC to terminate the program.
	switch (key) {
	case ESC:
		exit(0);
		break;
	}
}

void reshape(int w, int h) {
	// Respond to user reshaping the window.
	current_width = w;
	current_height = h;
	glViewport(0, 0, current_width, current_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, double(w) / double(h), 1.0, 20.0);
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {

	// General openGL initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL | GLUT_DEPTH);
	glutInitWindowSize(INIT_WINDOW_SIZE, INIT_WINDOW_SIZE);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Reflections in a Mirror");

	// Register callback functions.
	glutDisplayFunc(display);
	glutIdleFunc(spin);
	glutMotionFunc(drag);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);

	// Initialize stencilling.
	glClearStencil(0);
	glEnable(GL_STENCIL_TEST);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}