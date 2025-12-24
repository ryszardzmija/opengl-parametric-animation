#include <iostream>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "shaders.h"
#include "render.h"
#include "animation.h"
#include "geometry.h"

RenderingProgram getRenderingProgram() {
	constexpr const char* vertex_shader_path = "shaders/basic.vert";
	constexpr const char* fragment_shader_path = "shaders/basic.frag";
	return RenderingProgram(vertex_shader_path, fragment_shader_path);
}

Scene getScene() {
	std::shared_ptr<const ClosedPlaneCurve> base_ellipse = std::make_shared<const Ellipse>(glm::vec2(0.0f, 0.0f), 0.25f, 0.125f);
	std::shared_ptr<const ClosedPlaneCurve> apex_circle = std::make_shared<const Ellipse>(Ellipse::circle({ -0.25f, 0.0f }, 0.25f));

	ClosedPlaneCurvePoint base_1(base_ellipse, 0.0f, 0.25f);
	ClosedPlaneCurvePoint base_2(base_ellipse, 0.5f, 0.25f);
	ClosedPlaneCurvePoint apex(apex_circle, 0.0f, 0.125f);

	AnimatedTriangle triangle({ base_1, base_2, apex });

	return Scene({ triangle });
}

void display(GLuint program, Scene& scene, float dt) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	scene.update(dt);
	scene.draw(program);
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

	RenderingProgram rendering_program = getRenderingProgram();
	Scene scene = getScene();

	double last_frame_time = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		float dt = static_cast<float>(glfwGetTime() - last_frame_time);
		last_frame_time += dt;
		display(rendering_program.getProgram(), scene, dt);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}