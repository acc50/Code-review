<<<<<<< HEAD
=======
#include <Windows.h>
#include "InitApp.h"
#include "Pacman.h"

#define WINDOW_POSITION 100		// À©µµ¿ì°¡ ½ºÅ©¸°ÀÇ ¾îµğ¿¡¼­ ½ÃÀÛÇÏ´ÂÁö -> ½ºÅ©¸° ÁÂ»ó´Ü ±âÁØ x,x ¿¡¼­ À©µµ¿ì°¡ ¿­¸²

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
GLfloat tempx = 0.0f, tempy = 0.0f;		// ÀÌÀüÀÇ ¸¶¿ì½º °ª

glm::vec3 EYE = glm::vec3(0.0f, 1.0f, 0.5f);
glm::vec3 AT = glm::vec3(-1.0f, 1.0f, 0.5f);
glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 T_EYE = glm::vec3(0.0f, 20.0f, 0.01f);		// Å¾ºä±âÁØ Ä«¸Ş¶ó EYE
glm::vec3 T_AT = glm::vec3(0.0f, 0.0f, 0.0f);		// Å¾ºä±âÁØ Ä«¸Ş¶ó AT

bool Left = false, Right = false, Up = false, Down = false;		// Å° ÀÔ·Â
bool move = false;
bool click = false;
Pacman *pacman = new Pacman;

EViewPoint view_point = E_DEFAULT_VIEW;

void Mouse(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void Timer(int a);
void InputKey(unsigned char key, int x, int y);
void KeyUP(unsigned char key, int x, int y);
bool check_move();								// ÀÌµ¿Å°°¡ ´­·È³ª È®ÀÎÇÏ´Â ÇÔ¼ö
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

	Set_Cursor();				// Ä¿¼­ ½ÃÀÛÁöÁ¡ ¼³Á¤
	init_wall();				// º® ÁÂÇ¥ ¼³Á¤

	InitProgram(ShaderProgram);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(InputKey);			// Å°º¸µå ÀÔ·Â
	glutKeyboardUpFunc(KeyUP);			// Å°º¸µå ¶¼´Â °Í
	glutMouseFunc(Mouse);				// ¸¶¿ì½º Å¬¸¯
	glutMotionFunc(MouseMotion);
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

	if(move)			// ¿òÁ÷ÀÌ´Â »óÅÂ¸é Å¸ÀÌ¸Ó ÀçÈ£Ãâ
		glutTimerFunc(10, Timer, a);
}

GLvoid drawScene()
{
	//
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(ShaderProgram);


	view(ShaderProgram, view_point, EYE, AT, UP, T_EYE, T_AT);	// Ä«¸Ş¶ó 

	Myprojection(ShaderProgram, view_point);

	draw_map(ShaderProgram, VBO, EBO);

	//ÀÓ½Ã ÇÃ·¹ÀÌ¾î À§Ä¡
	//draw_wall(ShaderProgram, VBO, EBO, EYE.x, EYE.z, 0.5f, 0.5f);		// Ä«¸Ş¶óÀ§Ä¡ = Ä³¸¯ÅÍÀ§Ä¡ -> 1ÀÎÄª
	
	//ÀÓ½Ã ÇÃ·¹ÀÌ¾î À§Ä¡
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
			
		if (!move) {				// ÀÌµ¿ÁßÀÌ¸é timer ÇÔ¼ö¸¦ È£Ãâ X
			move = true;
			glutTimerFunc(10, Timer, 1);
		}

		break;

	case 'a':
		Left = true;

		if (!move) {				// ÀÌµ¿ÁßÀÌ¸é timer ÇÔ¼ö¸¦ È£Ãâ X
			move = true;
			glutTimerFunc(10, Timer, 1);
		}

		break;

	case 's':
		Down = true;

		if (!move) {				// ÀÌµ¿ÁßÀÌ¸é timer ÇÔ¼ö¸¦ È£Ãâ X
			move = true;
			glutTimerFunc(10, Timer, 1);
		}

		break;

	case 'd':
		Right = true;

		if (!move) {				// ÀÌµ¿ÁßÀÌ¸é timer ÇÔ¼ö¸¦ È£Ãâ X
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

		if (!check_move()) {		// ÀÌµ¿ÇÏÁö ¾ÊÀ¸¸é move ÇÔ¼ö¸¦ false·Î ¸¸µë
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

		GLfloat mx = (GLfloat)(x - width) / (GLfloat)width;			// ¸¶¿ì½º ÀÌµ¿ÇÑ ÁÂÇ¥
		GLfloat my = (GLfloat)(height - y) / (GLfloat)height;


		// ÇöÀç ÇÁ·¹ÀÓ°ú ÀÌÀüÇÁ·¹ÀÓÀÇ ¸¶¿ì½º ÁÂÇ¥ Â÷ÀÌ
		xAngle += (my - tempy) * 3.6;				// À§¾Æ·¡ ÀÌµ¿ ½Ã xÃà ±âÁØ È¸Àü		µÚÀÇ ¼ıÀÚ´Â ¹èÀ²
		yAngle += (mx - tempx) / 2.0;				// ÁÂ¿ì ÀÌµ¿½Ã yÃà ±âÁØ È¸Àü


		std::cout << mx << " " << my << " " << tempx << " " << tempy << std::endl;



		glm::mat4 r = glm::mat4(1.0f);		// È¸Àü

		r = glm::rotate(r, glm::radians(1.0f), glm::vec3(xAngle, yAngle, 0.0f));

		glm::mat3 rm = glm::mat3(r);		// À§ÀÇ È¸ÀüÇà·Ä¿¡¼­ 3x3 ºÎºĞ¸¸ µû¿È


		// AT ÀÇ EYE ±âÁØ È¸Àü
		AT = AT - EYE;		// EYE¸¦ ¿øÁ¡ÀÌµ¿
		AT = AT * rm;		// ATÀ» È¸Àü
		AT = AT + EYE;		// ÀÌµ¿Çß´ø ¸¸Å­ ´Ù½Ã ¿ªÀÌµ¿

		AT.y += xAngle;

		xAngle = 0.0f;
		yAngle = 0.0f;

		tempx = mx;
		tempy = my;

		glutPostRedisplay();
	}
}

bool check_move()		// ÀÌµ¿Å°°¡ ´­·ÁÀÖÀ¸¸é true, ¾Æ´Ï¸é false
{
	if (Left || Right || Up || Down)
		return true;
	else
		return false;
}

void Set_Cursor()
{
	int width = WINDOW_WIDTH / 2;
	int height = WINDOW_HEIGHT / 2;

	int x = WINDOW_WIDTH / 2 + WINDOW_POSITION + 11;
	int y = WINDOW_HEIGHT / 2 + WINDOW_POSITION + 31;

	SetCursorPos(x, y);		// ½ÃÀÛ ¸¶¿ì½º Ä¿¼­ À§Ä¡ ¼³Á¤


	//tempx = (GLfloat)(x - width) / width;			// ½ÃÀÛ ¸¶¿ì½º À§Ä¡ÀÇ openGL xÁÂÇ¥¸¦ ¹ŞÀ½
	//tempy = (GLfloat)(height - y) / height;		// ½ÃÀÛ ¸¶¿ì½º À§Ä¡ÀÇ openGL yÁÂÇ¥¸¦ ¹ŞÀ½

	tempx = 0.0f;
	tempy = 0.0f;
}
>>>>>>> parent of 7e56ed6... ì¹´ë©”ë¼ êµ¬í˜„
