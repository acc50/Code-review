#include "WinItem.h"



WinItem::WinItem()
{
}


WinItem::~WinItem()
{
}

void WinItem::Draw(GLuint ShaderProgram, GLuint SVBO, GLuint SNVBO)
{
	if (is_activate) {
		float size = 1.0f / 80.0f;

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tm = glm::mat4(1.0f);
		glm::mat4 sm = glm::mat4(1.0f);

		sm = glm::scale(sm, glm::vec3(size, size, size));
		tm = glm::translate(tm, glm::vec3(Pos.x, 0.45f, Pos.z));


		model = tm * sm * model;

		int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		int objColorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
		glUniform3f(objColorLocation, 1.0, 1.0f, 1.0f);


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
}

void WinItem::Set_Pos(GLfloat x, GLfloat z)
{
	this->Pos.x = x;
	this->Pos.z = z;
}

glm::vec3 WinItem::Get_Pos()
{
	return this->Pos;
}

GLfloat WinItem::Get_Size()
{
	return rsize;
}