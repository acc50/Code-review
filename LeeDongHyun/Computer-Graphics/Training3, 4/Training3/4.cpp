#include <GL/glew.h>
#include <GL/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <random>
#include <time.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "file2buf.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")

using namespace std;

random_device rd;
default_random_engine dre(rd());
uniform_real_distribution<float> random_Pos(-0.2f, 0.2f);
uniform_real_distribution<float> random_color(0.0f, 1.0f);

float quadrant1 = random_Pos(dre), quadrant2 = random_Pos(dre),				// 1,2,3,4 사분면 위의 랜덤한 점을 찍기위해 만든 변수
quadrant3 = random_Pos(dre), quadrant4 = random_Pos(dre);

int Window_Width = 1200, Window_Height = 1000;
int n = 0, i = 0;									// 쉐이더 프로그램 여러개를 만들기 위한 변수, 몇번째 삼각형인지를 알기 위한 변수
GLfloat r[4], g[4], b[4];
int Draw_type = 0;
GLfloat tempx[4], tempy[4];	// 삼각형의 이동 시 현재 좌표값을 저장하는 변수
int ratio = 0;				// 직선이동 비율
int dir[4] = { 0,1,2,3 };	// 삼각형의 이동방향  0 - 아래 1 - 오른쪽 2 - 위 3 - 왼쪽
bool timerswitch = false;	// 삼각형의 이동 제어 변수

GLfloat TriShape[4][3][3] = {											// 삼각형 쉐이더 4개를 전역변수로 선언	2,3,4,1 사분면 순서대로 삼각형의 순서
	{{-0.5f + quadrant2, 0.5f + quadrant2 + 0.15f, 0.0f},
	{-0.5f + quadrant2 - 0.15f , 0.5f + quadrant2 - 0.15f, 0.0f},
	{-0.5f + quadrant2 + 0.15f, 0.5f + quadrant2 - 0.15f, 0.0f}},

	{{-0.5f + quadrant3, -0.5f + quadrant3 + 0.15f, 0.0f},
	{-0.5f + quadrant3 - 0.15f, -0.5f + quadrant3 - 0.15f, 0.0f},
	{-0.5f + quadrant3 + 0.15f, -0.5f + quadrant3 - 0.15f, 0.0f}},

	{{0.5f + quadrant4, -0.5f + quadrant4 + 0.15f, 0.0f},
	{0.5f + quadrant4 - 0.15f, -0.5f + quadrant4 - 0.15f, 0.0f},
	{0.5f + quadrant4 + 0.15f, -0.5f + quadrant4 - 0.15f, 0.0f}},

	{{0.5f + quadrant1, 0.5f + quadrant1 + 0.15f, 0.0f},
	{0.5f + quadrant1 - 0.15f, 0.5f + quadrant1 - 0.15f, 0.0f},
	{0.5f + quadrant1 + 0.15f, 0.5f + quadrant1 - 0.15f, 0.0f}}
};

GLuint compile_shader()				// 쉐이더 함수
{
	GLfloat colors[4][3][3] = {		// 색상값을 초기화
		{{r[0], g[0], b[0]},
		{r[0], g[0], b[0]},
		{r[0], g[0], b[0]}},

		{{r[1], g[1], b[1]},
		{r[1], g[1], b[1]},
		{r[1], g[1], b[1]}},

		{{r[2], g[2], b[2]},
		{r[2], g[2], b[2]},
		{r[2], g[2], b[2]}},

		{{r[3], g[3], b[3]},
		{r[3], g[3], b[3]},
		{r[3], g[3], b[3]}},
	};

	GLuint vao, vbo[2];
	GLuint ShaderProgramID;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, vbo);			// vao, vbo 바인드

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), TriShape[n], GL_STATIC_DRAW);		// 점 9개를 n번째 삼각형의 좌표로 함
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors[n], GL_STATIC_DRAW);		// 값 9개를 n번째 삼각형의 색상으로 함
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);




	const GLchar* vertexsource = filetobuf("Vertex.glvs");
	const GLchar* fragmentssource = filetobuf("frag.glfs");
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexsource, NULL);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR:vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return false;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentssource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR:fragmentShader 컴파일 실패\n" << errorLog << std::endl;
		return false;
	}
	ShaderProgramID = glCreateProgram();

	glAttachShader(ShaderProgramID, vertexShader);
	glAttachShader(ShaderProgramID, fragmentShader);

	glBindAttribLocation(ShaderProgramID, 0, "vPos");		// 링크 전 쉐이더 프로그램에 붙여야함 
	glBindAttribLocation(ShaderProgramID, 1, "vColor");

	glLinkProgram(ShaderProgramID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);
		std::cerr << "EROOR:shader program연결실패\n" << errorLog << std::endl;
		return false;
	}
	glUseProgram(ShaderProgramID);

	glBindVertexArray(vao);		// vao 바인드

	return ShaderProgramID;

}

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Move_Line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, int num);
void Tri_rotation(GLfloat x1, GLfloat y1, int number);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Timer(int value);

int main(int argc, char** argv) // 윈도우 출력하고 콜백함수 설정 
{
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정
	glutCreateWindow("Training3"); // 윈도우 생성

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLE" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized" << std::endl;


	for (int k = 0; k < 4; k++) {		// 메인에서 삼각형의 색상들을 정하고 루프를 돌림 
		r[k] = random_color(dre);
		g[k] = random_color(dre);
		b[k] = random_color(dre);
	}

	glutDisplayFunc(drawScene);						 	 // 출력 함수의 지정
	glutReshapeFunc(Reshape);							 // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();										 // 이벤트 처리 시작 
}

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기


	// 그리기 부분 구현

	GLuint ShaderProgramID[4];

	for (n = 0; n < 4; n++) {
		ShaderProgramID[n] = compile_shader();		// 쉐이더 프로그램을 4개 만듬
		glUseProgram(ShaderProgramID[n]);			// 4개를 각각 사용함			즉 한개의 삼각형에 한개의 프로그램이 사용됨

		if (Draw_type == 0)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	//--- 그리기 관련 부분이 여기에 포함된다

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) // 콜백 함수: 다시 그리기
{
	glViewport(0, 0, w, h);
}

void Mouse(int button, int state, int x, int y)
{
	GLfloat x1, y1;	float x_size = Window_Width / 2, y_size = Window_Height / 2;

	if (x < x_size) {
		x1 = -(GLfloat)((GLfloat)(x_size - x) / (GLfloat)x_size);
	}
	else {
		x1 = (GLfloat)((GLfloat)(x - x_size) / (GLfloat)x_size);
	}

	if (y < y_size) {
		y1 = (GLfloat)((GLfloat)(y_size - y) / (GLfloat)y_size);
	}
	else {
		y1 = -(GLfloat)((GLfloat)(y - y_size) / (GLfloat)y_size);
	}

	//	----- 위의 작업은 윈도우상의 마우스좌표를 뷰포트상의 좌표로 바꾸는 작업

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {		// 현재 삼각형의 좌표를 바꿈
		TriShape[i][0][0] = x1;
		TriShape[i][1][0] = x1 - 0.15f;
		TriShape[i][2][0] = x1 + 0.15f;
		TriShape[i][0][1] = y1 + 0.15f;
		TriShape[i][1][1] = y1 - 0.15f;
		TriShape[i][2][1] = y1 - 0.15f;
												// 바꾼곳이 어느 사분면인지에 따라 이동할 방향 설정
		if (x >= x_size && y < y_size) {		// 1사분면
			dir[i] = 3;
		}
		else if(x < x_size && y < y_size){		// 2사분면
			dir[i] = 0;
		}
		else if (x < x_size && y >= y_size) {		// 3사분면
			dir[i] = 1;
		}
		else if (x >= x_size && y >= y_size) {		// 4사분면
			dir[i] = 2;
		}

		i = (i + 1) % 4;			// 삼각형은 최대 4개고 5번째클릭시 처음 삼각형으로 돌아와야함
	}

	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'F':
	case 'f':
		Draw_type = 1 - Draw_type;
		break;

	case 'c':
	case 'C':
		for (int k = 0; k < 4; k++) {
			r[k] = random_color(dre);
			g[k] = random_color(dre);
			b[k] = random_color(dre);
		}
		break;

	case 'm':
	case 'M':
		if (!timerswitch) {					// 회전 시 현재 좌표값을 절대값으로 저장후 그 값만큼 회전 범위가 결정될 것
			for (int k = 0; k < 4; k++) {
				tempx[k] = fabs(TriShape[k][0][0]);
				tempy[k] = fabs(TriShape[k][0][1] - 0.15f);			// 삼각형의 중심을 저장할것이므로 top 좌표에서 y값에 -0.15f 를 함
				//cout << tempx[k] << " " << tempy[k] << endl;
			}
			timerswitch = true;
			glutTimerFunc(25, Timer, 1);
		}
		else {
			ratio = 0;				// 회전 종료 시 이동 비율은 0으로 되돌림
			timerswitch = false;
		}

		break;

	case 'q':
	case 'Q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

void Timer(int value)
{
	if (timerswitch) {
		
		Tri_rotation(tempx[0], tempy[0], 1);		// 삼각형의 중심을 넘김
		Tri_rotation(tempx[1], tempy[1], 2);
		Tri_rotation(tempx[2], tempy[2], 3);
		Tri_rotation(tempx[3], tempy[3], 4);
		

		ratio = ratio + 1;
		if (ratio > 100) {			// 직선이동이 끝나면 방향을 바꿈
			ratio = 0;
			dir[0] = (dir[0] + 1) % 4;
			dir[1] = (dir[1] + 1) % 4;
			dir[2] = (dir[2] + 1) % 4;
			dir[3] = (dir[3] + 1) % 4;
		}

		glutPostRedisplay();
		glutTimerFunc(25, Timer, 1);
	}
}

void Tri_rotation(GLfloat x, GLfloat y, int num)			// 방향에 따른 직선이동 p1,p2 값을 넘겨줌
{
	if (dir[num - 1] == 0) {						// 아래
		Move_Line(-x, y, -x, -y, num);
	}

	else if (dir[num - 1] == 1) {				// 오른쪽
		Move_Line(-x, -y, x, -y, num);
	}

	else if (dir[num - 1] == 2) {				// 위
		Move_Line(x, -y, x, y, num);
	}

	else if (dir[num - 1] == 3) {				// 왼쪽
		Move_Line(x, y, -x, y, num);
	}
}

void Move_Line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, int num)			// 2dgp에서 한 직선이동 방식
{
	GLfloat t = (GLfloat)ratio / (GLfloat)100;
	TriShape[num - 1][0][0] = (1 - t)*x1 + t * x2;
	TriShape[num - 1][1][0] = (1 - t)*(x1 - 0.15f) + t * (x2 - 0.15f);
	TriShape[num - 1][2][0] = (1 - t)*(x1 + 0.15f) + t * (x2 + 0.15f);

	TriShape[num - 1][0][1] = (1 - t)*(y1 + 0.15f) + t * (y2 + 0.15f);
	TriShape[num - 1][1][1] = (1 - t)*(y1 - 0.15f) + t * (y2 - 0.15f);
	TriShape[num - 1][2][1] = (1 - t)*(y1 - 0.15f) + t * (y2 - 0.15f);
		
}