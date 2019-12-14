#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm.hpp>
#include <gl/ext.hpp>
#include <gl/gtc/matrix_transform.hpp>
#include <iostream>
#include <Windows.h>
#include <vector>
#include "file2buf.h"
#include "InitApp.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLuint ShaderProgram;
GLuint ConVBO;
GLuint ConEBO;
GLuint VBO;
GLuint EBO;

float cameraX = 0.0f, cameraY = 1.0f, cameraZ = 10.0f;
float dx = 1.0f;
float dy = 1.0f;
float AtX = 0.0f, AtY = 0.0f;
EViewPoint view_point = E_DEFAULT_VIEW;
void Mouse(int x, int y);
void Timer(int a);
void InputKey(unsigned char key, int x, int y);
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Example1");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glEnable(GL_CULL_FACE);
	CreateCon(ConEBO, ConVBO);
	CreateCube(ShaderProgram, EBO, VBO);

	InitProgram(ShaderProgram);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(InputKey);
	glutPassiveMotionFunc(Mouse);
	glutTimerFunc(10, Timer, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void Timer(int a)
{


	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}
GLvoid drawScene()
{
	//
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glUseProgram(ShaderProgram);
	view(ShaderProgram, view_point, cameraX, cameraY, cameraZ, AtX, AtY);
	Myprojection(ShaderProgram, view_point);

	draw_map(ShaderProgram, VBO, EBO);

	glutSwapBuffers();


}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}

void InputKey(unsigned char key, int x, int y)
{
	static bool culling = false;
	switch (key)
	{
	case '1':
		view_point = E_DEFAULT_VIEW;
		break;
	case '3':
		view_point = E_TOP_VIEW;
		break;
	case 'y':

		break;
	case 'w':
		cameraZ -= 0.1f;
		break;
	case 'a':
		cameraX -= 0.1f;
		break;
	case 's':
		cameraZ += 0.1f;
		break;
	case 'd':
		cameraX += 0.1f;
	case 'z':
		break;
	case 'x':
		break;
	default:
		break;
	}
}


void Mouse(int x, int y)
{
	
	
	int width = WINDOW_WIDTH / 2;
	int height = WINDOW_HEIGHT / 2;
	
	float value = 0.1f*dx;
	AtX = ((float)x - (float)width) / (float)width;
	AtY = ((float)y - (float)height) / (-1.0f*(float)height);
	/*if (AtX + (float)x < (float)WINDOW_WIDTH / 2.0f - 100.0f)
		dx = -1.0f;
	else if (AtX + (float)x > (float)WINDOW_WIDTH / 2.0f + 50.0f)
		dx = +1.0f;*/
	//
	//if (AtY + (float)y < (float)WINDOW_HEIGHT / 2.0f - 100.0f)
	//	dy -= 1.0f;
	//else if (AtY + (float)x > (float)WINDOW_HEIGHT / 2.0f + 50.0f)
	//	dy += 1.0f;
	std::cout << AtX + (float)x << std::endl;
	std::cout << "dx" << dx << std::endl;
	

}