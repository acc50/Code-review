#pragma once
#include "global.h"

class Pacman
{
private:

	glm::vec3 start_Pos = glm::vec3(0.0f, 1.0f, 0.5f);
	glm::vec3 Pos = glm::vec3(0.0f, 1.0f, 0.5f);	// �Ѹ� ��ġ

	bool is_trapped = false;	// ������ �ɷȴ��� Ȯ���ϴ� ����
	GLfloat sensitive = 30.0f;		//	�� ���� ũ�� �̵��ӵ��� ����
	GLfloat rsize = 0.2f;		// �Ѹ��� ������ ũ��


public:
	Pacman();
	~Pacman();

	void Draw(GLuint ShaderProgram, GLuint SVBO, GLuint SNVBO);
	void Move(bool Up, bool Down, bool Right, bool Left, glm::vec3 &EYE, glm::vec3 &AT, glm::vec3 &UP);

	void Set_Pos_x(GLfloat x);
	void Set_Pos_z(GLfloat z);
	void Set_Speed(GLfloat speed);


	glm::vec3 Get_Pos();
	GLfloat Get_Size();
	GLfloat Get_Speed();

	int slowdown_count = -1;
};

