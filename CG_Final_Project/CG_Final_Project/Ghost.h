#pragma once
#include "global.h"

class Ghost
{
private:
	glm::vec3 Pos = glm::vec3(0.0f, 0.7f, 0.5f);		// 유령 위치
	glm::vec3 Color = glm::vec3(0.0f, 0.0f, 0.0f);

	GLfloat rsize = 0.2f;		// 유령의 반지름 크기
	GLfloat speed = 50.0f;

	bool is_move = false;
	GLfloat time = 0.0f;
	GLfloat WAITING_TIME = 2.0f;

public:
	Ghost();
	~Ghost();

	void Draw(GLuint ShaderProgram, GLuint SVBO, GLuint SNVBO);
	void Update();
	void Move();

	void Init(GLfloat x, GLfloat z, GLfloat r, GLfloat g, GLfloat b);
	void Set_Pos_x(GLfloat x);
	void Set_Pos_y();
	void Set_Pos_z(GLfloat z);

	glm::vec3 Get_Pos();
	GLfloat Get_Size();
};

