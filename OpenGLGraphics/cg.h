#pragma once
#pragma comment (lib, "lib/freeglut.lib")
#pragma comment (lib, "lib/glew32.lib")

#include <cmath>
#include <iostream>  

// WINDOWS. Mac 은 라이브러리 경로 변경 필요
#pragma comment (lib, "lib/freeglut.lib")
#pragma comment (lib, "lib/glew32.lib")

//#include "GL/glew.h"
//#include "GL/freeglut.h"
//#include "GL/freeglut_ext.h"
//#include "GL/freeglut_std.h"
//#include "GL/glut.h"
#include "glew.h"
#include "freeglut.h"
#include "freeglut_ext.h"
#include "freeglut_std.h"
#include "glut.h"

// Windows 와 Mac 모두 동일
/*
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"*/

using namespace std; 
//using namespace glm; 

void version();
GLuint compile_shaders(const char*  vsource, const char*  fsource);
