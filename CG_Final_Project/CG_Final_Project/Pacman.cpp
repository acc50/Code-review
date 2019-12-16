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

	model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));

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

void Pacman::Move(bool Up, bool Down, bool Right, bool Left, glm::vec3 &EYE, glm::vec3 &AT, glm::vec3 &UP)
{
	// 원래는 EYE 와 AT 기준으로 이동해야함

	glm::vec3 front_dir = AT - EYE;		// EYE 기준 AT 으로 가는 방향 벡터
	front_dir = front_dir / (sqrt(front_dir.x * front_dir.x + front_dir.y * front_dir.y + front_dir.z * front_dir.z));
	glm::vec3 back_dir = glm::vec3(-front_dir.x, -front_dir.y, -front_dir.z);

	glm::vec3 left_dir = glm::vec3(1.0f);		// UP X front_dir  외적
	left_dir.x = UP.y * front_dir.z - UP.z * front_dir.y;
	left_dir.y = UP.z * front_dir.x - UP.x * front_dir.z;
	left_dir.z = UP.x * front_dir.y - UP.y * front_dir.x;

	glm::vec3 right_dir = glm::vec3(-left_dir.x, -left_dir.y, -left_dir.z);

	if (Up) {
		EYE.x += front_dir.x / sensitive;
		EYE.z += front_dir.z / sensitive;
		AT.x += front_dir.x / sensitive;
		AT.z += front_dir.z / sensitive;
	}

	if (Down) {
		EYE.x += back_dir.x / sensitive;
		EYE.z += back_dir.z / sensitive;
		AT.x += back_dir.x / sensitive;
		AT.z += back_dir.z / sensitive;
	}

	if (Left) {
		EYE.x += left_dir.x / sensitive;
		EYE.z += left_dir.z / sensitive;
		AT.x += left_dir.x / sensitive;
		AT.z += left_dir.z / sensitive;
	}

	if (Right) {
		EYE.x += right_dir.x / sensitive;
		EYE.z += right_dir.z / sensitive;
		AT.x += right_dir.x / sensitive;
		AT.z += right_dir.z / sensitive;
	}

	this->Pos = EYE;		// 카메라의 위치에 Pos를 항상 이동시킴
}

glm::vec3 Pacman::Get_Pos()
{
	return this->Pos;
}

GLfloat Pacman::Get_Size()
{
	return this->size;
}

void Pacman::Set_Speed(GLfloat speed)
{
	this->sensitive = speed;
}