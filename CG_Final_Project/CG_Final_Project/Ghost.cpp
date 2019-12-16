#include "Ghost.h"



Ghost::Ghost()
{
}


Ghost::~Ghost()
{

}

void Ghost::Draw(GLuint ShaderProgram, GLuint SVBO, GLuint SNVBO)
{
	float size = 1.0f / 80.0f;

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);

	sm = glm::scale(sm, glm::vec3(size, size, size));
	tm = glm::translate(tm, glm::vec3(Pos.x, Pos.y, Pos.z));


	model = tm * sm * model;

	int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int objColorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(objColorLocation, Color.r, Color.g, Color.b);


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

void Ghost::Update()
{


	if (is_move) {
		Move();
	}

	else {
		time += 0.1f;

		if (time > WAITING_TIME) {
			is_move = true;
		}
	}
}

void Ghost::Move()
{

}

void Ghost::Init(GLfloat x, GLfloat z, GLfloat r, GLfloat g, GLfloat b)
{
	this->Pos.x = x;
	this->Pos.z = z;
	Color.r = r;
	Color.g = g;
	Color.b = b;
}

void Ghost::Set_Pos_x(GLfloat x)
{
	this->Pos.x = x;
}

void Ghost::Set_Pos_y()
{

}

void Ghost::Set_Pos_z(GLfloat z)
{
	this->Pos.z = z;
}

glm::vec3 Ghost::Get_Pos()
{
	return this->Pos;
}

GLfloat Ghost::Get_Size()
{
	return this->rsize;
}