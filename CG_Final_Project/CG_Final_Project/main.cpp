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

glm::vec3 T_EYE = glm::vec3(0.0f, 20.0f, 0.01f);		// ž����� ī�޶� EYE
glm::vec3 T_AT = glm::vec3(0.0f, 0.0f, 0.0f);		// ž����� ī�޶� AT

bool Left = false, Right = false, Up = false, Down = false;		// Ű �Է�
bool move = false;
Pacman *pacman = new Pacman;

EViewPoint view_point = E_DEFAULT_VIEW;
void Mouse(int x, int y);
void Timer(int a);
void InputKey(unsigned char key, int x, int y);
void KeyUP(unsigned char key, int x, int y);
bool check_move();								// �̵�Ű�� ���ȳ� Ȯ���ϴ� �Լ�

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

	if(move)			// �����̴� ���¸� Ÿ�̸� ��ȣ��
		glutTimerFunc(10, Timer, a);
}

GLvoid drawScene()
{
	//
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(ShaderProgram);


	view(ShaderProgram, view_point, EYE, AT, UP, T_EYE, T_AT);	// ī�޶� 

	Myprojection(ShaderProgram, view_point);

	draw_map(ShaderProgram, VBO, EBO);

	//�ӽ� �÷��̾� ��ġ
	//draw_wall(ShaderProgram, VBO, EBO, EYE.x, EYE.z, 0.5f, 0.5f);		// ī�޶���ġ = ĳ������ġ -> 1��Ī
	
	//�ӽ� �÷��̾� ��ġ
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
			
		if (!move) {				// �̵����̸� timer �Լ��� ȣ�� X
			move = true;
			glutTimerFunc(10, Timer, 1);
		}

		break;

	case 'a':
		Left = true;

		if (!move) {				// �̵����̸� timer �Լ��� ȣ�� X
			move = true;
			glutTimerFunc(10, Timer, 1);
		}

		break;

	case 's':
		Down = true;

		if (!move) {				// �̵����̸� timer �Լ��� ȣ�� X
			move = true;
			glutTimerFunc(10, Timer, 1);
		}

		break;

	case 'd':
		Right = true;

		if (!move) {				// �̵����̸� timer �Լ��� ȣ�� X
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

		if (!check_move) {		// �̵����� ������ move �Լ��� false�� ����
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

bool check_move()		// �̵�Ű�� ���������� true, �ƴϸ� false
{
	if (Left || Right || Up || Down)
		return true;
	else
		return false;
}