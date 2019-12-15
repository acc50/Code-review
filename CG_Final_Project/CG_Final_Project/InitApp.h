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
void view(GLuint ShaderProgram, EViewPoint viewPoint, glm::vec3 EYE, glm::vec3 AT, glm::vec3 UP);
void Myprojection(GLuint ShaderProgra, EViewPoint viewPoint);
