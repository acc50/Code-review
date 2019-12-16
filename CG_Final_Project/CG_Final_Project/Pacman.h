#pragma once
#include "global.h"

class Pacman
{
private:

	glm::vec3 Pos = glm::vec3(0.0f, 1.0f, 0.5f);	// 팩맨 위치

	bool is_trapped = false;	// 함정에 걸렸는지 확인하는 변수
	GLfloat sensitive = 30.0f;		//	이 값이 크면 이동속도가 느림
	GLfloat rsize = 0.5f;		// 팩맨의 반지름 크기

public:
	Pacman();
	~Pacman();

	void Draw(GLuint ShaderProgram, GLuint SVBO, GLuint SNVBO);
	void Move(bool Up, bool Down, bool Right, bool Left, glm::vec3 &EYE, glm::vec3 &AT, glm::vec3 &UP);

	glm::vec3 Get_Pos();
	GLfloat Get_Size();
	void Set_Speed(GLfloat speed);
};

