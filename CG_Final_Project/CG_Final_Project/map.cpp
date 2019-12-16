#include "map.h"



TrapPoint trapPoint[TRAP_COUNT * 3] = {
	{-2.5f,-4.5f},{-0.3f,-3.7f},{2.0f,-4.5f},
	{-2.5f,0.0f},{2.0f,0.3f},{-3.5f,2.0f},
	{-1.5f,3.0f},{1.5f,3.0f},{3.5f,2.0f}

};

TrapPoint itemPoint[ITEM_COUNT] = {
	{-4.5f,-4.5f},{-3.5,-2.5},{-1.5f,-3.5},{-4.5,-2.5},//2�и�
	{1.5f,-4.5f},{4.5f,-4.5f},{2.5f,-2.5f},{3.5f,-1.5f},//1�и�
	{-4.5f,0.5f},{-0.5f,1.5f},{-2.5f,2.5f},{-4.5f,4.5f},
	{3.5f,1.5f},{2.5f,3.5f},{0.5f,3.5f},{4.5f,4.5f}


};

void draw_floor(GLuint ShaderProgram, GLuint VBO, GLuint EBO, Pacman* pacman)
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
	glUniform3f(colorLocation, 0.7f, 0.3f, 0.2f);

	int lightColorLocation = glGetUniformLocation(ShaderProgram, "LightColor");
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);

	int lightPosLocation = glGetUniformLocation(ShaderProgram, "LightPos");
	glUniform3f(lightPosLocation, 0.0f, 0.0f, 0.0f);
	std::cout << "pac X" << pacman->Get_Pos().x << std::endl;


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	GLuint frag_id = glGetAttribLocation(ShaderProgram, "vNormal");
	glEnableVertexAttribArray(frag_id);
	glVertexAttribPointer(frag_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void init_wall(Wall walls[], Thorn thorns[], Hole holes[], Deceleration_Trap traps[])				// ��ǥ ���Ǵ� �ѹ��� ���⼭ ����
{

	// �������� ��������Ƿ� �����ϸ� �������� 0.1��  �����ϳ��� ������ 0.1
	float default_width = 1.0f;
	float default_width2 = 0.15f;

	//1�� ��
	walls[0].Set_Wall(-4.0f, -3.5f, default_width2, 1.0f);

	//2�� ��
	walls[1].Set_Wall(-2.0f, -4.0f, 2.0f, default_width2);
	walls[2].Set_Wall(-2.0f, -3.5f, default_width2, default_width);

	//3�� ��
	walls[3].Set_Wall(2.0f, -4.0f, 2.0f, default_width2);
	walls[4].Set_Wall(2.0f, -3.5f, default_width2, default_width);

	//4����
	walls[5].Set_Wall(4.0f, -3.5f, default_width2, default_width);

	//5����
	walls[6].Set_Wall(-4.5f, -2.0f, default_width, default_width2);


	//6���� ���ڰ����
	walls[7].Set_Wall(-3.0f, -1.0f, 2.0f, default_width2); //����
	walls[8].Set_Wall(-3.0f, -1.5f, default_width2, 3.0f); //����

	//7����
	walls[9].Set_Wall(-1.5f, -2.0f, default_width, default_width2);

	//8����
	walls[10].Set_Wall(0.0f, -3.0f, 2.0f, default_width2); //����
	walls[11].Set_Wall(0.0f, -2.5f, default_width2, default_width); //����

	//9����
	walls[12].Set_Wall(1.5f, -2.0f, default_width, default_width2);

	//10����
	walls[13].Set_Wall(3.0f, -1.0f, 2.0f, default_width2); //����
	walls[14].Set_Wall(3.0f, -1.5f, default_width2, 3.0f); //����

	//11����
	walls[15].Set_Wall(4.5f, -2.0f, default_width, default_width2);

	//12��
	walls[16].Set_Wall(-4.5f, 0.0f, default_width, default_width2);

	//13��
	walls[17].Set_Wall(-1.0f, -0.5f, default_width2, default_width); //���ʼ���
	walls[18].Set_Wall(1.0f, -0.5f, default_width2, default_width); //�����ʼ���
	walls[19].Set_Wall(0.0f, -1.0f, 2.0f, default_width2); //���� ����
	walls[20].Set_Wall(0.0f, 0.0f, 2.0f, default_width2); //���� ����

	//14��
	walls[21].Set_Wall(4.5f, 0.0f, default_width, default_width2);

	//15�� ����� ��
	walls[22].Set_Wall(-3.5f, 1.0f, default_width, default_width2);//����
	walls[23].Set_Wall(-3.0f, 1.5f, default_width2, default_width);//����

	//16��
	walls[24].Set_Wall(0.0f, 1.0f, 2.0f, default_width2);//����
	walls[25].Set_Wall(0.0f, 1.5f, default_width2, default_width);//����

	//17��
	walls[26].Set_Wall(3.5f, 1.0f, default_width, default_width2);//����
	walls[27].Set_Wall(3.0f, 1.5f, default_width2, default_width);//����

	//18��
	walls[28].Set_Wall(-1.5f, 2.0f, default_width, default_width2);

	//19��
	walls[29].Set_Wall(1.5f, 2.0f, default_width, default_width2);

	//20��
	walls[30].Set_Wall(-4.5f, 3.0f, default_width, default_width2);

	//21��
	walls[31].Set_Wall(-3.0f, 4.0f, 2.0f, default_width2);//����
	walls[32].Set_Wall(-3.0f, 3.5f, default_width2, default_width);//����

	//22��
	walls[33].Set_Wall(0.0f, 3.0f, 2.0f, default_width2);//����
	walls[34].Set_Wall(0.0f, 3.5f, default_width2, default_width);//����

	//23
	walls[35].Set_Wall(3.0f, 4.0f, 2.0f, default_width2);//����
	walls[36].Set_Wall(3.0f, 3.5f, default_width2, default_width);//����

	//24
	walls[37].Set_Wall(4.5f, 3.0f, default_width, default_width2);

	//�׵θ�
	walls[38].Set_Wall(0.0f, -5.0f, 10.0f, default_width2);
	walls[39].Set_Wall(0.0f, 5.0f, 10.0f, default_width2);
	walls[40].Set_Wall(-5.0f, 0.0f, default_width2, 10.0f);
	walls[41].Set_Wall(5.0f, 0.0f, default_width2, 10.0f);


	thorns[0].Set_Pos(trapPoint[1].x, trapPoint[1].z);
	thorns[1].Set_Pos(trapPoint[3].x, trapPoint[3].z);
	thorns[2].Set_Pos(trapPoint[4].x, trapPoint[4].z);

	holes[0].Set_Pos(trapPoint[0].x, trapPoint[0].z);
	holes[1].Set_Pos(trapPoint[5].x, trapPoint[5].z);
	holes[2].Set_Pos(trapPoint[8].x, trapPoint[8].z);

	traps[0].Set_Pos(trapPoint[2].x, trapPoint[2].z);
	traps[1].Set_Pos(trapPoint[6].x, trapPoint[6].z);
	traps[2].Set_Pos(trapPoint[7].x, trapPoint[7].z);


}

void draw_map(GLuint ShaderProgram, SuperGLuint super, Pacman* pacman, Wall walls[], Thorn thorns[], Hole holes[], Deceleration_Trap traps[])
{
	draw_floor(ShaderProgram, super.VBO, super.EBO,pacman);

	// ��ǥ�����
	/*for (float i = -5.0f; i <= 5.0f; i += 1.0f) {
		for (float j = -5.0f; j <= 5.0f; j += 1.0f)
			draw_wall(ShaderProgram, VBO, EBO, j, i, default_width2, default_width2);
	}*/

	// �� �׸���
	for (int i = 0; i < WALL_COUNT; ++i) {
		walls[i].Draw(ShaderProgram, super.VBO, super.EBO,pacman);
	}

	//��ǥ�ٶ� ������ �ι�ø��� ������ x��ǥ�� 2��ø����� �߰����� ��ߵ�
	//ex   ��ǥ 0~2�ΰ��� ������ ��������� �ʱⰪ�� 1���ϰ� ���γʺ� 2�� �ش�.

	for (int i = 0; i < TRAP_COUNT; ++i) {
		thorns[i].Draw(ShaderProgram, super.ConVBO, super.ConEBO,pacman);
		holes[i].Draw(ShaderProgram, super.VBO, super.EBO,pacman);
		traps[i].Draw(ShaderProgram, super.VBO, super.EBO,pacman);
	}

	for (int i = 0; i < 4; ++i)
		draw_WinItem(ShaderProgram, super.SVBO, super.SNVBO, itemPoint[itemID[i]]);

}



void draw_WinItem(GLuint ShaderProgram, GLuint SVBO, GLuint SNVBO, TrapPoint p)
{
	float size = 1.0f / 80.0f;

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);

	sm = glm::scale(sm, glm::vec3(size, size, size));
	tm = glm::translate(tm, glm::vec3(p.x, 0.45f, p.z));


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
