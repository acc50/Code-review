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
float thronTime=0.0f;


void Mouse(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void PassiveMouse(int x, int y);

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

	if (thronTime > 0.6f)
		thronTime = -1.0f;
	thronTime += 0.1f;
	glutPostRedisplay();
	glutTimerFunc(100, Timer, 1);
}
GLvoid drawScene()
{
	//
	glClearColor(1.0f, 1.0f,1.0f, 1.0f);

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