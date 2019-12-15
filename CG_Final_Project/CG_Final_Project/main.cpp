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
GLfloat yaw = 0.0f, pitch = 0.0f;		// ���Ϸ� ��
GLfloat tempx = 0.0f, tempy = 0.0f;		// ������ ���콺 ��

glm::vec3 EYE = glm::vec3(0.0f, 1.0f, 0.5f);
glm::vec3 AT = glm::vec3(-1.0f, 1.0f, 0.5f);
glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 T_EYE = glm::vec3(0.0f, 20.0f, 0.01f);		// ž����� ī�޶� EYE
glm::vec3 T_AT = glm::vec3(0.0f, 0.0f, 0.0f);		// ž����� ī�޶� AT

bool Left = false, Right = false, Up = false, Down = false;		// Ű �Է�
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

	init_wall();				// �� ��ǥ ����

	InitProgram(ShaderProgram);
	glutDisplayFunc(drawScene);

	glutKeyboardFunc(InputKey);			// Ű���� �Է�
	glutKeyboardUpFunc(KeyUP);			// Ű���� ���� ��
	glutMouseFunc(Mouse);				// ���콺 Ŭ��
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

	//�ӽ� �÷��̾� ��ġ
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
	//�ӽ� ī�޶� ������ ��ġ (at)
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


		// ���� �����Ӱ� ������������ ���콺 ��ǥ ����
		xAngle = (my - tempy) * 100;				// ���Ʒ� �̵� �� x�� ���� ȸ��		���� ���ڴ� ����
		yAngle = (mx - tempx) * 100;				// �¿� �̵��� y�� ���� ȸ��

		yaw += yAngle;
		pitch += xAngle;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;


		AT.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		AT.y = sin(glm::radians(pitch));
		AT.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		// AT �� EYE ���� ȸ��
		AT = AT - EYE;		// EYE�� �����̵�

		AT.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		AT.y = sin(glm::radians(pitch));
		AT.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		AT = AT + EYE;		// �̵��ߴ� ��ŭ �ٽ� ���̵�

		tempx = mx;
		tempy = my;

		glutPostRedisplay();

}

void PassiveMouse(int x, int y)
{
	Set_Cursor();
	glutPostRedisplay();
}

bool check_move()		// �̵�Ű�� ���������� true, �ƴϸ� false
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

	SetCursorPos(x, y);		// ���� ���콺 Ŀ�� ��ġ ����

	tempx = 0.0f;
	tempy = 0.0f;
}