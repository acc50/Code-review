#include "Pacman.h"



Pacman::Pacman()
{
}


Pacman::~Pacman()
{
}

void Pacman::Draw(GLuint ShaderProgram, GLuint VBO, GLuint EBO)
{
	glm::mat4 model = glm::mat4(1.0f); //최종

	glm::mat4 tm = glm::mat4(1.0f);	// 이동
	glm::mat4 rm = glm::mat4(1.0f); // 회전

	tm = glm::translate(tm, glm::vec3(this->Pos.x, 1.0f, this->Pos.z));


	model = tm * rm * model;

	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int colorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(colorLocation, 1.0f, 0.0f, 1.0f);

	/*int lightPosLocation = glGetUniformLocation(ShaderProgram, "LightColor");
	glUniform3f(lightPosLocation, 1.0f,1.0f,0.0f);*/


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	GLuint frag_id = glGetAttribLocation(ShaderProgram, "vColor");
	glEnableVertexAttribArray(frag_id);
	glVertexAttribPointer(frag_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Pacman::Move(bool Up, bool Down, bool Right, bool Left, glm::vec3 EYE, glm::vec3 AT)
{
	// 임시로 x,z 위치를 이동

	// 원래는 EYE 와 AT 기준으로 이동해야함

	if (Up) {
		this->Pos.z -= 0.1f;
	}

	if (Down) {
		this->Pos.z += 0.1f;
	}

	if (Left) {
		this->Pos.x -= 0.1f;
	}

	if (Right) {
		this->Pos.x += 0.1f;
	}
}

glm::vec3 Pacman::Get_Pos()
{
	return this->Pos;
}