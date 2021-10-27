#pragma comment (lib, "lib/freeglut.lib")
#pragma comment (lib, "lib/glew32.lib")
#include "cg.h"

void startup();
void render();
void shutdown();

struct scene {
	int width = 800, height = 600;
	GLuint rendering_program;
	GLuint vertex_array_object;
};

scene sc;
void render()
{
	const GLfloat color[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);

	glUseProgram(sc.rendering_program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void idle() { glutPostRedisplay(); }

void startup()
{
	/**** Shaders as variables */

	sc.rendering_program = compile_shaders("v1.glsl", "f1.glsl");

	/* Vertex Array Object */
	glGenVertexArrays(1, &sc.vertex_array_object);
	glBindVertexArray(sc.vertex_array_object);
}

void shutdown()
{
	glDeleteVertexArrays(1, &sc.vertex_array_object); 
	glDeleteProgram(sc.rendering_program);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(sc.width, sc.height);
	glutCreateWindow("Triangle");
	glewInit();

	//version();
	startup();
	glutDisplayFunc(render);
	glutIdleFunc(idle);

	glutMainLoop();

	system("pause");

	shutdown();
	return 0;
}