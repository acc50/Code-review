#include "Pacman.h"



Pacman::Pacman()
{

}


Pacman::~Pacman()
{

}

void Pacman::Draw(GLuint ShaderProgram, GLuint SVBO, GLuint SNVBO)
{
	float size = 1.0f / 80.0f;

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);

	sm = glm::scale(sm, glm::vec3(size, size, size));
	tm = glm::translate(tm, glm::vec3(Pos.x, 0.35f, Pos.z));


	model = tm * sm * model;

	int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int objColorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(objColorLocation, 1.0, 1.0f, 0.0f);


	glBindBuffer(GL_ARRAY_BUFFER, SVBO);
	int light_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(light_id);
	glVertexAttribPointer(light_id, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, SNVBO);

	//int normal_id = glGetAttribLocation(ShaderProgram, "vNormal");  //노말
	//
	//glEnableVertexAttribArray(normal_id);
	//glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치

	glDrawArrays(GL_TRIANGLES, 0, 2880);

	glDisableVertexAttribArray(light_id);
	//glDisableVertexAttribArray(normal_id);
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
	return this->rsize;
}

void Pacman::Set_Speed(GLfloat speed)
{
	this->sensitive = speed;
}