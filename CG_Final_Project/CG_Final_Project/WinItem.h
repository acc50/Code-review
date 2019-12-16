#pragma once
#include "global.h"
class WinItem
{
private:
	glm::vec3 Pos = glm::vec3(1.0f);
	GLfloat rsize = 0.2f;

public:
	WinItem();
	~WinItem();

	void Draw(GLuint ShaderProgram, GLuint SVBO, GLuint SNVBO);

	void Set_Pos(GLfloat x, GLfloat z);
	glm::vec3 Get_Pos();
	GLfloat Get_Size();

	bool is_activate = true;			// 먹을 수 있는 아이템인가
};

