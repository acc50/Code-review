#pragma once
#include "global.h"
void draw_floor(GLuint ShaderProgram, GLuint VBO, GLuint EBO);
void draw_wall(GLuint ShaderProgram, GLuint VBO, GLuint EBO, float x, float z, float width, float width2);
void draw_At(GLuint ShaderProgram, GLuint VBO, GLuint EBO, float x, float z, float width, float width2);
void draw_map(GLuint ShaderProgram, GLuint VBO, GLuint EBO);