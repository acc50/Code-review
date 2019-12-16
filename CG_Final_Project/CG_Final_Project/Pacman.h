#pragma once
#include "global.h"

class Pacman
{
private:

	glm::vec3 start_Pos = glm::vec3(0.0f, 1.0f, 0.5f);
	glm::vec3 start_AT = glm::vec3(1.0f, 1.0f, 0.5f);
	glm::vec3 Pos = glm::vec3(0.0f, 1.0f, 0.5f);	// 팩맨 위치

	bool is_trapped = false;	// 함정에 걸렸는지 확인하는 변수
	GLfloat sensitive = 30.0f;		//	이 값이 크면 이동속도가 느림
	GLfloat rsize = 0.2f;		// 팩맨의 반지름 크기
	
	bool is_lived = true;
	int life = 2;
	GLfloat MAX_COUNT = 2.0f;
	GLfloat revive_count = 0.0f;

public:
	Pacman();
	~Pacman();

	void Draw(GLuint ShaderProgram, GLuint SVBO, GLuint SNVBO);
	void Move(bool Up, bool Down, bool Right, bool Left, glm::vec3 &EYE, glm::vec3 &AT, glm::vec3 &UP);

	void Set_Pos_x(GLfloat x);
	void Set_Pos_z(GLfloat z);
	void Set_Speed(GLfloat speed);
	void Decrease_Life();
	void Revive(glm::vec3 &EYE, glm::vec3 &AT, GLfloat &yaw, GLfloat &pitch);
	void Die();

	glm::vec3 Get_Pos();
	GLfloat Get_Size();
	GLfloat Get_Speed();
	bool Get_is_lived();

	int slowdown_count = -1;
};

