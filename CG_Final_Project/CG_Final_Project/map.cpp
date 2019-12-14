#include "map.h"


void draw_floor(GLuint ShaderProgram, GLuint VBO, GLuint EBO)
{
	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f); //회전
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
	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f); //회전

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

	// 가로폭을 사용자정의로 지정하면 세로폭은 0.1로  둘중하나는 무조건 0.1
	float defalut_width = 1.0f;
	float defalut_width2 = 0.1f;
	draw_floor(ShaderProgram, VBO, EBO);

	// 좌표점찍기
	for (float i = -5.0f; i <= 5.0f; i += 1.0f) {
		for (float j = -5.0f; j <= 5.0f; j += 1.0f)
			draw_wall(ShaderProgram, VBO, EBO, j, i, defalut_width2, defalut_width2);
	}

	//좌표줄때 옆으로 두배늘리고 싶으면 x좌표를 2배늘린것의 중간값을 줘야됨
	//ex   좌표 0~2로가는 길이의 벽만들려면 초기값을 1로하고 가로너비를 2를 준다.


	//1번 벽
	draw_wall(ShaderProgram, VBO, EBO, -4.0f, -3.5f, defalut_width2, 1.0f);

	////2번벽 뻐큐모양
	draw_wall(ShaderProgram, VBO, EBO, -2.0f, -4.0f, 2.0f, defalut_width2); //가로
	draw_wall(ShaderProgram, VBO, EBO, -2.0f, -3.5f, defalut_width2, defalut_width); //세로

	//3번벽
	draw_wall(ShaderProgram, VBO, EBO, 2.0f, -4.0f, 2.0f, defalut_width2); //가로
	draw_wall(ShaderProgram, VBO, EBO, 2.0f, -3.5f, defalut_width2, defalut_width); //세로

	//4번벽
	draw_wall(ShaderProgram, VBO, EBO, 4.0f, -3.5f, defalut_width2, defalut_width);

	//5번벽
	draw_wall(ShaderProgram, VBO, EBO, -4.5f, -2.0f, defalut_width, defalut_width2);


	//6번벽 십자가모양
	draw_wall(ShaderProgram, VBO, EBO, -3.0f, -1.0f, 2.0f, defalut_width2); //가로
	draw_wall(ShaderProgram, VBO, EBO, -3.0f, -1.5f, defalut_width2, 3.0f); //세로

	//7번벽
	draw_wall(ShaderProgram, VBO, EBO, -1.5f, -2.0f, defalut_width, defalut_width2);

	//8번벽
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, -3.0f, 2.0f, defalut_width2); //가로
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, -2.5f, defalut_width2, defalut_width); //가로

	//9번벽
	draw_wall(ShaderProgram, VBO, EBO, 1.5f, -2.0f, defalut_width, defalut_width2);

	//10번벽
	draw_wall(ShaderProgram, VBO, EBO, 3.0f, -1.0f, 2.0f, defalut_width2); //가로
	draw_wall(ShaderProgram, VBO, EBO, 3.0f, -1.5f, defalut_width2, 3.0f); //세로

	//11번벽
	draw_wall(ShaderProgram, VBO, EBO, 4.5f, -2.0f, defalut_width, defalut_width2);

	//12번
	draw_wall(ShaderProgram, VBO, EBO, -4.5f, 0.0f, defalut_width, defalut_width2);

	//13번
	draw_wall(ShaderProgram, VBO, EBO, -1.0f, -0.5f, defalut_width2, defalut_width); //왼쪽세로
	draw_wall(ShaderProgram, VBO, EBO, 1.0f, -0.5f, defalut_width2, defalut_width); //오른쪽세로
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, -1.0f, 2.0f, defalut_width2); //위쪽 가로
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, 0.0f, 2.0f, defalut_width2); //위쪽 가로

	//14번
	draw_wall(ShaderProgram, VBO, EBO, 4.5f, 0.0f, defalut_width, defalut_width2);

	//15번 ㄱ모양 벽
	draw_wall(ShaderProgram, VBO, EBO, -3.5f, 1.0f, defalut_width, defalut_width2);//가로
	draw_wall(ShaderProgram, VBO, EBO, -3.0f, 1.5f, defalut_width2, defalut_width);//세로

	//16번
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, 1.0f, 2.0f, defalut_width2);//가로
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, 1.5f, defalut_width2, defalut_width);//세로

	//17번
	draw_wall(ShaderProgram, VBO, EBO, 3.5f, 1.0f, defalut_width, defalut_width2);//가로
	draw_wall(ShaderProgram, VBO, EBO, 3.0f, 1.5f, defalut_width2, defalut_width);//세로

	//18번
	draw_wall(ShaderProgram, VBO, EBO, -1.5f, 2.0f, defalut_width, defalut_width2);

	//19번
	draw_wall(ShaderProgram, VBO, EBO, 1.5f, 2.0f, defalut_width, defalut_width2);

	//20번
	draw_wall(ShaderProgram, VBO, EBO, -4.5f, 3.0f, defalut_width, defalut_width2);

	//21번
	draw_wall(ShaderProgram, VBO, EBO, -3.0f, 4.0f, 2.0f, defalut_width2);//가로
	draw_wall(ShaderProgram, VBO, EBO, -3.0f,3.5f, defalut_width2, defalut_width);//세로

	//22번
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, 3.0f, 2.0f, defalut_width2);//가로
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, 3.5f, defalut_width2, defalut_width);//세로

	//23
	draw_wall(ShaderProgram, VBO, EBO, 3.0f, 4.0f, 2.0f, defalut_width2);//가로
	draw_wall(ShaderProgram, VBO, EBO, 3.0f, 3.5f, defalut_width2, defalut_width);//세로

	//24
	draw_wall(ShaderProgram, VBO, EBO, 4.5f, 3.0f, defalut_width, defalut_width2);

	//테두리
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, -5.0f, 10.0f, defalut_width2);
	draw_wall(ShaderProgram, VBO, EBO, 0.0f, 5.0f, 10.0f, defalut_width2);
	draw_wall(ShaderProgram, VBO, EBO, -5.0f, 0.0f, defalut_width2, 10.0f);
	draw_wall(ShaderProgram, VBO, EBO, 5.0f, 0.0f, defalut_width2, 10.0f);
	
}