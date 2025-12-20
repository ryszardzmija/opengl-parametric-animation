#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "shaders.h"
#include "curves.h"

void init() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void display(GLuint program) {
	static GLuint apex_loc = glGetUniformLocation(program, "apex");
	static GLuint base1_loc = glGetUniformLocation(program, "base1");
	static GLuint base2_loc = glGetUniformLocation(program, "base2");

	static ParametricEllipse base1_ellipse({ 0.0f, 0.0f }, 0.25f, 0.12f, 0.0f);
	static ParametricEllipse base2_ellipse({ 0.0f, 0.0f }, 0.25f, 0.12f, glm::pi<float>());
	static ParametricCircle apex_circle({ 0.0f, 0.0f }, 0.5f, glm::pi<float>() / 2);

	constexpr float apex_inc = glm::radians<float>(2.0);
	constexpr float base1_inc = glm::radians<float>(1.0);
	constexpr float base2_inc = glm::radians<float>(1.0);

	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);

	base1_ellipse.addIncrement(base1_inc);
	base2_ellipse.addIncrement(base2_inc);
	apex_circle.addIncrement(apex_inc);

	glm::vec2 base1_position = base1_ellipse.getCartesian();
	glm::vec2 base2_position = base2_ellipse.getCartesian();
	glm::vec2 apex_position = apex_circle.getCartesian();

	glProgramUniform2f(program, base1_loc, base1_position.x, base1_position.y);
	glProgramUniform2f(program, base2_loc, base2_position.x, base2_position.y);
	glProgramUniform2f(program, apex_loc, apex_position.x, apex_position.y);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main() {
	if (glfwInit() != GLFW_TRUE) {
		std::cerr << "Error initializing GLFW. Aborting...\n";
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Triangle with Vertices on Ellipses", nullptr, nullptr);
	if (!window) {
		std::cerr << "Error creating a window with an OpenGL context initialized. Aborting...\n";
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Error initializing GLEW. Aborting...\n";
		exit(EXIT_FAILURE);
	}

	constexpr const char* vertex_shader_path = "shaders/basic.vert";
	constexpr const char* fragment_shader_path = "shaders/basic.frag";
	RenderingProgram rendering_program(vertex_shader_path, fragment_shader_path);

	init();

	while (!glfwWindowShouldClose(window)) {
		display(rendering_program.getProgram());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}