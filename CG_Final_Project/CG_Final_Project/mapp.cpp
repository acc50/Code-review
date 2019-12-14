#include "map.h"


void draw_floor(GLuint ShaderProgram, GLuint VBO, GLuint EBO)
{
	glm::mat4 model = glm::mat4(1.0f); //����
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f); //ȸ��
	tm = glm::translate(tm, glm::vec3(0.0f, 0.0f, 0.0f));
	sm = glm::scale(sm, glm::vec3(10.0f, 0.25f, 10.0f));
	model = tm * rm * sm *model;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int colorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(colorLocation, 0.0f, 0.0f, 1.0f);

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