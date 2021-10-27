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

void make_house() {
	/*int index = 0;

	float green[4] = { 0.0, 1.0, 0.0, 1.0 };
	float purple[4] = { 1.0, 0.0, 1.0, 1.0 };
	float yellow[4] = { 1.0, 1.0, 0.0, 1.0 };

	triangle(0.15, 0.2, 0.0, 0.0, 0.3, 0.0, index, green);
	index += 3;
	rect(0.0, 0.0, 0.3, -0.3, index, yellow);
	index += 6;
	rect(0.1, -0.15, 0.2, -0.3, index, purple);
	index += 6;*/
}

// house, car, robot
void startup()
{
	// Separate attribute
	sc.rendering_program = compile_shaders("v_buffers2.glsl", "f_buffers2.glsl");

	GLuint buffer[2];
	//HOUSE
	
	const GLfloat positions[] = {
		0.25, -0.25, 0.5, 1.0,
		-0.25, -0.25, 0.5, 1.0,
		-0.25, 0.25, 0.5, 1.0,

		0.25, 0.25, 0.5, 1.0,
		0.25, -0.25, 0.5, 1.0,
		-0.25, 0.25, 0.5, 1.0,

		-0.25, 0.25, 0.5, 1.0,
		0.0, 0.5, 0.5, 1.0,
		0.25, 0.25, 0.5, 1.0,

		0.12, -0.25, 0.5, 1.0,
		-0.12, -0.25, 0.5, 1.0,
		-0.12, 0.1, 0.5, 1.0,

		-0.12, 0.1, 0.5, 1.0,
		0.12, 0.1, 0.5, 1.0,
		0.12, -0.25, 0.5, 1.0
	};

	const GLfloat colors[] = { 

		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,

		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,

		1.0, 0.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 1.0,

		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,

		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,

	};
	

	//CAR
	/*
	const GLfloat positions[] = {
		-0.25, 0.0, 0.5, 1.0,
		-0.25, 0.25, 0.5, 1.0,
		0.25, 0, 0.5, 1.0,

		0.25, 0.0, 0.5, 1.0,
		-0.25, 0.25, 0.5, 1.0,
		0.25, 0.25, 0.5, 1.0,

		0.5, 0.0, 0.5, 1.0,
		0.5, -0.25, 0.5, 1.0,
		-0.5, 0.0, 0.5, 1.0,

		-0.5, 0.0, 0.5, 1.0,
		-0.5, -0.25, 0.5, 1.0,
		0.5, -0.25, 0.5, 1.0,

		0.2, -0.25, 0.5, 1.0,
		0.1, -0.35, 0.5, 1.0,
		-0.0, -0.25, 0.5, 1.0,

		0.0, -0.25, 0.5, 1.0,
		0.1, -0.15, 0.5, 1.0,
		0.2, -0.25, 0.5, 1.0,

		-0.2, -0.25, 0.5, 1.0,
		-0.1, -0.35, 0.5, 1.0,
		0.0, -0.25, 0.5, 1.0,

		0.0, -0.25, 0.5, 1.0,
		-0.1, -0.15, 0.5, 1.0,
		-0.2, -0.25, 0.5, 1.0,

	};
	const GLfloat colors[] = {
		0.0, 0.0, 0.8, 1.0,
		0.0, 0.0, 0.6, 1.0,
		0.0, 0.0, 0.7, 1.0,

		0.0, 0.0, 0.8, 1.0,
		0.0, 0.0, 0.6, 1.0,
		0.0, 0.0, 0.7, 1.0,

		0.0, 0.0, 0.8, 1.0,
		0.0, 0.0, 0.6, 1.0,
		0.0, 0.0, 0.7, 1.0,

		0.0, 0.0, 0.8, 1.0,
		0.0, 0.0, 0.6, 1.0,
		0.0, 0.0, 0.7, 1.0,

		0.0, 1.0, 0.8, 1.0,
		0.0, 1.0, 0.6, 1.0,
		0.0, 1.0, 0.7, 1.0,

		0.0, 1.0, 0.8, 1.0,
		0.0, 1.0, 0.6, 1.0,
		0.0, 1.0, 0.7, 1.0,

		0.0, 1.0, 0.8, 1.0,
		0.0, 1.0, 0.6, 1.0,
		0.0, 1.0, 0.7, 1.0,

		0.0, 1.0, 0.8, 1.0,
		0.0, 1.0, 0.6, 1.0,
		0.0, 1.0, 0.7, 1.0,
	};
	*/

	//ROBOT
	/*
	const GLfloat positions[] = {
		0.4, 0.0, 0.5, 1.0,
		-0.4, 0.0, 0.5, 1.0,
		-0.4, 0.3, 0.5, 1.0,

		-0.4, 0.3, 0.5, 1.0,
		0.4, 0.3, 0.5, 1.0,
		0.4, 0.0, 0.5, 1.0,

		-0.5, 0.0, 0.5, 1.0,
		0.5, 0.0, 0.5, 1.0,
		0.5, -0.5, 0.5, 1.0,

		0.5, -0.5, 0.5, 1.0,
		-0.5, -0.5, 0.5, 1.0,
		-0.5, 0.0, 0.5, 1.0,

		0.6, 0.0, 0.5, 1.0,
		0.6, -0.3, 0.5, 1.0,
		0.5, 0.0, 0.5, 1.0,

		0.5, 0.0, 0.5, 1.0,
		0.6, -0.3, 0.5, 1.0,
		0.5, -0.3, 0.5, 1.0,

		-0.6, 0.0, 0.5, 1.0,
		-0.6, -0.3, 0.5, 1.0,
		-0.5, 0.0, 0.5, 1.0,

		-0.5, 0.0, 0.5, 1.0,
		-0.6, -0.3, 0.5, 1.0,
		-0.5, -0.3, 0.5, 1.0,

		0.2, -0.5, 0.5, 1.0,
		0.4, -0.5, 0.5, 1.0,
		0.4, -0.8, 0.5, 1.0,

		0.2, -0.5, 0.5, 1.0,
		0.4, -0.8, 0.5, 1.0,
		0.2, -0.8, 0.5, 1.0,

		-0.2, -0.5, 0.5, 1.0,
		-0.4, -0.5, 0.5, 1.0,
		-0.4, -0.8, 0.5, 1.0,

		-0.2, -0.5, 0.5, 1.0,
		-0.4, -0.8, 0.5, 1.0,
		-0.2, -0.8, 0.5, 1.0,

		0.25, 0.3, 0.5, 1.0,
		0.3, 0.25,0.5, 1.0,
		0.2, 0.25,0.5, 1.0,

		0.25, 0.2, 0.5, 1.0,
		0.3, 0.25,0.5, 1.0,
		0.2, 0.25,0.5, 1.0,

		-0.25, 0.3, 0.5, 1.0,
		-0.3, 0.25,0.5, 1.0,
		-0.2, 0.25,0.5, 1.0,

		-0.25, 0.2, 0.5, 1.0,
		-0.3, 0.25,0.5, 1.0,
		-0.2, 0.25,0.5, 1.0,

		0.25, 0.1,0.5, 1.0,
		-0.25, 0.1,0.5, 1.0,
		-0.25, 0.05,0.5, 1.0,

		0.25, 0.1,0.5, 1.0,
		-0.25, 0.1,0.5, 1.0,
		0.25, 0.05,0.5, 1.0,
	};
	const GLfloat colors[] = {
		0.3, 0.3, 0.3, 1.0,
		0.4, 0.4, 0.4, 1.0,
		0.5, 0.5, 0.5, 1.0,

		0.3, 0.3, 0.3, 1.0,
		0.4, 0.4, 0.4, 1.0,
		0.5, 0.5, 0.5, 1.0,

		0.3, 0.3, 0.3, 1.0,
		0.4, 0.4, 0.4, 1.0,
		0.5, 0.5, 0.5, 1.0,

		0.3, 0.3, 0.3, 1.0,
		0.4, 0.4, 0.4, 1.0,
		0.5, 0.5, 0.5, 1.0,

		0.3, 0.3, 0.3, 1.0,
		0.4, 0.4, 0.4, 1.0,
		0.5, 0.5, 0.5, 1.0,

		0.3, 0.3, 0.3, 1.0,
		0.4, 0.4, 0.4, 1.0,
		0.5, 0.5, 0.5, 1.0,

		0.3, 0.3, 0.3, 1.0,
		0.4, 0.4, 0.4, 1.0,
		0.5, 0.5, 0.5, 1.0,

		0.3, 0.3, 0.3, 1.0,
		0.4, 0.4, 0.4, 1.0,
		0.5, 0.5, 0.5, 1.0,

		0.3, 0.3, 0.3, 1.0,
		0.4, 0.4, 0.4, 1.0,
		0.5, 0.5, 0.5, 1.0,

		0.3, 0.3, 0.3, 1.0,
		0.4, 0.4, 0.4, 1.0,
		0.5, 0.5, 0.5, 1.0,

		0.3, 0.3, 0.3, 1.0,
		0.4, 0.4, 0.4, 1.0,
		0.5, 0.5, 0.5, 1.0,

		0.3, 0.3, 0.3, 1.0,
		0.4, 0.4, 0.4, 1.0,
		0.5, 0.5, 0.5, 1.0,

		0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,

		0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,

		0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,

		0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,

		0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,

		0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,


		//0.0, 0.0, 1.0, 1.0,
		//0.0, 1.0, 0.0, 1.0,
		//1.0, 0.0, 0.0, 1.0
	};
	*/
	glGenBuffers(2, buffer); // Generate buffers (버퍼 개수, 버퍼 id 포인터)

	//Vertex Position Buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]); // Assign target to generated buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW); //버퍼에 담길 데이터와 크기 지정

	GLuint vPosition = glGetAttribLocation(sc.rendering_program, "vPosition");
	
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, NULL); //Vertex attribute를 GPU가 어떻게 해석할지에 대한 정보 전달
	glEnableVertexAttribArray(vPosition);

	//Vertex Color Buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	GLuint vColor = glGetAttribLocation(sc.rendering_program, "vColor");

	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vColor);


}

// Display Callback
void render()
{
	const GLfloat color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);

	glUseProgram(sc.rendering_program); //sc.rendering_program 파이프라인을 사용하겠다 ??
	//glDrawArrays(GL_TRIANGLES, 0, 3); // 삼각형을 그려라! 삼각형으로 primitive 세팅을 하고 0~3까지 버텍스 어레이가 3개 동시 호출. vertices 12개였으니 4개 4개 4개씩 
	glDrawArrays(GL_TRIANGLES, 0, 90);
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
