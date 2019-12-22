#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm.hpp>
#include <gl/ext.hpp>
#include <gl/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <Windows.h>
#include <stdio.h>
#include <float.h>
#include "file2buf.h"
#include "Pacman.h"


struct SuperGLuint{

	GLuint VBO, EBO, ConVBO, ConEBO, SVBO, SNVBO;
};
extern int itemID[4];
	

enum EViewPoint
{
	
	E_DEFAULT_VIEW=0,E_TOP_VIEW
};