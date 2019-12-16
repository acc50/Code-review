#pragma once
#include "global.h"

class Wall
{
private:
	glm::vec3 Pos = glm::vec3(0.0f);		// ���� x,z ��ġ�� ��� ����
	GLfloat width;		// ���� ����
	GLfloat depth;		// ���� ����

public:
	Wall();
	~Wall();

	void Set_Wall(GLfloat x, GLfloat z, GLfloat width, GLfloat depth);
	void Draw(GLuint ShaderProgram, GLuint VBO, GLuint EBO);

	glm::vec3 Get_Pos();
	GLfloat Get_Width();		// ���� ���� ������
	GLfloat Get_Depth();		// ���� ���� ������

};

