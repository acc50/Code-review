#pragma once
#include "global.h"
#include "map.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
bool InitProgram(unsigned int& ShaderProgram);

bool Check(unsigned int ShaderProgram);

void CreateAxis(GLuint& Axis);
void CreateCube(GLuint ShaderProgram, GLuint& EBO, GLuint& VBO);
void CreateCon(GLuint& EBO, GLuint& VBO);
GLvoid draw_cube(GLuint ShaderProgram, GLuint VBO, GLuint EBO);
GLvoid drawCon(GLuint ShaderProgram, GLuint ConVBO, GLuint ConEBO);
void view(GLuint ShaderProgram, EViewPoint viewPoint, float x, float y, float z, float AtX, float AtY, float angle);
void Myprojection(GLuint ShaderProgra, EViewPoint viewPoint);
int loadObj(const char* filename, std::vector< glm::vec3 >& outvertex, std::vector< glm::vec3 >& outnormal, std::vector< glm::vec2 >& outuv);
void CreateSphere(GLuint& VBO, GLuint& NVBO);
void draw_sphere(GLuint ShaderProgram, GLuint SVBO, GLuint SNVBO, float x, float z);