#pragma once
#include "global.h"

class Wall
{
private:
	glm::vec3 Pos = glm::vec3(0.0f);		// 벽의 x,z 위치를 담는 변수
	GLfloat width;		// 가로 길이
	GLfloat depth;		// 세로 길이

public:
	Wall();
	~Wall();

	void Set_Wall(GLfloat x, GLfloat z, GLfloat width, GLfloat depth);
	void Draw(GLuint ShaderProgram, GLuint VBO, GLuint EBO);

	glm::vec3 Get_Pos();
	GLfloat Get_Width();		// 가로 길이 내보냄
	GLfloat Get_Depth();		// 세로 길이 내보냄

};

