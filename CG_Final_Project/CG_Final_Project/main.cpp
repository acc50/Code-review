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
float AtX = 0.0f, AtY = 0.0f, angleZ = 0.0f;
EViewPoint view_point = E_DEFAULT_VIEW;
float thronTime=0.0f;

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

	init_wall();				// 벽 좌표 설정

	InitProgram(ShaderProgram);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(InputKey);
	//glutPassiveMotionFunc(Mouse);
	glutTimerFunc(10, Timer, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void Timer(int a)
{

	if (thronTime > 0.6f)
		thronTime = -1.0f;
	thronTime += 0.1f;
	glutPostRedisplay();
	glutTimerFunc(100, Timer, 1);
}
GLvoid drawScene()
{
	//
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(ShaderProgram);
	view(ShaderProgram, view_point, cameraX, cameraY, cameraZ, AtX, AtY, angleZ);
	Myprojection(ShaderProgram, view_point);

	draw_map(ShaderProgram, VBO, EBO,ConVBO,ConEBO);

	//임시 플레이어 위치
	draw_wall(ShaderProgram, VBO, EBO, cameraX, cameraZ, 0.5f, 0.5f);

	float r = 3.0f;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f);
	glm::vec4 at=glm::vec4(cameraX, cameraY, cameraZ, 1.0f);
	tm = glm::translate(tm, glm::vec3(cameraX, cameraY, cameraZ));
	rm = glm::rotate(tm,glm::radians(angleZ), glm::vec3(0.0f, 1.0f, 0.0f));
	tm = glm::translate(model, glm::vec3(cameraX, 0.0f, 0.0f));
	at = rm*tm * at;
	//임시 카메라가 보는점 위치 (at)
	draw_At(ShaderProgram, VBO, EBO,at.x, at.z, 0.5f, 0.5f);
	
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
		break;
	case 'z':
		break;
	case 'x':
		break;
	case 'q':
		angleZ += 1.1f;
		break;
	case 'e':
		angleZ -= 1.1f;
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
		//std::cout << AtX + (float)x << std::endl;
		//std::cout << "dx" << dx << std::endl;


}