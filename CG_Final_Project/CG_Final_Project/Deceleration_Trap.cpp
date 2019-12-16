#include "Deceleration_Trap.h"



Deceleration_Trap::Deceleration_Trap()
{
}


Deceleration_Trap::~Deceleration_Trap()
{
}

void Deceleration_Trap::Set_Pos(GLfloat x, GLfloat z)
{
	Pos.x = x;
	Pos.z = z;
}

glm::vec3 Deceleration_Trap::Get_Pos()
{
	return this->Pos;
}

GLfloat Deceleration_Trap::Get_Size()
{
	return this->size;
}

void Deceleration_Trap::Draw(GLuint ShaderProgram, GLuint VBO, GLuint EBO, Pacman* pacman)
{
	glm::mat4 model = glm::mat4(1.0f); //����
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f); //ȸ��

	tm = glm::translate(tm, glm::vec3(Pos.x, 0.0f, Pos.z));
	sm = glm::scale(sm, glm::vec3(size, ysize, size));

	model = tm * rm * sm *model;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int colorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(colorLocation, 1.0f, 0.0f, 1.0f);

	int lightColorLocation = glGetUniformLocation(ShaderProgram, "LightColor");
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);

	int lightPosLocation = glGetUniformLocation(ShaderProgram, "LightPos");
	glUniform3f(lightPosLocation, pacman->Get_Pos().x, pacman->Get_Pos().y, pacman->Get_Pos().z);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	GLuint frag_id = glGetAttribLocation(ShaderProgram, "vColor");
	glEnableVertexAttribArray(frag_id);
	glVertexAttribPointer(frag_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(pos_id);
	glDisableVertexAttribArray(frag_id);
}

void Deceleration_Trap::Crash_to_Player(glm::vec3 Pos, GLfloat size)
{

}
