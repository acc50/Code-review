#pragma once
#ifndef __MAP
#define __MAP

#include "Wall.h"
#include "Thorn.h"
#include "Hole.h"
#include "Deceleration_Trap.h"
#include "WinItem.h"
#include "Ghost.h"

#define WALL_COUNT 43
#define TRAP_COUNT 3
#define ITEM_COUNT 16
#define WIN_COUNT 4
#define GHOST_COUNT 3

struct TrapPoint {
	float x, z;
};

//struct Point {
//	float x, z;
//};



//void draw_floor(GLuint ShaderProgram, GLuint VBO, GLuint EBO);

void draw_floor(GLuint ShaderProgram, GLuint VBO, GLuint EBO, Pacman* pacman);
void init_wall(Wall walls[], Thorn thorns[], Hole holes[], Deceleration_Trap traps[], WinItem items[], Ghost ghosts[]);
void draw_map(GLuint ShaderProgram,SuperGLuint super, Wall walls[], Thorn thorns[], Hole holes[], Deceleration_Trap traps[], WinItem items[], Ghost ghosts[], Pacman* pacman);
#endif