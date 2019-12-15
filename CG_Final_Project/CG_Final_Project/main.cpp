#include "InitApp.h"
#include "Pacman.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLuint ShaderProgram;
GLuint ConVBO;
GLuint ConEBO;
GLuint VBO;
GLuint EBO;

float dx = 1.0f;
float dy = 1.0f;

glm::vec3 EYE = glm::vec3(0.0f, 1.0f, 0.5f);
glm::vec3 AT = glm::vec3(-1.0f, 1.0f, 0.5f);
glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 T_EYE = glm::vec3(0.0f, 20.0f, 0.01f);		// 탑뷰기준 카메라 EYE
glm::vec3 T_AT = glm::vec3(0.0f, 0.0f, 0.0f);		// 탑뷰기준 카메라 AT

bool Left = false, Right = false, Up = false, Down = false;		// 키 입력
bool move = false;
Pacman *pacman = new Pacman;

EViewPoint view_point = E_DEFAULT_VIEW;
void Mouse(int x, int y);
void Timer(int a);
void InputKey(unsigned char key, int x, int y);
void KeyUP(unsigned char key, int x, int y);
bool check_move();								// 이동키가 눌렸나 확인하는 함수

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
	glutKeyboardFunc(InputKey);			// 키보드 입력
	glutKeyboardUpFunc(KeyUP);			// 키보드 떼는 것
	//glutPassiveMotionFunc(Mouse);
	glutTimerFunc(10, Timer, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void Timer(int a)
{
	if (move) {
		pacman->Move(Up, Down, Right, Left, EYE, AT, UP);


	}


	glutPostRedisplay();

	if(move)			// 움직이는 상태면 타이머 재호출
		glutTimerFunc(10, Timer, a);
}

GLvoid drawScene()
{
	//
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(ShaderProgram);


	view(ShaderProgram, view_point, EYE, AT, UP, T_EYE, T_AT);	// 카메라 

	Myprojection(ShaderProgram, view_point);

	draw_map(ShaderProgram, VBO, EBO);

	//임시 플레이어 위치
	//draw_wall(ShaderProgram, VBO, EBO, EYE.x, EYE.z, 0.5f, 0.5f);		// 카메라위치 = 캐릭터위치 -> 1인칭
	
	//임시 플레이어 위치
	pacman->Draw(ShaderProgram, VBO, EBO);


	float r = 3.0f;


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
		Up = true;
			
		if (!move) {				// 이동중이면 timer 함수를 호출 X
			move = true;
			glutTimerFunc(10, Timer, 1);
		}

		break;

	case 'a':
		Left = true;

		if (!move) {				// 이동중이면 timer 함수를 호출 X
			move = true;
			glutTimerFunc(10, Timer, 1);
		}

		break;

	case 's':
		Down = true;

		if (!move) {				// 이동중이면 timer 함수를 호출 X
			move = true;
			glutTimerFunc(10, Timer, 1);
		}

		break;

	case 'd':
		Right = true;

		if (!move) {				// 이동중이면 timer 함수를 호출 X
			move = true;
			glutTimerFunc(10, Timer, 1);
		}

		break;

	case 'z':
		break;
	case 'x':
		break;

	/*case 'q':
		angleZ += 1.1f;
		break;
	case 'e':
		angleZ -= 1.1f;
		break;*/

	default:
		break;
	}
}

void KeyUP(unsigned char key, int x, int y)
{
	switch (key){
	case 'w':
		Up = false;

		if (!check_move) {		// 이동하지 않으면 move 함수를 false로 만듬
			move = false;
		}

		break;

	case 'a':
		Left = false;

		if (!check_move) {
			move = false;
		}

		break;

	case 's':
		Down = false;

		if (!check_move) {
			move = false;
		}

		break;

	case 'd':
		Right = false;

		if (!check_move) {
			move = false;
		}

		break;

	}
}


void Mouse(int x, int y)
{


	int width = WINDOW_WIDTH / 2;
	int height = WINDOW_HEIGHT / 2;

	float value = 0.1f*dx;
	//AtX = ((float)x - (float)width) / (float)width;
	//AtY = ((float)y - (float)height) / (-1.0f*(float)height);
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

bool check_move()		// 이동키가 눌려있으면 true, 아니면 false
{
	if (Left || Right || Up || Down)
		return true;
	else
		return false;
}