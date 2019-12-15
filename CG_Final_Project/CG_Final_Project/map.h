#pragma once
#include "Wall.h"
void draw_floor(GLuint ShaderProgram, GLuint VBO, GLuint EBO);

void init_wall();
void draw_wall(GLuint ShaderProgram, GLuint VBO, GLuint EBO, float x, float z, float width, float width2);

void draw_map(GLuint ShaderProgram, GLuint VBO, GLuint EBO);