#include <Windows.h>
#include "InitApp.h"
#include "Pacman.h"

#define WINDOW_POSITION 100		// 윈도우가 스크린의 어디에서 시작하는지 -> 스크린 좌상단 기준 x,x 에서 윈도우가 열림

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLuint ShaderProgram;
GLuint ConVBO;
GLuint ConEBO;
GLuint VBO;
GLuint EBO;


GLfloat xAngle = 0.0f, yAngle = 0.0f;
GLfloat yaw = 0.0f, pitch = 0.0f;		// 오일러 각
GLfloat tempx = 0.0f, tempy = 0.0f;		// 이전의 마우스 값

glm::vec3 EYE = glm::vec3(0.0f, 1.0f, 0.5f);
glm::vec3 AT = glm::vec3(-1.0f, 1.0f, 0.5f);
glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 T_EYE = glm::vec3(0.0f, 20.0f, 0.01f);		// 탑뷰기준 카메라 EYE
glm::vec3 T_AT = glm::vec3(0.0f, 0.0f, 0.0f);		// 탑뷰기준 카메라 AT

bool Left = false, Right = false, Up = false, Down = false;		// 키 입력
bool move = false;
bool click = false;
Pacman *pacman = new Pacman;

EViewPoint view_point = E_DEFAULT_VIEW;

void Mouse(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void PassiveMouse(int x, int y);
void Timer(int a);
void InputKey(unsigned char key, int x, int y);
void KeyUP(unsigned char key, int x, int y);
bool check_move();								// 이동키가 눌렸나 확인하는 함수
void Set_Cursor();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(WINDOW_POSITION, WINDOW_POSITION);
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

	Set_Cursor();				// 커서 시작지점 설정
	init_wall();				// 벽 좌표 설정

	InitProgram(ShaderProgram);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(InputKey);			// 키보드 입력
	glutKeyboardUpFunc(KeyUP);			// 키보드 떼는 것
	glutMouseFunc(Mouse);				// 마우스 클릭
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(PassiveMouse);
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

	case 'q':
		glutLeaveMainLoop();
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void KeyUP(unsigned char key, int x, int y)
{
	switch (key){
	case 'w':
		Up = false;

		if (!check_move()) {		// 이동하지 않으면 move 함수를 false로 만듬
			move = false;
		}

		break;

	case 'a':
		Left = false;

		if (!check_move()) {
			move = false;
		}

		break;

	case 's':
		Down = false;

		if (!check_move()) {
			move = false;
		}

		break;

	case 'd':
		Right = false;

		if (!check_move()) {
			move = false;
		}

		break;

	}

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		click = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		click = false;
		Set_Cursor();
	}
	glutPostRedisplay();
}

void MouseMotion(int x, int y)
{
	if (click) {
		int width = WINDOW_WIDTH / 2;
		int height = WINDOW_HEIGHT / 2;

		GLfloat mx = (GLfloat)(x - width) / (GLfloat)width;			// 마우스 이동한 좌표
		GLfloat my = (GLfloat)(height - y) / (GLfloat)height;


		// 현재 프레임과 이전프레임의 마우스 좌표 차이
		xAngle = (my - tempy) * 100;				// 위아래 이동 시 x축 기준 회전		뒤의 숫자는 배율
		yAngle = (mx - tempx) * 100;				// 좌우 이동시 y축 기준 회전

		yaw += yAngle;
		pitch += xAngle;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;


		AT.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		AT.y = sin(glm::radians(pitch));
		AT.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		// AT 의 EYE 기준 회전
		AT = AT - EYE;		// EYE를 원점이동

		AT.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		AT.y = sin(glm::radians(pitch));
		AT.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		AT = AT + EYE;		// 이동했던 만큼 다시 역이동

		tempx = mx;
		tempy = my;

		glutPostRedisplay();
	}
}

void PassiveMouse(int x, int y)
{
	Set_Cursor();
	glutPostRedisplay();
}

bool check_move()		// 이동키가 눌려있으면 true, 아니면 false
{
	if (Left || Right || Up || Down)
		return true;
	else
		return false;
}

void Set_Cursor()
{
	int x = WINDOW_WIDTH / 2 + WINDOW_POSITION + 11;
	int y = WINDOW_HEIGHT / 2 + WINDOW_POSITION + 31;

	SetCursorPos(x, y);		// 시작 마우스 커서 위치 설정

	tempx = 0.0f;
	tempy = 0.0f;
}