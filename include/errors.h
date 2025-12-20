#ifndef ERRORS_H_
#define ERRORS_H_

#include <iostream>

#include <GL/glew.h>

inline GLint shaderCompilationSucceeded(GLuint shader) {
	GLint comp_status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &comp_status);
	return comp_status;
}

inline GLint programLinkingSucceeded(GLuint program) {
	GLint link_status;
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);
	return link_status;
}

void printShaderLog(GLuint shader, std::ostream& os);
void printProgramLog(GLuint program, std::ostream& os);
bool checkOpenGLError(std::ostream& os);

#endif