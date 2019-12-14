#pragma once
#include "global.h"
void draw_floor(GLuint ShaderProgram, GLuint VBO, GLuint EBO);
void draw_wall(GLuint ShaderProgram, GLuint VBO, GLuint EBO, float x, float z,float width);

void draw_map(GLuint ShaderProgram, GLuint VBO, GLuint EBO);