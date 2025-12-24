#include "render.h"

#include <vector>

#include <GL/glew.h>

#include "animation.h"

Scene::Scene(const std::vector<AnimatedTriangle>& triangles)
	: triangles_(triangles) {
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
}

Scene::~Scene() {
	glDeleteBuffers(1, &vbo_);
	glDeleteVertexArrays(1, &vao_);
}

void Scene::update(float dt) {
	std::vector<glm::vec2> vertices;
	for (auto& triangle : triangles_) {
		auto positions = triangle.getNextPositions(dt);
		vertices.insert(vertices.end(), positions.begin(), positions.end());
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_DYNAMIC_DRAW);
}

void Scene::draw(GLuint program) {
	glUseProgram(program);
	glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(triangles_.size() * 3));
}