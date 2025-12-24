#ifndef RENDER_H_
#define RENDER_H_

#include <vector>

#include <GL/glew.h>

#include "animation.h"

class Scene {
public:
	Scene(const std::vector<AnimatedTriangle>& triangles);

	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	~Scene();

	void update(float dt);
	void draw(GLuint program);

private:
	std::vector<AnimatedTriangle> triangles_;
	GLuint vbo_;
	GLuint vao_;
};

#endif