#include "cg.h"
#include "time.h"

void startup(); // �ʱ⿡ OpenGL ����������, ���� ����
void render(); // ���÷��� �ݹ�
void shutdown();

struct scene {
	int width = 800, height = 600;
	GLuint rendering_program; // �¾��� ��ü ������������ ��
	GLuint vertex_array_object; // ��θ� �����?
};

scene sc;
				   
void startup()
{

	//--------- EXAMPLE1----------------------------------------------------
	// feeding vertex shaders from buffers 
	
	sc.rendering_program = compile_shaders("v_buffers1.glsl", "f_buffers1.glsl");

	// Vertex Array �����
	// Generate Vertex Array Object, Bind Vertex Array Object
	// Vertex Array Object 
	glGenVertexArrays(1, &sc.vertex_array_object);
	glBindVertexArray(sc.vertex_array_object);

	float vertices[12] = { 0.25, -0.25, 0.5, 1.0,
						-0.25, -0.25, 0.5, 1.0,
						0.25, 0.25, 0.5, 1.0 };

	// Buffer �����
	GLuint buffer;
	glGenBuffers(1, &buffer);

	// First, bind our buffer object to the GL_ARRAY_BUFFER binding
	// The subsequent call to glVertexAttribPointer will reference this buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// AttributeLocation�� ������ �ְ� enable
	// Attribute 0, four components, floating-point data, non-normalized,
	// tightly packed, offset zero
	GLuint vPosition = glGetAttribLocation(sc.rendering_program, "vPosition");
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, ((GLvoid*)(0)));
	glEnableVertexAttribArray(vPosition); 
	
	
	//------------------------------------------------------------------------
	// EXAMPLE2
	// Separate attribute

	// ��� ���� �ΰ� ����
	
	sc.rendering_program = compile_shaders("v_buffers2.glsl", "f_buffers2.glsl");

	GLuint buffer[2];
	const GLfloat positions[] = {0.25, -0.25, 0.5, 1.0,
									-0.25, -0.25, 0.5, 1.0,
									0.25, 0.25, 0.5, 1.0};
	const GLfloat colors[] = {1.0, 0.0, 0.0, 1.0,
								  0.0, 1.0, 0.0, 1.0,
								  0.0, 0.0, 1.0, 1.0};

	//ù��° ���ۿ��� ������ �Ѱ��ְ�
	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	GLuint vPosition = glGetAttribLocation(sc.rendering_program, "vPosition");
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vPosition);

	//�ι�° ���ۿ��� �÷� �Ѱ���
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	GLuint vColor = glGetAttribLocation(sc.rendering_program, "vColor");
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE,0, NULL);
	glEnableVertexAttribArray(vColor);
	
	
	
//------------------------------------------------------------------------
	// EXAMPLE3
	// Multiple Buffer Object (interleaved attributes) 
	// ���� �ϳ��� �����ϰ� interleaved attributes(���ۿ��� ��� ��ġ�� �о������ ����)
	
	//Graphics pipeline setup
	sc.rendering_program = compile_shaders("v_buffers2.glsl", "f_buffers2.glsl");

	glGenVertexArrays(1, &sc.vertex_array_object);
	glBindVertexArray(sc.vertex_array_object);

	struct vertex { float x, y, z, w, r, g, b, a; };
	GLuint buffer;
	static const vertex vertices[] = { 0.25, -0.25, 0.5,1.0, 1.0, 0.0, 0.0, 1.0, 
									-0.25, -0.25, 0.5, 1.0,  0.0, 1.0, 0.0,1.0, 
									0.25, 0.25, 0.5,1.0,  0.0, 0.0, 1.0, 1.0 };
	// allocate and initialize a buffer object
	glGenBuffers(1, &buffer); //���� �̸� ����
	glBindBuffer(GL_ARRAY_BUFFER, buffer); //OpenGL�� ���� ���ε�
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Allocate Storage

	// set up two vertex attributes - first positions
	GLuint vPosition = glGetAttribLocation(sc.rendering_program, "vPosition");
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, x));
	glEnableVertexAttribArray(vPosition);
	// now colors
	GLuint vColor = glGetAttribLocation(sc.rendering_program, "vColor");
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, r));
	glEnableVertexAttribArray(vColor);
	
	/*
//------------------------------------------------
	// Uniforms
	// ������ �Ѱ��ִ� ����???

	//  Setting Uniform Arrays 
	GLint locTime, locIndex, locColor, locFlag;
	locTime = glGetUniformLocation(sc.rendering_program, "fTime");
	locIndex = glGetUniformLocation(sc.rendering_program, "iIndex");
	locColor = glGetUniformLocation(sc.rendering_program, "vColorValue");
	locFlag = glGetUniformLocation(sc.rendering_program, "bSomeFlag");

	glUseProgram(sc.rendering_program);
	glUniform1f(locTime, 45.2f);
	glUniform1i(locIndex, 42);
	glUniform4f(locColor, 1.0f, 0.0f, 0.0f, 1.0f);
	glUniform1i(locFlag, GL_FALSE);*/
}

void render()
{
	const GLfloat color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);

	glUseProgram(sc.rendering_program); //sc.rendering_program ������������ ����ϰڴ� ??
	glDrawArrays(GL_TRIANGLES, 0, 3); // �ﰢ���� �׷���! �ﰢ������ primitive ������ �ϰ� 0~3���� ���ؽ� ��̰� 3�� ���� ȣ��. vertices 12�������� 4�� 4�� 4���� 
	glutSwapBuffers();
}

void shutdown()
{
	glDeleteVertexArrays(1, &sc.vertex_array_object);
	glDeleteProgram(sc.rendering_program);
}

int main(int argc, char **argv)
{
	//main�� ������ �׻� ����.

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA |GLUT_DOUBLE);
	
	//�������� ���ÿ� �ʿ��� �κ��ε� �Ƚᵵ �ȴٰ� �Ѵ�.
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_DEBUG);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	
	glutInitWindowSize(800, 600);
	glutCreateWindow("Basic Buffer Examples");
	glewInit();
	version();

	startup(); // startup ���� ȣ��, �׷��Ƚ� ���������� �¾�, ���� �����, vertex array object �����
	glutDisplayFunc(render); // display �ݹ�. �����ؼ� �׸��� �׷���

	glutMainLoop(); // ���η���
	shutdown(); // ������ ������ �˴ٿ�
	return 0;
}
