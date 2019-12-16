#pragma once
#ifndef __MAP
#define __MAP

#include "Wall.h"
#include "Thorn.h"
#include "Hole.h"
#include "Deceleration_Trap.h"

#define WALL_COUNT 42
#define TRAP_COUNT 3


struct TrapPoint {
	float x, z;
};
void draw_floor(GLuint ShaderProgram, GLuint VBO, GLuint EBO);

void init_wall(Wall walls[], Thorn thorns[], Hole holes[], Deceleration_Trap traps[]);
void draw_map(GLuint ShaderProgram, GLuint VBO, GLuint EBO, GLuint ConVBO, GLuint ConEBO, Wall walls[], Thorn thorns[], Hole holes[], Deceleration_Trap traps[]);

#endif