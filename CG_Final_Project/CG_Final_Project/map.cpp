#include "map.h"

#define WALL_COUNT 42

Wall walls[WALL_COUNT];

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

void init_wall()				// 좌표 정의는 한번만 여기서 해줌
{

	// 가로폭을 사용자정의로 지정하면 세로폭은 0.1로  둘중하나는 무조건 0.1
	float default_width = 1.0f;
	float default_width2 = 0.1f;

	//1번 벽
	walls[0].Set_Wall(-4.0f, -3.5f, default_width2, 1.0f);

	//2번 벽
	walls[1].Set_Wall(-2.0f, -4.0f, 2.0f, default_width2);
	walls[2].Set_Wall(-2.0f, -3.5f, default_width2, default_width);

	//3번 벽
	walls[3].Set_Wall(2.0f, -4.0f, 2.0f, default_width2);
	walls[4].Set_Wall(2.0f, -3.5f, default_width2, default_width);

	//4번벽
	walls[5].Set_Wall(4.0f, -3.5f, default_width2, default_width);

	//5번벽
	walls[6].Set_Wall(-4.5f, -2.0f, default_width, default_width2);


	//6번벽 십자가모양
	walls[7].Set_Wall(-3.0f, -1.0f, 2.0f, default_width2); //가로
	walls[8].Set_Wall(-3.0f, -1.5f, default_width2, 3.0f); //세로

	//7번벽
	walls[9].Set_Wall(-1.5f, -2.0f, default_width, default_width2);

	//8번벽
	walls[10].Set_Wall(0.0f, -3.0f, 2.0f, default_width2); //가로
	walls[11].Set_Wall(0.0f, -2.5f, default_width2, default_width); //가로

	//9번벽
	walls[12].Set_Wall(1.5f, -2.0f, default_width, default_width2);

	//10번벽
	walls[13].Set_Wall(3.0f, -1.0f, 2.0f, default_width2); //가로
	walls[14].Set_Wall(3.0f, -1.5f, default_width2, 3.0f); //세로

	//11번벽
	walls[15].Set_Wall(4.5f, -2.0f, default_width, default_width2);

	//12번
	walls[16].Set_Wall(-4.5f, 0.0f, default_width, default_width2);

	//13번
	walls[17].Set_Wall(-1.0f, -0.5f, default_width2, default_width); //왼쪽세로
	walls[18].Set_Wall(1.0f, -0.5f, default_width2, default_width); //오른쪽세로
	walls[19].Set_Wall(0.0f, -1.0f, 2.0f, default_width2); //위쪽 가로
	walls[20].Set_Wall(0.0f, 0.0f, 2.0f, default_width2); //위쪽 가로

	//14번
	walls[21].Set_Wall(4.5f, 0.0f, default_width, default_width2);

	//15번 ㄱ모양 벽
	walls[22].Set_Wall(-3.5f, 1.0f, default_width, default_width2);//가로
	walls[23].Set_Wall(-3.0f, 1.5f, default_width2, default_width);//세로

	//16번
	walls[24].Set_Wall(0.0f, 1.0f, 2.0f, default_width2);//가로
	walls[25].Set_Wall(0.0f, 1.5f, default_width2, default_width);//세로

	//17번
	walls[26].Set_Wall(3.5f, 1.0f, default_width, default_width2);//가로
	walls[27].Set_Wall(3.0f, 1.5f, default_width2, default_width);//세로

	//18번
	walls[28].Set_Wall(-1.5f, 2.0f, default_width, default_width2);

	//19번
	walls[29].Set_Wall(1.5f, 2.0f, default_width, default_width2);

	//20번
	walls[30].Set_Wall(-4.5f, 3.0f, default_width, default_width2);

	//21번
	walls[31].Set_Wall(-3.0f, 4.0f, 2.0f, default_width2);//가로
	walls[32].Set_Wall(-3.0f, 3.5f, default_width2, default_width);//세로

	//22번
	walls[33].Set_Wall(0.0f, 3.0f, 2.0f, default_width2);//가로
	walls[34].Set_Wall(0.0f, 3.5f, default_width2, default_width);//세로

	//23
	walls[35].Set_Wall(3.0f, 4.0f, 2.0f, default_width2);//가로
	walls[36].Set_Wall(3.0f, 3.5f, default_width2, default_width);//세로

	//24
	walls[37].Set_Wall(4.5f, 3.0f, default_width, default_width2);

	//테두리
	walls[38].Set_Wall(0.0f, -5.0f, 10.0f, default_width2);
	walls[39].Set_Wall(0.0f, 5.0f, 10.0f, default_width2);
	walls[40].Set_Wall(-5.0f, 0.0f, default_width2, 10.0f);
	walls[41].Set_Wall(5.0f, 0.0f, default_width2, 10.0f);
}

void draw_map(GLuint ShaderProgram, GLuint VBO, GLuint EBO)
{
	draw_floor(ShaderProgram, VBO, EBO);

	// 좌표점찍기
	/*for (float i = -5.0f; i <= 5.0f; i += 1.0f) {
		for (float j = -5.0f; j <= 5.0f; j += 1.0f)
			draw_wall(ShaderProgram, VBO, EBO, j, i, default_width2, default_width2);
	}*/

	// 벽 그리기
	for (int i = 0; i < WALL_COUNT; ++i) {
		walls[i].Draw(ShaderProgram, VBO, EBO);
	}

	//좌표줄때 옆으로 두배늘리고 싶으면 x좌표를 2배늘린것의 중간값을 줘야됨
	//ex   좌표 0~2로가는 길이의 벽만들려면 초기값을 1로하고 가로너비를 2를 준다.

}