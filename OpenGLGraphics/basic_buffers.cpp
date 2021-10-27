#include "cg.h"
#include "time.h"

void startup(); // 초기에 OpenGL 파이프라인, 버퍼 생성
void render(); // 디스플레이 콜백
void shutdown();

struct scene {
	int width = 800, height = 600;
	GLuint rendering_program; // 셋업한 전체 파이프라인이 들어감
	GLuint vertex_array_object; // 통로를 만든다?
};

scene sc;
				   
void startup()
{

	//--------- EXAMPLE1----------------------------------------------------
	// feeding vertex shaders from buffers 
	
	sc.rendering_program = compile_shaders("v_buffers1.glsl", "f_buffers1.glsl");

	// Vertex Array 만들고
	// Generate Vertex Array Object, Bind Vertex Array Object
	// Vertex Array Object 
	glGenVertexArrays(1, &sc.vertex_array_object);
	glBindVertexArray(sc.vertex_array_object);

	float vertices[12] = { 0.25, -0.25, 0.5, 1.0,
						-0.25, -0.25, 0.5, 1.0,
						0.25, 0.25, 0.5, 1.0 };

	// Buffer 만들고
	GLuint buffer;
	glGenBuffers(1, &buffer);

	// First, bind our buffer object to the GL_ARRAY_BUFFER binding
	// The subsequent call to glVertexAttribPointer will reference this buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// AttributeLocation에 포인터 주고 enable
	// Attribute 0, four components, floating-point data, non-normalized,
	// tightly packed, offset zero
	GLuint vPosition = glGetAttribLocation(sc.rendering_program, "vPosition");
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, ((GLvoid*)(0)));
	glEnableVertexAttribArray(vPosition); 
	
	
	//------------------------------------------------------------------------
	// EXAMPLE2
	// Separate attribute

	// 얘는 버퍼 두개 만듬
	
	sc.rendering_program = compile_shaders("v_buffers2.glsl", "f_buffers2.glsl");

	GLuint buffer[2];
	const GLfloat positions[] = {0.25, -0.25, 0.5, 1.0,
									-0.25, -0.25, 0.5, 1.0,
									0.25, 0.25, 0.5, 1.0};
	const GLfloat colors[] = {1.0, 0.0, 0.0, 1.0,
								  0.0, 1.0, 0.0, 1.0,
								  0.0, 0.0, 1.0, 1.0};

	//첫번째 버퍼에는 포지션 넘겨주고
	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	GLuint vPosition = glGetAttribLocation(sc.rendering_program, "vPosition");
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vPosition);

	//두번째 버퍼에는 컬러 넘겨줌
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	GLuint vColor = glGetAttribLocation(sc.rendering_program, "vColor");
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE,0, NULL);
	glEnableVertexAttribArray(vColor);
	
	
	
//------------------------------------------------------------------------
	// EXAMPLE3
	// Multiple Buffer Object (interleaved attributes) 
	// 버퍼 하나만 생성하고 interleaved attributes(버퍼에서 어느 위치를 읽어들일지 지정)
	
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
	glGenBuffers(1, &buffer); //버퍼 이름 예약
	glBindBuffer(GL_ARRAY_BUFFER, buffer); //OpenGL과 버퍼 바인딩
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
	// 유니폼 넘겨주는 예제???

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

	glUseProgram(sc.rendering_program); //sc.rendering_program 파이프라인을 사용하겠다 ??
	glDrawArrays(GL_TRIANGLES, 0, 3); // 삼각형을 그려라! 삼각형으로 primitive 세팅을 하고 0~3까지 버텍스 어레이가 3개 동시 호출. vertices 12개였으니 4개 4개 4개씩 
	glutSwapBuffers();
}

void shutdown()
{
	glDeleteVertexArrays(1, &sc.vertex_array_object);
	glDeleteProgram(sc.rendering_program);
}

int main(int argc, char **argv)
{
	//main의 구조는 항상 같다.

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA |GLUT_DOUBLE);
	
	//오픈지엘 세팅에 필요한 부분인데 안써도 된다고 한다.
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_DEBUG);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	
	glutInitWindowSize(800, 600);
	glutCreateWindow("Basic Buffer Examples");
	glewInit();
	version();

	startup(); // startup 먼저 호출, 그래픽스 파이프라인 셋업, 버퍼 만들기, vertex array object 만들기
	glutDisplayFunc(render); // display 콜백. 렌더해서 그림을 그려줌

	glutMainLoop(); // 메인루프
	shutdown(); // 끝나기 직전에 셧다운
	return 0;
}
