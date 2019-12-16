#include "Wall.h"



Wall::Wall()
{
}


Wall::~Wall()
{
}

void Wall::Set_Wall(GLfloat x, GLfloat z, GLfloat width, GLfloat depth)
{
	this->Pos.x = x;
	this->Pos.z = z;
	this->Pos.y = 1.0;

	this->width = width / 2;
	this->depth = depth / 2;
}

void Wall::Draw(GLuint ShaderProgram, GLuint VBO, GLuint EBO,Pacman* pacman)
{
	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f); //회전

	tm = glm::translate(tm, glm::vec3(this->Pos.x, 0.0f, this->Pos.z));
	sm = glm::scale(sm, glm::vec3(this->width * 2, 5.0f, this->depth * 2));

	model = tm * rm * sm *model;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int colorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(colorLocation, 1.0f, 0.0f, 1.0f);

	int lightColorLocation = glGetUniformLocation(ShaderProgram, "LightColor");
	glUniform3f(lightColorLocation, 1.0f,1.0f,1.0f);

	int lightPosLocation = glGetUniformLocation(ShaderProgram, "LightPos");
	glUniform3f(lightPosLocation,pacman->Get_Pos().x, pacman->Get_Pos().y, pacman->Get_Pos().z);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	GLuint frag_id = glGetAttribLocation(ShaderProgram, "vNormal");
	glEnableVertexAttribArray(frag_id);
	glVertexAttribPointer(frag_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	
	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

glm::vec3 Wall::Get_Pos()		// 벽의 위치 내보냄
{
	return this->Pos;
}

GLfloat Wall::Get_Width()		// 가로 길이 내보냄
{
	return this->width;
}

GLfloat Wall::Get_Depth()		// 세로 길이 내보냄
{
	return this->depth;
}