#include "Ghost.h"



Ghost::Ghost()
{
}


Ghost::~Ghost()
{

}

void Ghost::Draw(GLuint ShaderProgram, GLuint SVBO, GLuint SNVBO)
{
	float size = 1.0f / 80.0f;

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);

	sm = glm::scale(sm, glm::vec3(size, size, size));
	tm = glm::translate(tm, glm::vec3(Pos.x, Pos.y, Pos.z));


	model = tm * sm * model;

	int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int objColorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(objColorLocation, Color.r, Color.g, Color.b);


	glBindBuffer(GL_ARRAY_BUFFER, SVBO);
	int light_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(light_id);
	glVertexAttribPointer(light_id, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, SNVBO);

	//int normal_id = glGetAttribLocation(ShaderProgram, "vNormal");  //노말
	//
	//glEnableVertexAttribArray(normal_id);
	//glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치

	glDrawArrays(GL_TRIANGLES, 0, 2880);

	glDisableVertexAttribArray(light_id);
	//glDisableVertexAttribArray(normal_id);
}

void Ghost::Update()
{
	if (is_move) {
		Move();
	}

	else {
		time += 0.1f;

		if (time > WAITING_TIME) {
			is_move = true;
		}
	}
}

void Ghost::Move()
{
	if (patrol_type == 1)
		first_Patrol();
	else if (patrol_type == 2) {
		second_Patrol();
	}

	else if (patrol_type == 3) {
		third_Patrol();
	}

}

void Ghost::first_Patrol()
{
	if(!is_starting_point){
		int next_point = (cur_point + 1) % 8;

		glm::vec3 next = glm::vec3(0.0f, 0.0f, 0.0f);

		next.x = startingPoint[next_point].x - startingPoint[cur_point].x;		// x 방향벡터
		next.z = startingPoint[next_point].z - startingPoint[cur_point].z;		// z 방향벡터

		//정규화
		next = next / sqrt(next.x * next.x + next.y * next.y + next.z * next.z);
		next.x /= speed;
		next.z /= speed;

		this->Pos.x += next.x;
		this->Pos.z += next.z;

		if (fabsf(Pos.x - startingPoint[next_point].x) <= 0.001f && fabsf(Pos.z - startingPoint[next_point].z) <= 0.001f)	// 다음 위치에 유령이 도달하면
		{
			cur_point += 1;

			if (cur_point == 7) {
				is_starting_point = true;
				cur_point = 0;
			}
		}

	}

	else {
		int next_point = (cur_point + 1) % 36;

		glm::vec3 next = glm::vec3(0.0f, 0.0f, 0.0f);

		next.x = patrolPoint[next_point].x - patrolPoint[cur_point].x;		// x 방향벡터
		next.z = patrolPoint[next_point].z - patrolPoint[cur_point].z;		// z 방향벡터

		//정규화
		next = next / sqrt(next.x * next.x + next.y * next.y + next.z * next.z);
		next.x /= speed;
		next.z /= speed;

		this->Pos.x += next.x;
		this->Pos.z += next.z;

		if (fabsf(Pos.x - patrolPoint[next_point].x) <= 0.001f && fabsf(Pos.z - patrolPoint[next_point].z) <= 0.001f)	// 다음 위치에 유령이 도달하면
		{
			cur_point = (cur_point + 1) % 36;
		}
	}
}

void Ghost::second_Patrol()
{
	if (!is_starting_point) {
		int next_point = (cur_point + 1) % 3;

		glm::vec3 next = glm::vec3(0.0f, 0.0f, 0.0f);

		next.x = startingPoint2[next_point].x - startingPoint2[cur_point].x;		// x 방향벡터
		next.z = startingPoint2[next_point].z - startingPoint2[cur_point].z;		// z 방향벡터

		//정규화
		next = next / sqrt(next.x * next.x + next.y * next.y + next.z * next.z);
		next.x /= speed;
		next.z /= speed;

		this->Pos.x += next.x;
		this->Pos.z += next.z;

		if (fabsf(Pos.x - startingPoint2[next_point].x) <= 0.001f && fabsf(Pos.z - startingPoint2[next_point].z) <= 0.001f)	// 다음 위치에 유령이 도달하면
		{
			cur_point += 1;

			if (cur_point == 2) {
				is_starting_point = true;
				cur_point = 5;
			}
		}
	}

	else {
		int next_point = (cur_point + 1) % 24;

		glm::vec3 next = glm::vec3(0.0f, 0.0f, 0.0f);

		next.x = patrolPoint2[next_point].x - patrolPoint2[cur_point].x;		// x 방향벡터
		next.z = patrolPoint2[next_point].z - patrolPoint2[cur_point].z;		// z 방향벡터

		//정규화
		next = next / sqrt(next.x * next.x + next.y * next.y + next.z * next.z);
		next.x /= speed;
		next.z /= speed;

		this->Pos.x += next.x;
		this->Pos.z += next.z;

		if (fabsf(Pos.x - patrolPoint2[next_point].x) <= 0.001f && fabsf(Pos.z - patrolPoint2[next_point].z) <= 0.001f)	// 다음 위치에 유령이 도달하면
		{
			cur_point = (cur_point + 1) % 24;
		}
	}
}

void Ghost::third_Patrol()
{
	if (!is_starting_point) {
		int next_point = (cur_point + 1) % 4;

		glm::vec3 next = glm::vec3(0.0f, 0.0f, 0.0f);

		next.x = startingPoint3[next_point].x - startingPoint3[cur_point].x;		// x 방향벡터
		next.z = startingPoint3[next_point].z - startingPoint3[cur_point].z;		// z 방향벡터

		//정규화
		next = next / sqrt(next.x * next.x + next.y * next.y + next.z * next.z);
		next.x /= speed;
		next.z /= speed;

		this->Pos.x += next.x;
		this->Pos.z += next.z;

		if (fabsf(Pos.x - startingPoint3[next_point].x) <= 0.001f && fabsf(Pos.z - startingPoint3[next_point].z) <= 0.001f)	// 다음 위치에 유령이 도달하면
		{
			cur_point += 1;

			if (cur_point == 3) {
				is_starting_point = true;
				cur_point = 27;
			}
		}
	}

	else {
		int next_point = (cur_point + 1) % 46;

		glm::vec3 next = glm::vec3(0.0f, 0.0f, 0.0f);

		next.x = patrolPoint3[next_point].x - patrolPoint3[cur_point].x;		// x 방향벡터
		next.z = patrolPoint3[next_point].z - patrolPoint3[cur_point].z;		// z 방향벡터

		//정규화
		next = next / sqrt(next.x * next.x + next.y * next.y + next.z * next.z);
		next.x /= speed;
		next.z /= speed;

		this->Pos.x += next.x;
		this->Pos.z += next.z;

		if (fabsf(Pos.x - patrolPoint3[next_point].x) <= 0.001f && fabsf(Pos.z - patrolPoint3[next_point].z) <= 0.001f)	// 다음 위치에 유령이 도달하면
		{
			cur_point = (cur_point + 1) % 46;
		}
	}
}

void Ghost::Init(GLfloat x, GLfloat z, GLfloat r, GLfloat g, GLfloat b, int type)
{
	this->Pos.x = x;
	this->Pos.z = z;
	Color.r = r;
	Color.g = g;
	Color.b = b;
	this->patrol_type = type;
}

void Ghost::Set_Pos_x(GLfloat x)
{
	this->Pos.x = x;
}

void Ghost::Set_Pos_y()
{

}

void Ghost::Set_Pos_z(GLfloat z)
{
	this->Pos.z = z;
}

glm::vec3 Ghost::Get_Pos()
{
	return this->Pos;
}

GLfloat Ghost::Get_Size()
{
	return this->rsize;
}