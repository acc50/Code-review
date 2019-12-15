#pragma once
#include "Wall.h"

struct TrapPoint {
	float x, z;
};
void draw_floor(GLuint ShaderProgram, GLuint VBO, GLuint EBO);

void init_wall();
void draw_wall(GLuint ShaderProgram, GLuint VBO, GLuint EBO, float x, float z, float width, float width2);
void draw_At(GLuint ShaderProgram, GLuint VBO, GLuint EBO, float x, float z, float width, float width2);
void draw_map(GLuint ShaderProgram, GLuint VBO, GLuint EBO, GLuint ConVBO, GLuint ConEBO);

void draw_thorn(GLuint ShaderProgram, GLuint ConVBO, GLuint ConEBO, float x, float z); //가시함정
void draw_thorns(GLuint ShaderProgram, GLuint ConVBO, GLuint ConEBO, TrapPoint id);

void draw_hole(GLuint ShaderProgram, GLuint VBO, GLuint EBO, TrapPoint id);// 구덩이함정
void draw_slow(GLuint ShaderProgram, GLuint VBO, GLuint EBO, TrapPoint id);//슬로우 함정