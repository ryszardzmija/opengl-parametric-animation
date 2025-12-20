#ifndef CURVES_H_
#define CURVES_H_

#include <glm/vec2.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/constants.hpp>

class ParametricEllipse {
public:
	ParametricEllipse(glm::vec2 center, float a, float b, float t)
		: center_(center), a_(a), b_(b), t_(t) {
	}

	glm::vec2 getCartesian() const {
		return center_ + glm::vec2{ a_ * glm::cos(t_), b_ * glm::sin(t_) };
	}

	void addIncrement(float increment) {
		t_ += increment;
		if (t_ >= 2 * glm::pi<float>()) {
			t_ -= 2 * glm::pi<float>();
		}
	}

private:
	glm::vec2 center_;
	float a_;
	float b_;
	float t_;
};

class ParametricCircle {
public:
	ParametricCircle(glm::vec2 center, float r, float t)
		: center_(center), r_(r), t_(t) {
	}

	glm::vec2 getCartesian() const {
		return center_ + glm::vec2{ r_ * glm::cos(t_), r_ * glm::sin(t_) };
	}

	void addIncrement(float increment) {
		t_ += increment;
		if (t_ >= 2 * glm::pi<float>()) {
			t_ -= 2 * glm::pi<float>();
		}
	}

private:
	glm::vec2 center_;
	float r_;
	float t_;
};

#endif