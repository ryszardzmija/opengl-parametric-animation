#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <glm/vec2.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/constants.hpp>

class ClosedPlaneCurve {
public:
	virtual glm::vec2 getCartesian(float u) const = 0;

	virtual ~ClosedPlaneCurve() = default;
};

class Ellipse : public ClosedPlaneCurve {
public:
	Ellipse(glm::vec2 center, float a, float b)
		: center_(center), a_(a), b_(b) {}

	glm::vec2 getCartesian(float u) const override {
		float theta = 2 * glm::pi<float>() * u;
		return center_ + glm::vec2{ a_ * glm::cos(theta), b_ * glm::sin(theta) };
	}

	static Ellipse circle(glm::vec2 center, float r) {
		return Ellipse(center, r, r);
	}

private:
	glm::vec2 center_;
	float a_;
	float b_;
};

#endif