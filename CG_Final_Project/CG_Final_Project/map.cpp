#include "map.h"
#include <random>

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution <int> uid(0, (TRAP_COUNT * 3 - 1));
std::uniform_real_distribution <GLfloat> color(0.3f, 0.9f);

TrapPoint trapPoint[TRAP_COUNT * 3] = {
	{-2.5f,-4.5f},{-0.3f,-3.7f},{2.0f,-4.5f},
	{-2.5f,0.0f},{2.0f,0.3f},{-3.5f,2.0f},
	{-1.5f,3.0f},{1.5f,3.0f},{3.5f,2.0f}
};

int flag[TRAP_COUNT * 3] = { 0, };

TrapPoint itemPoint[ITEM_COUNT] = {
	{-4.5f,-4.5f},{-3.5,-2.5},{-1.5f,-3.5},{-4.5,-2.5},//2�и�
	{1.5f,-4.5f},{4.5f,-4.5f},{2.5f,-2.5f},{3.5f,-1.5f},//1�и�
	{-4.5f,0.5f},{-0.5f,1.5f},{-2.5f,2.5f},{-4.5f,4.5f},
	{3.5f,1.5f},{2.5f,3.5f},{0.5f,3.5f},{4.5f,4.5f}
};

//Point patrolPoint[28] = {
//	{-4.5,-4.5},{-4.5,-2.5},{-3.5,-2.5},{-3.5,-1.5},{-4.5,-1.5},{-4.5,-0.5},{-3.5,-0.5},
//	{-3.5, 0.5},{-4.5, 0.5},{-4.5, 2.5},{-3.5, 2.5},{-3.5, 3.5},{-4.5, 3.5},{-4.5, 4.5},
//	{4.5,  4.5},{4.5,  3.5},{3.5,  3.5},{3.5,  2.5},{4.5, 2.5},{4.5,  0.5},{3.5,  0.5},
//	{3.5, -0.5},{4.5, -0.5},{4.5, -1.5},{3.5, -1.5},{3.5, -2.5},{4.5, -2.5},{4.5, -4.5}
//};

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

void init_wall(Wall walls[], Thorn thorns[], Hole holes[], Deceleration_Trap traps[], WinItem items[], Ghost ghosts[])				// ��ǥ ���Ǵ� �ѹ��� ���⼭ ����
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
	walls[19].Set_Wall(-0.7f, -1.0f, 0.7f, default_width2); //���� ����
	walls[42].Set_Wall(0.7f, -1.0f, 0.7f, default_width2);	// ���� ����
	walls[20].Set_Wall(0.0f, 0.0f, 2.0f, default_width2); //�Ʒ��� ����

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

	GLfloat gx = -0.5f;
	for (int i = 0; i < GHOST_COUNT; ++i) {
		ghosts[i].Init(gx, -0.5f, color(dre), color(dre), color(dre), 1);
		gx += 0.5f;
	}

	ghosts[0].Init(-4.5f, -4.5f, color(dre), color(dre), color(dre), 1);
	ghosts[1].Init(-0.5f, -3.5f, color(dre), color(dre), color(dre), 2);

	// --------------- ���� ���� ���� -------------



	int point[TRAP_COUNT * 3];
	int temp;

	for (int i = 0; i < TRAP_COUNT * 3; ++i) {
		
		while (1) {
			temp = uid(dre);

			if (flag[temp] == 0) {
				flag[temp] = 1;
				point[i] = temp;
				break;
			}
		}

	}

	for (int i = 0; i < TRAP_COUNT; ++i) {
		thorns[i].Set_Pos(trapPoint[point[i]].x, trapPoint[point[i]].z);
		holes[i].Set_Pos(trapPoint[point[i + 3]].x, trapPoint[point[i + 3]].z);
		traps[i].Set_Pos(trapPoint[point[i + 6]].x, trapPoint[point[i + 6]].z);
	}


	// --------------- ���� ���� ���� -------------



	for (int i = 0; i < WIN_COUNT; ++i) {
		items[i].Set_Pos(itemPoint[itemID[i]].x, itemPoint[itemID[i]].z);
	}
}

void draw_map(GLuint ShaderProgram, SuperGLuint super, Wall walls[], Thorn thorns[], Hole holes[], Deceleration_Trap traps[], WinItem items[], Ghost ghosts[])
{
	draw_floor(ShaderProgram, super.VBO, super.EBO);

	// ��ǥ�����
	/*for (float i = -5.0f; i <= 5.0f; i += 1.0f) {
		for (float j = -5.0f; j <= 5.0f; j += 1.0f)
			draw_wall(ShaderProgram, VBO, EBO, j, i, default_width2, default_width2);
	}*/

	// �� �׸���
	for (int i = 0; i < WALL_COUNT; ++i) {
		walls[i].Draw(ShaderProgram, super.VBO, super.EBO);
	}

	//��ǥ�ٶ� ������ �ι�ø��� ������ x��ǥ�� 2��ø����� �߰����� ��ߵ�
	//ex   ��ǥ 0~2�ΰ��� ������ ��������� �ʱⰪ�� 1���ϰ� ���γʺ� 2�� �ش�.

	for (int i = 0; i < TRAP_COUNT; ++i) {
		thorns[i].Draw(ShaderProgram, super.ConVBO, super.ConEBO);
		holes[i].Draw(ShaderProgram, super.VBO, super.EBO);
		traps[i].Draw(ShaderProgram, super.VBO, super.EBO);
	}

	for (int i = 0; i < WIN_COUNT; ++i) {
		items[i].Draw(ShaderProgram, super.SVBO, super.SNVBO);
	}

}