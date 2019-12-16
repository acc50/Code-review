#include <Windows.h>
#include <float.h>
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
GLuint SVBO;  //구 정점정보
GLuint SNVBO; //구 노멀정보

Wall walls[WALL_COUNT];
Thorn thorns[TRAP_COUNT];
Hole holes[TRAP_COUNT];
Deceleration_Trap deceleration_traps[TRAP_COUNT];


int count = 0;

GLfloat xAngle = 0.0f, yAngle = 0.0f;
GLfloat yaw = 0.0f, pitch = 0.0f;		// 오일러 각
GLfloat tempx = 0.0f, tempy = 0.0f;		// 이전의 마우스 값

glm::vec3 EYE = glm::vec3(0.0f, 1.0f, 0.5f);
glm::vec3 AT = glm::vec3(1.0f, 1.0f, 0.5f);
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
void myTimer(int a);
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
	CreateSphere(SVBO, SNVBO);
	Set_Cursor();				// 커서 시작지점 설정
	init_wall(walls, thorns, holes, deceleration_traps);				// 벽 좌표 설정

	InitProgram(ShaderProgram);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(InputKey);			// 키보드 입력
	glutKeyboardUpFunc(KeyUP);			// 키보드 떼는 것
	glutMouseFunc(Mouse);				// 마우스 클릭
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(PassiveMouse);
	glutTimerFunc(10, myTimer, 2);
	glutTimerFunc(10, Timer, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void myTimer(int a)
{


	// ---------------------------- 함정 업데이트 부분 -----------------------------

	for (int i = 0; i < TRAP_COUNT; ++i) {
		thorns[i].Update(pacman->Get_Pos());
		holes[i].Update(pacman->Get_Pos());
	}


	// ---------------------------- 함정 업데이트 부분 -----------------------------



	// ------------------------- 함정 충돌체크 부분 -------------------------------------

	// 함정의 좌표를 받을 벡터
	glm::vec3 t_pos;		
	glm::vec3 h_pos;
	glm::vec3 d_pos;

	// 팩맨의 정보
	glm::vec3 pacman_pos = pacman->Get_Pos();
	GLfloat rsize = pacman->Get_Size();
	
	// 함정의 좌표, 사이즈를 담을 변수
	GLfloat x, z;
	GLfloat trap_size;




	// ---------------------------------- 가시 함정 ------------------------------------------------

	for (int i = 0; i < TRAP_COUNT; ++i) {
		t_pos = thorns[i].Get_Pos();
		trap_size = thorns[i].Get_Size() + 0.1f;

		x = t_pos.x;
		z = t_pos.z;

		if (is_Collision(pacman_pos.x, pacman_pos.z, rsize, x, z, trap_size, trap_size) && thorns[i].Get_State()) {		// 충돌검사


			// 충돌 시 처리 할 부분 , 충돌은 일어남


		}
	}


	// ---------------------------------- 가시 함정 ------------------------------------------------




	// ---------------------------------- 구멍 함정 ------------------------------------------------

	for (int i = 0; i < TRAP_COUNT; ++i) {
		h_pos = holes[i].Get_Pos();
		trap_size = thorns[i].Get_Size();		

		x = h_pos.x;
		z = h_pos.z;

		if (is_Collision(pacman_pos.x, pacman_pos.z, rsize, x, z, trap_size, trap_size) && holes[i].Get_State()) {		// 충돌검사


			// 충돌 시 처리 할 부분 , 충돌은 일어남  구멍 함정의 중앙 근처에 있어야 발동하도록 함


		}
	}



	// ---------------------------------- 구멍 함정 ------------------------------------------------







	// ---------------------------------- 감속 함정 ------------------------------------------------



	for (int i = 0; i < TRAP_COUNT; ++i) {
		d_pos = deceleration_traps[i].Get_Pos();
		trap_size = thorns[i].Get_Size() + 0.15f;

		x = d_pos.x;
		z = d_pos.z;

		// 초기 속도값이 30.0f
		// 충돌 && 초기속도값이면 속도를 낮춤
		if (is_Collision(pacman_pos.x, pacman_pos.z, rsize, x, z, trap_size, trap_size) && 			// 충돌검사
			(fabsf(pacman->Get_Speed() - 30.0f) <= FLT_EPSILON))
		{

			pacman->Set_Speed(100.0f);		// 속도 값으로 이동거리를 나누기 때문에 속도값이 크면느려짐
			pacman->slowdown_count = i;		// 몇번 함정에 걸린지를 알려줌

			break;
		}

		// 충돌 X && 느려진 상태면 속도 되돌림
		else if (!is_Collision(pacman_pos.x, pacman_pos.z, rsize, x, z, trap_size, trap_size) &&
			(fabsf(pacman->Get_Speed() - 100.0f) <= FLT_EPSILON) && (i == pacman->slowdown_count))		// 해당 함정에서 빠져나오면 속도 정상화
		{

			pacman->Set_Speed(30.0f);
			
		}

	}

	// ---------------------------------- 감속 함정 ------------------------------------------------



	// ------------------------- 함정 충돌체크 부분 -------------------------------------

	glutPostRedisplay();
	glutTimerFunc(100, myTimer, 2);
}

void Timer(int a)
{
	if (move) {
		pacman->Move(Up, Down, Right, Left, EYE, AT, UP);

		// -------------------------- 벽과 플레이어 충돌 -----------------------------------

		glm::vec3 w_pos;
		glm::vec3 pacman_pos = pacman->Get_Pos();

		GLfloat x, z;									// 벽의 x, z값
		GLfloat width, depth;							// 벽의 가로 세로 길이
		GLfloat rsize = pacman->Get_Size();				// 팩맨의 반지름

		GLfloat degree = 0.25f;		// 밀어낼때 판단 정도

		for (int i = 0; i < WALL_COUNT; ++i) {
			w_pos = walls[i].Get_Pos();

			x = w_pos.x;
			z = w_pos.z;

			width = walls[i].Get_Width();
			depth = walls[i].Get_Depth();



			if (is_Collision(pacman_pos.x, pacman_pos.z, rsize, x, z, width, depth)) {		// 사각형과 원의 충돌검사


				// 충돌 시 밀어내기 

				if (x + width - degree < pacman_pos.x - rsize) {		// 벽의 오른쪽에서 충돌

					pacman->Set_Pos_x(x + width + rsize);		// 벽의 오른쪽 + 반지름으로 x좌표 설정
				}

				else if (x - width + degree > pacman_pos.x + rsize) {		// 벽의 왼쪽에서 충돌

					pacman->Set_Pos_x(x - width - rsize);		// 벽의 왼쪽 - 반지름으로 x좌표 설정
				}

				if (z + depth - degree < pacman_pos.z - rsize) {		// 벽의 앞쪽에서 충돌

					pacman->Set_Pos_z(z + depth + rsize);		// 벽의 앞쪽 + 반지름으로 z좌표 설정
				}

				else if (z - depth + degree > pacman_pos.z + rsize) {		// 벽의 뒷쪽에서 충돌

					pacman->Set_Pos_z(z - depth - rsize);		// 벽의 뒷쪽 - 반지름으로 z좌표 설정
				}




			}

		}

		// -------------------------- 벽과 플레이어 충돌 -----------------------------------


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

	draw_map(ShaderProgram, VBO, EBO, ConVBO, ConEBO, walls, thorns, holes, deceleration_traps);
	
	//임시 플레이어 위치
	pacman->Draw(ShaderProgram, SVBO, SNVBO);

	draw_sphere(ShaderProgram, SVBO, SNVBO, 0.0f, 0.0f);
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