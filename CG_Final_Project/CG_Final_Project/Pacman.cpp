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
	tm = glm::translate(tm, glm::vec3(Pos.x, 0.35f, Pos.z));


	model = tm * sm * model;

	int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int objColorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(objColorLocation, 1.0, 0.0f, 1.0f);


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
}

void Pacman::Move(bool Up, bool Down, bool Right, bool Left, glm::vec3 &EYE, glm::vec3 &AT, glm::vec3 &UP)
{
	
	if (is_lived) {		// ����־�� ������

		glm::vec3 front_dir = AT - EYE;		// EYE ���� AT ���� ���� ���� ����
		front_dir = front_dir / (sqrt(front_dir.x * front_dir.x + front_dir.y * front_dir.y + front_dir.z * front_dir.z));
		glm::vec3 back_dir = glm::vec3(-front_dir.x, -front_dir.y, -front_dir.z);

		glm::vec3 left_dir = glm::vec3(1.0f);		// UP X front_dir  ����
		left_dir.x = UP.y * front_dir.z - UP.z * front_dir.y;
		left_dir.y = UP.z * front_dir.x - UP.x * front_dir.z;
		left_dir.z = UP.x * front_dir.y - UP.y * front_dir.x;

		glm::vec3 right_dir = glm::vec3(-left_dir.x, -left_dir.y, -left_dir.z);

		if (Up) {
			Pos.x += front_dir.x / sensitive;
			Pos.z += front_dir.z / sensitive;

		}

		if (Down) {
			Pos.x += back_dir.x / sensitive;
			Pos.z += back_dir.z / sensitive;

		}

		if (Left) {
			Pos.x += left_dir.x / sensitive;
			Pos.z += left_dir.z / sensitive;

		}

		if (Right) {
			Pos.x += right_dir.x / sensitive;
			Pos.z += right_dir.z / sensitive;
		}

		glm::vec3 temp = Pos - EYE;  // -> Pos ���� EYE �� ���� ����

		AT.x += temp.x;
		AT.z += temp.z;


		EYE = this->Pos;		// ī�޶��� ��ġ�� Pos�� �׻� �̵���Ŵ
	}

}

void Pacman::Update(bool JUMP, glm::vec3 &EYE, glm::vec3 &AT, glm::vec3 &UP)
{
	GLfloat temp = Pos.y;

	if (is_lived) {
		Fall(EYE, AT, UP);
		Jump(JUMP, EYE, AT, UP);


		EYE.y = Pos.y;
		
		temp = Pos.y - temp;

		AT.y += temp;
	}
}

void Pacman::Fall(glm::vec3 &EYE, glm::vec3 &AT, glm::vec3 &UP)
{
	if (!is_on_floor) {
		Pos.y += fall_speed;
	}
}

void Pacman::Fall_Hole()
{
	is_on_floor = false;	// �߷� �ۿ�
	jump_count = 0;			// ���� �Ұ���
	is_fall = true;			// ������ ���� ������ true
	is_jump = false;
}

void Pacman::Jump(bool Space, glm::vec3 &EYE, glm::vec3 &AT, glm::vec3 &UP)
{
	if (is_on_floor && jump_count > 0 && Space) {	// ������ �ְ�, ���� Ƚ���� ������ ����
		is_on_floor = false;
		is_jump = true;
		jump_count = 0;
	}

	if (is_jump) {
		Pos.y += jump_speed;

		std::cout << Pos.y << std::endl;

		if (Pos.y >= this->MAX_HEIGHT) {		// �ִ���̱��� �ö󰡸�
			is_jump = false;
		}
	}

}

void Pacman::Set_Jump()
{
	is_on_floor = true;
	jump_count = 1;
	is_jump = false;
}

void Pacman::Set_Pos_x(GLfloat x)
{
	this->Pos.x = x;
}

void Pacman::Set_Pos_y()
{
	this->Pos.y = 0.0f + 1.0f;
}

void Pacman::Set_Pos_z(GLfloat z)
{
	this->Pos.z = z;
}

glm::vec3 Pacman::Get_Pos()
{
	return this->Pos;
}

GLfloat Pacman::Get_Size()
{
	return this->rsize;
}

void Pacman::Set_Speed(GLfloat speed)
{
	this->sensitive = speed;
}

GLfloat Pacman::Get_Speed()
{
	return sensitive;
}

void Pacman::Decrease_Life()
{
	this->life -= 1;

	if (life < 0) {
		std::cout << "game over" << std::endl;

	}
	else {
		is_lived = true;
		revive_count = 0.0f;
	}
}

void Pacman::Revive(glm::vec3 &EYE, glm::vec3 &AT, GLfloat &yaw, GLfloat &pitch)
{
	this->revive_count += 0.1f;

	std::cout << revive_count << std::endl;

	if (revive_count > this->MAX_COUNT) {		// ��Ȱ ��� �ð��� ������
		this->Decrease_Life();

		std::cout << "��Ȱ" << std::endl;

		if (life >= 0) {
			EYE = start_Pos;
			Pos = start_Pos;
			AT = start_AT;
			yaw = 0.0f;
			pitch = 0.0f;
		}
	}
	
}


void Pacman::Die()
{
	this->is_lived = false;
}

bool Pacman::Get_is_lived()
{
	return this->is_lived;
}

int Pacman::Get_lifecount()
{
	return this->life;
}
