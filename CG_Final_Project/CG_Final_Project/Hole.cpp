#include "Hole.h"



Hole::Hole()
{
}


Hole::~Hole()
{
}

glm::vec3 Hole::Get_Pos()
{
	return this->Pos;
}

GLfloat Hole::Get_Size()
{
	return this->size;
}

void Hole::Set_Pos(GLfloat x, GLfloat z)
{
	this->Pos.x = x;
	this->Pos.z = z;
}

bool Hole::Get_State()
{
	return this->is_activate;
}


void Hole::Draw(GLuint ShaderProgram, GLuint VBO, GLuint EBO)
{
	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f); //회전

	tm = glm::translate(tm, glm::vec3(Pos.x, 0.0f, Pos.z));
	sm = glm::scale(sm, glm::vec3(size, ysize, size));

	model = tm * rm * sm *model;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int colorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(colorLocation, this->Color.r, this->Color.g, this->Color.b);

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

	glDisableVertexAttribArray(pos_id);
	glDisableVertexAttribArray(frag_id);
}

void Hole::Update(glm::vec3 Pos)
{
	this->Detect_to_Player(Pos);


	if (is_detect_player && !is_activate) {		// 플레이어를 감지했다면
		
		this->Color.b = 0.0f;
		is_activate = true;		// 함정 발동
	}

}

void Hole::Detect_to_Player(glm::vec3 Pos)		// 플레이어를 감지함
{
	GLfloat x;
	GLfloat z;

	x = this->Pos.x - Pos.x;
	z = this->Pos.z - Pos.z;

	if ((x * x + z * z) < detect_range) {		// 감지범위 내로 플레이어가 들어오면

		is_detect_player = true;			// 감지했나 = true

	}

	else if(is_detect_player && is_activate){	// 한번만 실행되도록 함		
		is_detect_player = false;				// 감지범위 벗어나면 함정 발동 X
		is_activate = false;
		this->Color.b = 1.0f;
	}

}