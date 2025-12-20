#ifndef SHADERS_H_
#define SHADERS_H_

#include <filesystem>
#include <string>

#include <GL/glew.h>

class RenderingProgram {
public:
	RenderingProgram(const std::filesystem::path& vertex_shader_path, const std::filesystem::path& fragment_shader_path);

	GLuint getProgram() const;

private:
	std::string readVertexShaderSource() const;
	std::string readFragmentShaderSource() const;
	std::string readShaderSource(const std::filesystem::path& path) const;

	std::filesystem::path vertex_shader_path_;
	std::filesystem::path fragment_shader_path_;
	GLuint program;
};

#endif