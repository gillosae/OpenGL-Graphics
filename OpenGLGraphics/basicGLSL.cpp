#include "cg.h"

#include <fstream>
#include <string>
#pragma warning(disable:4996)

using std::ifstream;
using std::string;

//version check
void version() {
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	GLint major, minor;

	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	cout << "GL Vendor  :" << vendor << endl;
	cout << "GL Renderer : " << renderer << endl;
	cout << "GL Version(string) :" << version << endl;
	cout << "GL Version(integer) : " << major << "." << minor << endl;
	cout << "GLSL Version : " << glslVersion << endl;
	cout << "//-------------------------------------" << endl;

}

//Shaders
//Create a Null..
static char* readShaderSource(const char* shaderFile) {
	string VertexShaderCode;
	ifstream VertexShaderStream(shaderFile, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		cout << "Impossible to open" << shaderFile << endl;
		getchar();
		return 0;

	}

	char* buf = new char[VertexShaderCode.length() + 1];
	strcpy(buf, VertexShaderCode.c_str());
	return buf;
}

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