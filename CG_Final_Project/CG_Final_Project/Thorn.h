#pragma once
#include "global.h"

class Thorn
{
private:
	glm::vec3 Pos = glm::vec3(1.0f);
	GLfloat height = 0.0f;					// ������ ����
	GLfloat MAX_HEIGHT = 0.6f;
	GLfloat size = 1.0f / 6.0f;
	
	bool is_detect_player = false;		// �����߳� Ȯ���ϴ� ����
	bool is_activated = false;			// �ߵ��߳� Ȯ���ϴ� ����, -> �ߵ��ߴٸ� ��Ÿ���� ����
	GLfloat duration = 2.5f;
	GLfloat cool_time = 3.0f;
	GLfloat time = 0.0f;
	GLfloat detect_range = 2.5f;

public:
	Thorn();
	~Thorn();

	void Set_Pos(GLfloat x, GLfloat z);
	void Draw(GLuint ShaderProgram, GLuint ConVBO, GLuint ConEBO);
	void Render(GLuint ShaderProgram, GLuint ConVBO, GLuint ConEBO, GLfloat x, GLfloat z);
	void Update(glm::vec3 Pos);
	void Detect_to_Player(glm::vec3 Pos);		// �÷��̾ ������
};

