#pragma once
#ifndef __MAP
#define __MAP

#include "Wall.h"
#include "Thorn.h"

#define THORN_COUNT 3
#define WALL_COUNT 42
#define TRAP_COUNT 9


struct TrapPoint {
	float x, z;
};
void draw_floor(GLuint ShaderProgram, GLuint VBO, GLuint EBO);

void init_wall(Wall walls[], Thorn thorns[]);
void draw_map(GLuint ShaderProgram, GLuint VBO, GLuint EBO, GLuint ConVBO, GLuint ConEBO, Wall walls[], Thorn thorns[]);

void draw_thorn(GLuint ShaderProgram, GLuint ConVBO, GLuint ConEBO, float x, float z); //가시함정
void draw_thorns(GLuint ShaderProgram, GLuint ConVBO, GLuint ConEBO, TrapPoint id);

void draw_hole(GLuint ShaderProgram, GLuint VBO, GLuint EBO, TrapPoint id);// 구덩이함정
void draw_slow(GLuint ShaderProgram, GLuint VBO, GLuint EBO, TrapPoint id);//슬로우 함정

#endif