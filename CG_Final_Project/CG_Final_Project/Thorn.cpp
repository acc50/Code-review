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
	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 tm = glm::mat4(1.0f); //회전
	glm::mat4 rm = glm::mat4(1.0f); //회전
	glm::mat4 sm = glm::mat4(1.0f); //회전

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
	glVertexAttribPointer(frag_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치

	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(pos_id);
	glDisableVertexAttribArray(frag_id);
}

void Thorn::Update(glm::vec3 Pos)
{
	if (!is_activated && !is_detect_player) {		//발동하지 않았다면 플레이어 감지  && 감지하지 않았다면
		this->Detect_to_Player(Pos);
	}

	if (is_detect_player) {		// 플레이어를 감지했다면
		height += 0.1f;
		time += 0.1f;

		if (height > MAX_HEIGHT) {		// 가시가  최대 높이로 커졌다면

			// 최대 높이로 고정
			height = MAX_HEIGHT;
		}

		if (time > duration) {		// 최대높이에서 기다렸다가 일정시간이 지나면

			// 가시를 발동했다 함
			is_activated = true;
			is_detect_player = false;
			time = 0.0f;
			height = 0.0f;
		}
	}

	if (is_activated) {		// 감지 후 가시 함정이 발동되었다면
		
		time += 0.1f;

		if (time > cool_time) {		// 일정 시간이 지나면 다시 발동할 수 있게 됨
			is_activated = false;

			time = 0.0f;
		}
	}

}

void Thorn::Detect_to_Player(glm::vec3 Pos)		// 플레이어를 감지함
{
	GLfloat x;
	GLfloat z;

	x = this->Pos.x - Pos.x;
	z = this->Pos.z - Pos.z;

	if ((x * x + z * z) < detect_range) {		// 감지범위 내로 플레이어가 들어오면

		is_detect_player = true;			// 감지했나 = true

	}

	
}