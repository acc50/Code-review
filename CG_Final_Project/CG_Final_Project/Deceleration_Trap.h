#pragma once
#include "global.h"

class Deceleration_Trap
{
private:
	glm::vec3 Pos = glm::vec3(1.0f);
	glm::vec3 Color = glm::vec3(0.0f, 1.0f, 0.0f);

	GLfloat size = 0.7f;
	GLfloat ysize = 0.3f;

public:
	Deceleration_Trap();
	~Deceleration_Trap();

	void Set_Pos(GLfloat x, GLfloat z);
	glm::vec3 Get_Pos();
	GLfloat Get_Size();

	void Draw(GLuint ShaderProgram, GLuint VBO, GLuint EBO);
	void Crash_to_Player(glm::vec3 Pos, GLfloat size);
};

