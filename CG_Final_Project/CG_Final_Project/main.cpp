#include <Windows.h>
#include <float.h>
#include "InitApp.h"
#include "Pacman.h"

#define WINDOW_POSITION 100		// �����찡 ��ũ���� ��𿡼� �����ϴ��� -> ��ũ�� �»�� ���� x,x ���� �����찡 ����

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLuint ShaderProgram;

SuperGLuint super;

Wall walls[WALL_COUNT];
Thorn thorns[TRAP_COUNT];
Hole holes[TRAP_COUNT];
Deceleration_Trap deceleration_traps[TRAP_COUNT];
WinItem win_items[WIN_COUNT];


GLfloat xAngle = 0.0f, yAngle = 0.0f;
GLfloat yaw = 0.0f, pitch = 0.0f;		// ���Ϸ� ��
GLfloat tempx = 0.0f, tempy = 0.0f;		// ������ ���콺 ��


glm::vec3 EYE = glm::vec3(0.0f, 1.0f, 0.5f);
glm::vec3 AT = glm::vec3(1.0f, 1.0f, 0.5f);
glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 T_EYE = glm::vec3(0.0f, 20.0f, 0.01f);		// ž����� ī�޶� EYE
glm::vec3 T_AT = glm::vec3(0.0f, 0.0f, 0.0f);		// ž����� ī�޶� AT

bool Left = false, Right = false, Up = false, Down = false;		// Ű �Է�
bool move = false;
bool click = false;
bool JUMP = false;
Pacman *pacman = new Pacman;
Ghost ghosts[GHOST_COUNT];

//HSJ�߰�����
int itemID[4];  //���������۾��̵�
int itemCOunt = 4;
//
EViewPoint view_point = E_DEFAULT_VIEW;

void Mouse(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void PassiveMouse(int x, int y);
void Timer(int a);
void myTimer(int a);
void JumpTimer(int a);
void InputKey(unsigned char key, int x, int y);
void KeyUP(unsigned char key, int x, int y);
bool check_move();								// �̵�Ű�� ���ȳ� Ȯ���ϴ� �Լ�
void Set_Cursor();

int main(int argc, char** argv)
{
	srand(time(NULL));
	for (int i = 0; i < 4; ++i) {
		itemID[i] = rand() % 4 + i * 4;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
	CreateCon(super.ConEBO, super.ConVBO);
	CreateCube(ShaderProgram, super.EBO, super.VBO);
	CreateSphere(super.SVBO, super.SNVBO);
	Set_Cursor();				// Ŀ�� �������� ����
	init_wall(walls, thorns, holes, deceleration_traps, win_items, ghosts);				// �� ��ǥ ����
	

	InitProgram(ShaderProgram);

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(InputKey);			// Ű���� �Է�
	glutKeyboardUpFunc(KeyUP);			// Ű���� ���� ��
	glutMouseFunc(Mouse);				// ���콺 Ŭ��
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(PassiveMouse);
	glutTimerFunc(10, myTimer, 2);
	glutTimerFunc(10, Timer, 1);
	glutTimerFunc(10, JumpTimer, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void myTimer(int a)
{
	if (!pacman->Get_is_lived()) {		// �׾�����
		pacman->Revive(EYE, AT, yaw, pitch);
	}



	// ---------------------------- ���� ������Ʈ �κ� -----------------------------

	for (int i = 0; i < TRAP_COUNT; ++i) {
		thorns[i].Update(pacman->Get_Pos());
		holes[i].Update(pacman->Get_Pos());
	}


	// ---------------------------- ���� ������Ʈ �κ� -----------------------------



	// ------------------------- ���� �浹üũ �κ� -------------------------------------

	// ������ ��ǥ�� ���� ����
	glm::vec3 t_pos;		
	glm::vec3 h_pos;
	glm::vec3 d_pos;

	// �Ѹ��� ����
	glm::vec3 pacman_pos = pacman->Get_Pos();
	GLfloat rsize = pacman->Get_Size();
	
	// ������ ��ǥ, ����� ���� ����
	GLfloat x, z;
	GLfloat trap_size;




	// ---------------------------------- ���� ���� ------------------------------------------------

	for (int i = 0; i < TRAP_COUNT; ++i) {
		t_pos = thorns[i].Get_Pos();
		trap_size = thorns[i].Get_Size() + 0.1f;

		x = t_pos.x;
		z = t_pos.z;

		if (is_Collision(pacman_pos.x, pacman_pos.z, rsize, x, z, trap_size, trap_size) && thorns[i].Get_State() && pacman->Get_is_lived()) {		// �浹�˻�


			pacman->Die();		// Die �Լ����� lifeCount �� ����, ��Ȱ�� �ڵ����� �Ͼ
								// gameover �� text ������� �ӽ� ���� �Ǿ�����
			std::cout << "�ɸ�";

		}
	}


	// ---------------------------------- ���� ���� ------------------------------------------------




	// ---------------------------------- ���� ���� ------------------------------------------------

	for (int i = 0; i < TRAP_COUNT; ++i) {
		h_pos = holes[i].Get_Pos();
		trap_size = thorns[i].Get_Size() - 0.1f;		

		x = h_pos.x;
		z = h_pos.z;

		if (is_Collision(pacman_pos.x, pacman_pos.z, rsize, x, z, trap_size, trap_size) && holes[i].Get_State()) {		// �浹�˻�

			if (pacman->is_on_floor) {		// �Ѹǿ� ���� ������ �ɷȴµ� �ٴڿ� ������
				
				pacman->Fall_Hole();

			}
		}
	}



	// ---------------------------------- ���� ���� ------------------------------------------------



	// ---------------------------------- ���� ���� ------------------------------------------------



	for (int i = 0; i < TRAP_COUNT; ++i) {
		d_pos = deceleration_traps[i].Get_Pos();
		trap_size = thorns[i].Get_Size() + 0.15f;

		x = d_pos.x;
		z = d_pos.z;

		// �ʱ� �ӵ����� 30.0f
		// �浹 && �ʱ�ӵ����̸� �ӵ��� ����
		if (is_Collision(pacman_pos.x, pacman_pos.z, rsize, x, z, trap_size, trap_size) && 			// �浹�˻�
			(fabsf(pacman->Get_Speed() - 30.0f) <= FLT_EPSILON) && pacman->is_on_floor)
		{

			pacman->Set_Speed(100.0f);		// �ӵ� ������ �̵��Ÿ��� ������ ������ �ӵ����� ũ�������
			pacman->slowdown_count = i;		// ��� ������ �ɸ����� �˷���

			break;
		}

		// �浹 X && ������ ���¸� �ӵ� �ǵ���
		else if (!is_Collision(pacman_pos.x, pacman_pos.z, rsize, x, z, trap_size, trap_size) &&
			(fabsf(pacman->Get_Speed() - 100.0f) <= FLT_EPSILON) && (i == pacman->slowdown_count))		// �ش� �������� ���������� �ӵ� ����ȭ
		{

			pacman->Set_Speed(30.0f);
			
		}

	}

	// ---------------------------------- ���� ���� ------------------------------------------------



	// ------------------------- ���� �浹üũ �κ� -------------------------------------

	glutPostRedisplay();
	glutTimerFunc(100, myTimer, 2);
}

void Timer(int a)
{
	glm::vec3 pacman_pos;
	GLfloat rsize;

	if (move) {
		pacman->Move(Up, Down, Right, Left, EYE, AT, UP);

		pacman_pos = pacman->Get_Pos();
		rsize = pacman->Get_Size() + 0.1f;			// �Ѹ��� ������

		// -------------------------- ���� �÷��̾� �浹 -----------------------------------

		glm::vec3 w_pos;

		GLfloat x, z;									// ���� x, z��
		GLfloat width, depth;							// ���� ���� ���� ����

		GLfloat degree = 0.05f;		// �о�� �Ǵ� ����,   ���� �ʹ� ������ �浹ó�� X, ���� �ʹ� ũ�� �о�� ����� ����

		for (int i = 0; i < WALL_COUNT; ++i) {
			w_pos = walls[i].Get_Pos();

			x = w_pos.x;
			z = w_pos.z;

			width = walls[i].Get_Width();
			depth = walls[i].Get_Depth();



			if (is_Collision(pacman_pos.x, pacman_pos.z, rsize, x, z, width, depth)) {		// �簢���� ���� �浹�˻�

				// �浹 �� �о�� 
				if (x + width - degree < pacman_pos.x - rsize) {		// ���� �����ʿ��� �浹

					pacman->Set_Pos_x(x + width + rsize);		// ���� ������ + ���������� x��ǥ ����
				}

				else if (x - width + degree > pacman_pos.x + rsize) {		// ���� ���ʿ��� �浹

					pacman->Set_Pos_x(x - width - rsize);		// ���� ���� - ���������� x��ǥ ����
				}

				if (z + depth - degree < pacman_pos.z - rsize) {		// ���� ���ʿ��� �浹

					pacman->Set_Pos_z(z + depth + rsize);		// ���� ���� + ���������� z��ǥ ����
				}

				else if (z - depth + degree > pacman_pos.z + rsize) {		// ���� ���ʿ��� �浹

					pacman->Set_Pos_z(z - depth - rsize);		// ���� ���� - ���������� z��ǥ ����
				}




			}

		}

		// -------------------------- ���� �÷��̾� �浹 -----------------------------------



		

		// -------------------------- �÷��̾�� ������ �浹 -----------------------------------

		glm::vec3 item_pos;

		GLfloat px, pz;		// �Ѹ� ��ġ
		GLfloat dx, dz;		// �Ѹ� �� ������ �Ÿ�
		GLfloat d;		// �������� ��

		for (int i = 0; i < WIN_COUNT; ++i) {
			item_pos = win_items[i].Get_Pos();

			x = item_pos.x;		// ������ ��ġ
			z = item_pos.z;

			px = pacman_pos.x;
			pz = pacman_pos.z;

			dx = x - px;
			dz = z - pz;
			
			d = win_items[i].Get_Size() + pacman->Get_Size();
			
			if ((dx * dx) + (dz * dz) <= (d * d) && win_items[i].is_activate) {	// ������ �� ���� ���������� �Ÿ��� ������ -> �浹
				
				win_items[i].is_activate = false;
				itemCOunt -= 1;

				if (itemCOunt == 0) {
					std::cout << "���� �¸�!" << std::endl;
				}
			}
		}



		// -------------------------- �÷��̾�� ������ �浹 -----------------------------------



	

	}

	// -------------------------- �÷��̾�� ���� �浹 -----------------------------------


	glm::vec3 ghost_pos;
	GLfloat gx, gz, p_x, p_z, d_x, d_z, d2;

	for (int i = 0; i < GHOST_COUNT; ++i) {

		ghosts[i].Update();			// ���� ������

		ghost_pos = ghosts[i].Get_Pos();
		pacman_pos = pacman->Get_Pos();

		gx = ghost_pos.x;
		gz = ghost_pos.z;

		p_x = pacman_pos.x;
		p_z = pacman_pos.z;

		d_x = gx - p_x;
		d_z = gz - p_z;

		d2 = ghosts[i].Get_Size() + pacman->Get_Size() + 0.07f;

		if ((d_x * d_x) + (d_z * d_z) <= (d2 * d2) && pacman->Get_is_lived()) {	// �浹 && �Ѹ��� ����ִٸ�

			pacman->Die();
		}
	}


	// -------------------------- �÷��̾�� ���� �浹 -----------------------------------


	glutPostRedisplay();



	glutTimerFunc(10, Timer, a);
}

void JumpTimer(int a)
{
	/// ----------------------------- ������Ʈ --------------------

	glm::vec3 pacman_pos = pacman->Get_Pos();

	pacman->Update(JUMP, EYE, AT, UP);

	if ((pacman_pos.y < 1.0f) && !pacman->is_fall && !pacman->is_on_floor) {		// y��ǥ, �Ѹ��� ������ �������ʾҴ°�, �ٴ����� ����������
		pacman->Set_Pos_y();
		pacman->Set_Jump();
		JUMP = false;				// ���� �� �ٴڿ� ��Ҵٸ� ���� false
	}



	/// ----------------------------- ������Ʈ --------------------

	glutPostRedisplay();

	glutTimerFunc(15, JumpTimer, a);
}

GLvoid drawScene()
{
	//
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(ShaderProgram);


	view(ShaderProgram, view_point, EYE, AT, UP, T_EYE, T_AT);	// ī�޶� 

	Myprojection(ShaderProgram, view_point);

	draw_map(ShaderProgram, super, walls, thorns, holes, deceleration_traps, win_items, ghosts);

	// �÷��̾� ��ġ
	pacman->Draw(ShaderProgram, super.SVBO, super.SNVBO);

	for (int i = 0; i < GHOST_COUNT; ++i) {
		ghosts[i].Draw(ShaderProgram, super.SVBO, super.SNVBO);
	}

	
	renderBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pacman->Get_lifecount(), itemCOunt);

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

	case 'w':
		Up = true;

		if (!move) {				// �̵����̸� timer �Լ��� ȣ�� X
			move = true;

		}

		break;

	case 'a':
		Left = true;

		if (!move) {				// �̵����̸� timer �Լ��� ȣ�� X
			move = true;
		}

		break;

	case 's':
		Down = true;

		if (!move) {				// �̵����̸� timer �Լ��� ȣ�� X
			move = true;
		}

		break;

	case 'd':
		Right = true;

		if (!move) {				// �̵����̸� timer �Լ��� ȣ�� X
			move = true;
		}

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
	switch (key) {
	case 'w':
		Up = false;

		if (!check_move()) {		// �̵����� ������ move �Լ��� false�� ����
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

	case 32:			// �����̽���
		if (!JUMP) {
			JUMP = true;

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

		GLfloat mx = (GLfloat)(x - width) / (GLfloat)width;			// ���콺 �̵��� ��ǥ
		GLfloat my = (GLfloat)(height - y) / (GLfloat)height;


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

