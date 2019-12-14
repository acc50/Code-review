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

void draw_wall(GLuint ShaderProgram, GLuint VBO, GLuint EBO, float x, float z, float width, float width2)
{
	glm::mat4 model = glm::mat4(1.0f); //����
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f); //ȸ��

	tm = glm::translate(tm, glm::vec3(x, 0.0f, z));
	sm = glm::scale(sm, glm::vec3(width, 5.0f, width2));

	model = tm * rm * sm *model;
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

void draw_map(GLuint ShaderProgram, GLuint VBO, GLuint EBO)
{

	// �������� ��������Ƿ� �����ϸ� �������� 0.1��  �����ϳ��� ������ 0.1
	float defalut_width = 1.0f;
	float defalut_width2 = 0.1f;
	draw_floor(ShaderProgram, VBO, EBO);

	// ��ǥ�����
	for (float i = -5.0f; i <= 5.0f; i += 1.0f) {
		for (float j = -5.0f; j <= 5.0f; j += 1.0f)
			draw_wall(ShaderProgram, VBO, EBO, j, i, defalut_width2, defalut_width2);
	}

	//��ǥ�ٶ� ������ �ι�ø��� ������ x��ǥ�� 2��ø����� �߰����� ��ߵ�
	//ex   ��ǥ 0~2�ΰ��� ������ ��������� �ʱⰪ�� 1���ϰ� ���γʺ� 2�� �ش�.


	//1�� ��
	draw_wall(ShaderProgram, VBO, EBO, -4.0f, -3.5f, defalut_width2, 1.0f);

	////2���� ��ť���
	draw_wall(ShaderProgram, VBO, EBO, -2.0f, -4.0f, 2.0f, defalut_width2); //����
	draw_wall(ShaderProgram, VBO, EBO, -2.0f, -3.5f, defalut_width2, defalut_width); //����

	//3����
	draw_wall(ShaderProgram, VBO, EBO, 2.0f, -4.0f, 2.0f, defalut_width2); //����
	draw_wall(ShaderProgram, VBO, EBO, 2.0f, -3.5f, defalut_width2, defalut_width); //����

	//4����
	draw_wall(ShaderProgram, VBO, EBO, 4.0f, -3.5f, defalut_width2, defalut_width);

	//5����
	draw_wall(ShaderProgram, VBO, EBO, -4.5f, -2.0f, defalut_width, defalut_width2);


	//6���� ���ڰ����
	draw_wall(ShaderProgram, VBO, EBO, -3.0f, -1.0f, 2.0f, defalut_width2); //����
	draw_wall(ShaderProgram, VBO, EBO, -3.0f, -1.5f, defalut_width2, 3.0f); //����

	//7����
	draw_wall(ShaderProgram, VBO, EBO, -1.5f, -2.0f, defalut_width, defalut_width2);

	//8����
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, -3.0f, 2.0f, defalut_width2); //����
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, -2.5f, defalut_width2, defalut_width); //����

	//9����
	draw_wall(ShaderProgram, VBO, EBO, 1.5f, -2.0f, defalut_width, defalut_width2);

	//10����
	draw_wall(ShaderProgram, VBO, EBO, 3.0f, -1.0f, 2.0f, defalut_width2); //����
	draw_wall(ShaderProgram, VBO, EBO, 3.0f, -1.5f, defalut_width2, 3.0f); //����

	//11����
	draw_wall(ShaderProgram, VBO, EBO, 4.5f, -2.0f, defalut_width, defalut_width2);

	//12��
	draw_wall(ShaderProgram, VBO, EBO, -4.5f, 0.0f, defalut_width, defalut_width2);

	//13��
	draw_wall(ShaderProgram, VBO, EBO, -1.0f, -0.5f, defalut_width2, defalut_width); //���ʼ���
	draw_wall(ShaderProgram, VBO, EBO, 1.0f, -0.5f, defalut_width2, defalut_width); //�����ʼ���
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, -1.0f, 2.0f, defalut_width2); //���� ����
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, 0.0f, 2.0f, defalut_width2); //���� ����

	//14��
	draw_wall(ShaderProgram, VBO, EBO, 4.5f, 0.0f, defalut_width, defalut_width2);

	//15�� ����� ��
	draw_wall(ShaderProgram, VBO, EBO, -3.5f, 1.0f, defalut_width, defalut_width2);//����
	draw_wall(ShaderProgram, VBO, EBO, -3.0f, 1.5f, defalut_width2, defalut_width);//����

	//16��
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, 1.0f, 2.0f, defalut_width2);//����
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, 1.5f, defalut_width2, defalut_width);//����

	//17��
	draw_wall(ShaderProgram, VBO, EBO, 3.5f, 1.0f, defalut_width, defalut_width2);//����
	draw_wall(ShaderProgram, VBO, EBO, 3.0f, 1.5f, defalut_width2, defalut_width);//����

	//18��
	draw_wall(ShaderProgram, VBO, EBO, -1.5f, 2.0f, defalut_width, defalut_width2);

	//19��
	draw_wall(ShaderProgram, VBO, EBO, 1.5f, 2.0f, defalut_width, defalut_width2);

	//20��
	draw_wall(ShaderProgram, VBO, EBO, -4.5f, 3.0f, defalut_width, defalut_width2);

	//21��
	draw_wall(ShaderProgram, VBO, EBO, -3.0f, 4.0f, 2.0f, defalut_width2);//����
	draw_wall(ShaderProgram, VBO, EBO, -3.0f,3.5f, defalut_width2, defalut_width);//����

	//22��
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, 3.0f, 2.0f, defalut_width2);//����
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, 3.5f, defalut_width2, defalut_width);//����

	//23
	draw_wall(ShaderProgram, VBO, EBO, 3.0f, 4.0f, 2.0f, defalut_width2);//����
	draw_wall(ShaderProgram, VBO, EBO, 3.0f, 3.5f, defalut_width2, defalut_width);//����

	//24
	draw_wall(ShaderProgram, VBO, EBO, 4.5f, 3.0f, defalut_width, defalut_width2);

	//�׵θ�
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, -5.0f, 10.0f, defalut_width2);
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, 5.0f, 10.0f, defalut_width2);
	draw_wall(ShaderProgram, VBO, EBO, -5.0f, 0.0f, defalut_width2, 10.0f);
	draw_wall(ShaderProgram, VBO, EBO, 5.0f, 0.0f, defalut_width2, 10.0f);
	
}