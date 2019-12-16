#pragma once
#include "global.h"

class Hole
{
private:
	glm::vec3 Pos = glm::vec3(1.0f);
	glm::vec3 Color = glm::vec3(0.0f, 0.0f, 1.0f);

	bool is_detect_player = false;		// 감지했나 확인하는 변수
	bool is_activate = false;
	GLfloat detect_range = 2.5f;
	GLfloat size = 0.7f;
	GLfloat ysize = 0.3f;

public:
	Hole();
	~Hole();

	void Set_Pos(GLfloat x, GLfloat z);
	glm::vec3 Get_Pos();
	GLfloat Get_Size();
	bool Get_State();


	void Draw(GLuint ShaderProgram, GLuint VBO, GLuint EBO, Pacman* pacman);
	void Update(glm::vec3 Pos);
	void Detect_to_Player(glm::vec3 Pos);		// 플레이어를 감지함

};

