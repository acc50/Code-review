
#include "InitApp.h"

bool InitProgram(unsigned int& ShaderProgram)
{
	const char* vertexSource = filetobuf("Vertex.glsl");
	const char* fragmentSource = filetobuf("Fragment.glsl");
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	if (!Check(vertexShader)) return false;

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	if (!Check(fragmentShader)) return false;

	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vertexShader);
	glAttachShader(ShaderProgram, fragmentShader);
	glLinkProgram(ShaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (!Check(ShaderProgram)) {
		glDeleteProgram(ShaderProgram);
		return false;

	}


}


bool Check(unsigned int ShaderProgram)
{
	GLint state;
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &state);
	if (state == GL_FALSE) {
		int infologLength = 0;
		glGetProgramiv(ShaderProgram, GL_INFO_LOG_LENGTH, &infologLength);
		if (infologLength > 0) {
			char* infolog = new char[infologLength];
			glGetProgramInfoLog(ShaderProgram, infologLength, NULL, infolog);
			std::cout << infolog << std::endl;
			delete[] infolog;
		}
		return false;
	}
	return true;
}


void CreateCon(GLuint& ConEBO, GLuint& ConVBO)
{
	GLfloat vertexData[] = {
		0.0f,0.5f,0.0f,		1.0f,1.0f,0.0f,  //0번점
		-0.5f,-0.5f,-0.5f,	0.0f,1.0f,0.0f,  //1번점
		-0.5f,-0.5f,0.5f,	1.0f,0.0f,0.0f,  //2번점
		0.5f,-0.5f,0.5f,	1.0f,1.0f,0.5f,  //3번점
		0.5f,-0.5f,-0.5f,	0.0f,0.0f,0.0f  //4번점
	};
	glGenBuffers(1, &ConVBO);

	glBindBuffer(GL_ARRAY_BUFFER, ConVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	unsigned int indexDeta[] = {
		2,1,3,
		3,1,4, //밑면
		0,2,3, //앞면
		0,1,2,//좌측면
		0,4,1,//뒷면
		0,3,4,//우측면	
	};
	glGenBuffers(1, &ConEBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ConEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 18, &indexDeta, GL_STATIC_DRAW);
}
void CreateCube(GLuint ShaderProgram,GLuint& EBO, GLuint& VBO)
{

	GLfloat vertex[] = {
		-0.5f,0.5f,-0.5f,	1.0f,1.0f,0.0f,  //0번점
		-0.5f,0.5f,0.5f,	0.0f,1.0f,1.0f,  //1번점
		0.5f,0.5f,0.5f,		1.0f,0.0f,1.0f,  //2번점
		0.5f,0.5f,-0.5f,	0.0f,0.0f,1.0f,  //3번점

		-0.5f,-0.5f,-0.5f,	0.0f,1.0f,0.0f,  //4번점
		-0.5f,-0.5f,0.5f,	1.0f,0.0f,0.0f,  //5번점
		0.5f,-0.5f,0.5f,	1.0f,1.0f,0.5f,  //6번점
		0.5f,-0.5f,-0.5f,	0.0f,0.0f,0.0f,  //7번점
	};
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	
	

	//front
	GLint gIndices[]
	{
		0,1,2,
		0,2,3,  //윗면

		1,5,6,
		1,6,2, //앞면

		2,6,7,
		2,7,3, //우측면

		0,4,5,
		0,5,1, //좌측면

		5,4,6,
		4,7,6,// 밑면

		0,7,4, //뒷면
		0,3,7
	};

	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gIndices), &gIndices, GL_STATIC_DRAW);




}

void CreateAxis(GLuint& Axis)
{
	GLfloat AxisData[] = {
		1.0f,0.0f,0.0f,
		-1.0f,0.0f,0.0f,

		0.0f,1.0f,0.0f,
		0.0f,-1.0f,0.0f
	};
	glGenBuffers(1, &Axis);
	glBindBuffer(GL_ARRAY_BUFFER, Axis);
	glBufferData(GL_ARRAY_BUFFER, sizeof(AxisData), &AxisData, GL_STATIC_DRAW);
}



void view(GLuint ShaderProgram, EViewPoint viewPoint, glm::vec3 EYE, glm::vec3 AT, glm::vec3 UP, glm::vec3 T_EYE, glm::vec3 T_AT)
{

	glm::mat4 view = glm::mat4(1.0f);

	switch (viewPoint)
	{

	case E_DEFAULT_VIEW:
		view = glm::lookAt(EYE, AT, UP);		// 디폴트 뷰 일때의 view 
		break;

	case E_TOP_VIEW:
		view = glm::lookAt(T_EYE, T_AT, UP);		// 탑 뷰 일때의 view
		break;

	default:
		break;

	}

	unsigned int viewLocation = glGetUniformLocation(ShaderProgram, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
}

void Myprojection(GLuint ShaderProgram, EViewPoint viewPoint) {
	glm::mat4 projection = glm::mat4(1.0f);
	switch (viewPoint)
	{
	case E_DEFAULT_VIEW:
		projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 10.0f);
		break;
	case E_TOP_VIEW:
		projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 20.0f);
		break;
	default:
		break;

	}
	
	unsigned int projectionLocation = glGetUniformLocation(ShaderProgram, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}





GLvoid draw_cube(GLuint ShaderProgram, GLuint VBO, GLuint EBO)
{


	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f); //회전
	tm = glm::translate(tm, glm::vec3(1.0f, 0.0f, 0.0f));
	sm = glm::scale(sm, glm::vec3(0.25f, 0.25f, 0.25f));
	model = tm * rm * sm *model;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int colorLocation =glGetUniformLocation(ShaderProgram, "objectColor");
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

GLvoid drawCon(GLuint ShaderProgram, GLuint ConVBO, GLuint ConEBO)
{
	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 tm = glm::mat4(1.0f); //회전
	glm::mat4 rm = glm::mat4(1.0f); //회전
	glm::mat4 sm = glm::mat4(1.0f); //회전
	tm = glm::translate(tm, glm::vec3(-1.0f, 0.0f, 0.0f));
	sm = glm::scale(sm, glm::vec3(0.5f, 0.5f, 0.5f));

	model = tm * sm;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
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


void CreateSphere(GLuint& VBO, GLuint& NVBO)
{
	std::vector< glm::vec3 > outvertex, outnormal;
	std::vector< glm::vec2 > outuv;
	loadObj("sphere.obj", outvertex, outnormal, outuv);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);


	glGenBuffers(1, &NVBO);
	glBindBuffer(GL_ARRAY_BUFFER, NVBO);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);

	std::cout << outvertex.size() << std::endl;
}

void draw_sphere(GLuint ShaderProgram, GLuint SVBO, GLuint SNVBO, float x, float z)
{
	float size = 1.0f / 80.0f;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	sm = glm::scale(sm, glm::vec3(size, size, size));
	tm = glm::translate(tm, glm::vec3(x, 0.35f, z));
	model = tm * sm * model;
	int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int objColorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(objColorLocation, 1.0, 1.0f, 0.0f);


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


bool is_Collision(GLfloat cx, GLfloat cz, GLfloat cr, GLfloat rx, GLfloat rz, GLfloat width, GLfloat depth)
{
	
	GLfloat left = (rx - width - cr);				//	사각형의 왼쪽 - 구의 반지름
	GLfloat back = (rz - depth - cr);				//	사각형의 뒷쪽 - 구의 반지름
	GLfloat front = (rz + depth + cr);				//	사각형의 앞쪽 + 구의 반지름
	GLfloat right = (rx + width + cr);				//	사각형의 오른쪽 + 구의 반지름

	// 사각형을 구의반지름만큼 확장


	// 확장한 사각형 안에 구 원점이 있으면 충돌
	if ((cx >= left && cx <= right) && (cz <= front && cz >= back)) {
		return true;
	}

	return false;
}


void renderBitmapCharacter(void *font,int lifeCount,int itemCount)
{
	const char* life = "life:";
	const char* remainjewel = "remain Jewel:";
	const char *c;
	char a[10];
	glRasterPos3f(-0.8, 0.9, 0.0f);//life id
	for (c = life; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
	itoa(lifeCount, a, 10);
	for (c = a; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *a);
	}
	glRasterPos3f(0.6, 0.9, 0.0f);//life id
	for (c = remainjewel; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
	itoa(itemCount, a, 10);
	for (c = a; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *a);
	}
}

