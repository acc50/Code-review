#include "Thorn.h"



Thorn::Thorn()
{
}


Thorn::~Thorn()
{
}

void Thorn::Set_Pos(GLfloat x, GLfloat z)
{
	this->Pos.x = x;
	this->Pos.z = z;
}

void Thorn::Draw(GLuint ShaderProgram, GLuint ConVBO, GLuint ConEBO)
{
	for (float i = -size; i < size * 1.5f; i += size)
		for (float j = -size; j < size * 1.5f; j += size)
			this->Render(ShaderProgram, ConVBO, ConEBO, Pos.x + j, Pos.z + i);
}

void Thorn::Render(GLuint ShaderProgram, GLuint ConVBO, GLuint ConEBO, GLfloat x, GLfloat z)
{
	glm::mat4 model = glm::mat4(1.0f); //����
	glm::mat4 tm = glm::mat4(1.0f); //ȸ��
	glm::mat4 rm = glm::mat4(1.0f); //ȸ��
	glm::mat4 sm = glm::mat4(1.0f); //ȸ��

	this->size = 1.0f / 6.0f;

	tm = glm::translate(tm, glm::vec3(x, height, z));
	sm = glm::scale(sm, glm::vec3(size, height*2.0f, size));

	model = tm * sm;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int colorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(colorLocation, 1.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, ConVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ConEBO);
	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	GLuint frag_id = glGetAttribLocation(ShaderProgram, "vColor");
	glEnableVertexAttribArray(frag_id);
	glVertexAttribPointer(frag_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//3��° ���ڴ� ���������� �󸶳� ��������, �ǵڿ� ���ڴ� ��� �����ұ� x,y,z,r,g,b,�ϱ�  3�������ͽ����ؼ� 6ĭ�������� ����������ġ

	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(pos_id);
	glDisableVertexAttribArray(frag_id);
}

void Thorn::Update(glm::vec3 Pos)
{
	if (!is_activated && !is_detect_player) {		//�ߵ����� �ʾҴٸ� �÷��̾� ����  && �������� �ʾҴٸ�
		this->Detect_to_Player(Pos);
	}

	if (is_detect_player) {		// �÷��̾ �����ߴٸ�
		height += 0.1f;
		time += 0.1f;

		if (height > MAX_HEIGHT) {		// ���ð�  �ִ� ���̷� Ŀ���ٸ�

			// �ִ� ���̷� ����
			height = MAX_HEIGHT;
		}

		if (time > duration) {		// �ִ���̿��� ��ٷȴٰ� �����ð��� ������

			// ���ø� �ߵ��ߴ� ��
			is_activated = true;
			is_detect_player = false;
			time = 0.0f;
			height = 0.0f;
		}
	}

	if (is_activated) {		// ���� �� ���� ������ �ߵ��Ǿ��ٸ�
		
		time += 0.1f;

		if (time > cool_time) {		// ���� �ð��� ������ �ٽ� �ߵ��� �� �ְ� ��
			is_activated = false;

			time = 0.0f;
		}
	}

}

void Thorn::Detect_to_Player(glm::vec3 Pos)		// �÷��̾ ������
{
	GLfloat x;
	GLfloat z;

	x = this->Pos.x - Pos.x;
	z = this->Pos.z - Pos.z;

	if ((x * x + z * z) < detect_range) {		// �������� ���� �÷��̾ ������

		is_detect_player = true;			// �����߳� = true

	}

	
}