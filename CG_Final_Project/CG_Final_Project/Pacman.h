#pragma once
#include "global.h"

class Pacman
{
private:

	glm::vec3 Pos = glm::vec3(0.0f, 1.0f, 0.5f);	// ÆÑ¸Ç À§Ä¡

public:
	Pacman();
	~Pacman();

	void Draw(GLuint ShaderProgram, GLuint VBO, GLuint EBO);
	void Move(bool Up, bool Down, bool Right, bool Left, glm::vec3 &EYE, glm::vec3 &AT, glm::vec3 &UP);

	glm::vec3 Get_Pos();
};

