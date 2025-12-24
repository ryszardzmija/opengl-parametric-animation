#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <memory>
#include <utility>
#include <array>

#include <glm/vec2.hpp>

#include "geometry.h"

class ClosedPlaneCurvePoint {
public:
	ClosedPlaneCurvePoint(std::shared_ptr<const ClosedPlaneCurve> plane_curve, float u, float u_speed)
		: plane_curve_(std::move(plane_curve)), u_(u), u_speed_(u_speed) {}

	glm::vec2 getNextPosition(float dt);

private:
	std::shared_ptr<const ClosedPlaneCurve> plane_curve_;
	float u_;
	float u_speed_;
};

class AnimatedTriangle {
public:
	AnimatedTriangle(std::array<ClosedPlaneCurvePoint, 3> vertices)
		: vertices_(std::move(vertices)) {}

	std::array<glm::vec2, 3> getNextPositions(float dt) {
		return { vertices_[0].getNextPosition(dt), vertices_[1].getNextPosition(dt), vertices_[2].getNextPosition(dt) };
	}

private:
	std::array<ClosedPlaneCurvePoint, 3> vertices_;
};
#endif
