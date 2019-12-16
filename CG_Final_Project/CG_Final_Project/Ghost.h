#pragma once
#include "global.h"
struct Point {
	float x, z;
};

class Ghost
{
private:
	glm::vec3 Pos = glm::vec3(0.0f, 0.7f, 0.5f);		// 유령 위치
	glm::vec3 Color = glm::vec3(0.0f, 0.0f, 0.0f);

	GLfloat rsize = 0.2f;		// 유령의 반지름 크기
	GLfloat speed = 20.0f;

	bool is_move = false;
	GLfloat time = 0.0f;
	GLfloat WAITING_TIME = 2.0f;
	int cur_point = 0;				// 패트롤 현재 위치
	int patrol_type = 0;

	Point patrolPoint[36] = {
	{-4.5,-4.5},{-4.5,-2.5},{-3.5,-2.5},{-3.5,-1.5},{-4.5,-1.5},{-4.5,-0.5},{-3.5,-0.5},
	{-3.5, 0.5},{-4.5, 0.5},{-4.5, 2.5},{-3.5, 2.5},{-3.5, 3.5},{-4.5, 3.5},{-4.5, 4.5},
	{-2.5, 4.5},{-0.5, 4.5},{0.5,  4.5},{ 2.5, 4.5},{4.5,  4.5},{4.5,  3.5},{3.5,  3.5},
	{3.5,  2.5},{4.5, 2.5},{4.5,  0.5},{3.5,  0.5},{3.5, -0.5},{4.5, -0.5},{4.5, -1.5},
	{3.5, -1.5},{3.5, -2.5},{4.5, -2.5},{4.5, -4.5},{2.5, -4.5},{0.5,-4.5},{-0.5,-4.5},
	{-2.5, -4.5}
	};

	Point startingPoint[8] = {
	{-4.5,-4.5},{-4.5,-2.5},{-3.5,-2.5},{-3.5,-1.5},{-4.5,-1.5},{-4.5,-0.5},{-3.5,-0.5},
	{-3.5, 0.5}
	}

	Point patrolPoint2[24] = {
	{-0.5,-3.5},{-1.5,-3.5},{-1.5,-2.5},{-2.5,-2.5},{-2.5,-1.5},{-1.5,-1.5},{-1.5,-0.5},
	{-2.5,-0.5},{-2.5, 0.5},{-2.5, 1.5},{-2.5, 2.5},{-0.5, 2.5},{0.5, 2.5},{2.5, 2.5},
	{2.5, 1.5},{2.5, 0.5},{2.5, -0.5},{1.5, -0.5},{1.5, -1.5},{2.5, -1.5},{2.5, -2.5},
	{1.5, -2.5},{1.5, -3.5},{0.5, -3.5}
	};

public:
	Ghost();
	~Ghost();

	void Draw(GLuint ShaderProgram, GLuint SVBO, GLuint SNVBO);
	void Update();
	void Move();
	void first_Patrol();
	void second_Patrol();

	void Init(GLfloat x, GLfloat z, GLfloat r, GLfloat g, GLfloat b, int type);
	void Set_Pos_x(GLfloat x);
	void Set_Pos_y();
	void Set_Pos_z(GLfloat z);

	glm::vec3 Get_Pos();
	GLfloat Get_Size();
};