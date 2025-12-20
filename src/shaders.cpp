#include "shaders.h"

#include <filesystem>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include "errors.h"

namespace fs = std::filesystem;

RenderingProgram::RenderingProgram(const fs::path& vertex_shader_path, const fs::path& fragment_shader_path)
	: vertex_shader_path_(vertex_shader_path), fragment_shader_path_(fragment_shader_path) {

	std::string vertex_shader_source = readVertexShaderSource();
	std::string fragment_shader_source = readFragmentShaderSource();

	const char* vertex_shader_source_ptr = vertex_shader_source.c_str();
	const char* fragment_shader_source_ptr = fragment_shader_source.c_str();

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex_shader, 1, &vertex_shader_source_ptr, nullptr);
	glShaderSource(fragment_shader, 1, &fragment_shader_source_ptr, nullptr);

	glCompileShader(vertex_shader);
	checkOpenGLError(std::cerr);
	if (shaderCompilationSucceeded(vertex_shader) != GL_TRUE) {
		printShaderLog(vertex_shader, std::cerr);
		exit(EXIT_FAILURE);
	}

	glCompileShader(fragment_shader);
	checkOpenGLError(std::cerr);
	if (shaderCompilationSucceeded(fragment_shader) != GL_TRUE) {
		printShaderLog(fragment_shader, std::cerr);
		exit(EXIT_FAILURE);
	}

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	checkOpenGLError(std::cerr);
	if (programLinkingSucceeded(program) != GL_TRUE) {
		printProgramLog(program, std::cerr);
		exit(EXIT_FAILURE);
	}
}

GLuint RenderingProgram::getProgram() const {
	return program;
}

std::string RenderingProgram::readShaderSource(const fs::path& path) const {
	std::string source;
	std::string line;

	std::ifstream ifs(path);
	while (std::getline(ifs, line)) {
		source.append(line + '\n');
	}

	return source;
}

std::string RenderingProgram::readVertexShaderSource() const {
	return readShaderSource(vertex_shader_path_);
}

std::string RenderingProgram::readFragmentShaderSource() const {
	return readShaderSource(fragment_shader_path_);
}
