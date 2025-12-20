#include "errors.h"

#include <iostream>

#include <GL/glew.h>

void printShaderLog(GLuint shader, std::ostream& os) {
	GLint length;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

	if (length > 0) {
		char* log = new char[length];
		glGetShaderInfoLog(shader, length, nullptr, log);
		os << log;
		delete log;
	}
}

void printProgramLog(GLuint program, std::ostream& os) {
	GLint length;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

	if (length > 0) {
		char* log = new char[length];
		glGetProgramInfoLog(program, length, nullptr, log);
		os << log;
		delete log;
	}
}

bool checkOpenGLError(std::ostream& os) {
	bool error_occurred = false;

	GLenum error = glGetError();
	while (error != GL_NO_ERROR) {
		error_occurred = true;
		os << error << '\n';
		error = glGetError();
	}

	return error_occurred;
}