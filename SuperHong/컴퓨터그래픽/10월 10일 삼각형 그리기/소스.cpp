#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm.hpp>
#include <gl/ext.hpp>
#include <gl/gtc/matrix_transform.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "file2buf.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
GLuint complie_shader()
{
	const GLchar* vertexsource = filetobuf("myVertex.glvs");
	const GLchar* fragmentssource = filetobuf("frag.fs");
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexsource, NULL);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR:vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return false;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1, &fragmentssource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR:fragmentShader 컴파일 실패\n" << errorLog << std::endl;
		return false;
	}
	GLuint ShaderProgramID = glCreateProgram();

	glAttachShader(ShaderProgramID, vertexShader);
	glAttachShader(ShaderProgramID, fragmentShader);
	glLinkProgram(ShaderProgramID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);
		std::cerr << "EROOR:shader program연결실패\n" << errorLog << std::endl;
		return false;
	}
	glUseProgram(ShaderProgramID);
	return ShaderProgramID;

}
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}
GLvoid drawScene()
{
	GLchar* vertexsource, *framentsource;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	GLuint ShaderProgramID=complie_shader();
	glUseProgram(ShaderProgramID);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
	glFlush();

}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}
