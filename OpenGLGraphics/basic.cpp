#include "cg.h"

void mydisplay() {
	//Array
	float vertices[26];
	float x = 0.0;
	vertices[0] = 0.0; vertices[1] = 0.0;
	for(int i = 1; i < 13; i++) {
		vertices[2 * i] = 0.5 * cos(x);
		vertices[2 * i + 1] = 0.5 * sin(x);
		//x += radians(30.0);
	}

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, vertices);
	unsigned int indices[] = { 0,2,1, 0,3,2, 0,4,3, 0,5,4, 0,6,5, 0,7,6, 0,8,7, 0,9,8, 0,10,9, 0,11,10, 0,12,11, 0,1,12 };
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Drawing");
	glutDisplayFunc(mydisplay);
	glutMainLoop();

	return 0;
}