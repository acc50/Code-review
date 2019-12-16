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
	tm = glm::translate(tm, glm::vec3(this->Pos.x, 1.0f, this->Pos.z));

	model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));

	model = tm * sm * model;

	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int colorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(colorLocation, 1.0f, 1.0f, 0.0f);

	/*int lightPosLocation = glGetUniformLocation(ShaderProgram, "LightColor");
	glUniform3f(lightPosLocation, 1.0f,1.0f,0.0f);*/


	glBindBuffer(GL_ARRAY_BUFFER, SVBO);
	int light_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(light_id);
	glVertexAttribPointer(light_id, 3, GL_FLOAT, GL_FALSE, 0, 0);


	//glBindBuffer(GL_ARRAY_BUFFER, SNVBO);

	//int normal_id = glGetAttribLocation(ShaderProgram, "vNormal");  //�븻
	//
	//glEnableVertexAttribArray(normal_id);
	//glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);//3��° ���ڴ� ���������� �󸶳� ��������, �ǵڿ� ���ڴ� ��� �����ұ� x,y,z,r,g,b,�ϱ�  3�������ͽ����ؼ� 6ĭ�������� ����������ġ

	glDrawArrays(GL_TRIANGLES, 0, 2880);

	glDisableVertexAttribArray(light_id);
	//glDisableVertexAttribArray(normal_id);
}

void Pacman::Move(bool Up, bool Down, bool Right, bool Left, glm::vec3 &EYE, glm::vec3 &AT, glm::vec3 &UP)
{
	// ������ EYE �� AT �������� �̵��ؾ���

	GLfloat step = 20;

	glm::vec3 front_dir = AT - EYE;		// EYE ���� AT ���� ���� ���� ����
	front_dir = front_dir / (sqrt(front_dir.x * front_dir.x + front_dir.y * front_dir.y + front_dir.z * front_dir.z));
	glm::vec3 back_dir = glm::vec3(-front_dir.x, -front_dir.y, -front_dir.z);

	glm::vec3 left_dir = glm::vec3(1.0f);		// UP X front_dir  ����
	left_dir.x = UP.y * front_dir.z - UP.z * front_dir.y;
	left_dir.y = UP.z * front_dir.x - UP.x * front_dir.z;
	left_dir.z = UP.x * front_dir.y - UP.y * front_dir.x;

	glm::vec3 right_dir = glm::vec3(-left_dir.x, -left_dir.y, -left_dir.z);

	if (Up) {
		EYE.x += front_dir.x / step;
		EYE.z += front_dir.z / step;
		AT.x += front_dir.x / step;
		AT.z += front_dir.z / step;
	}

	if (Down) {
		EYE.x += back_dir.x / step;
		EYE.z += back_dir.z / step;
		AT.x += back_dir.x / step;
		AT.z += back_dir.z / step;
	}

	if (Left) {
		EYE.x += left_dir.x / step;
		EYE.z += left_dir.z / step;
		AT.x += left_dir.x / step;
		AT.z += left_dir.z / step;
	}

	if (Right) {
		EYE.x += right_dir.x / step;
		EYE.z += right_dir.z / step;
		AT.x += right_dir.x / step;
		AT.z += right_dir.z / step;
	}

	this->Pos = EYE;
}

glm::vec3 Pacman::Get_Pos()
{
	return this->Pos;
}