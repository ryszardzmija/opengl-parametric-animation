#include "render.h"

#include <cmath>

#include <glm/vec2.hpp>

glm::vec2 ClosedPlaneCurvePoint::getNextPosition(float dt) {
	u_ += u_speed_ * dt;
	if (u_ > 1 || u_ < 0) {
		// Normalize the parameter into the [0, 1] interval
		// and ensure periodic behavior
		u_ -= std::floor(u_);
	}
	return plane_curve_->getCartesian(u_);
}