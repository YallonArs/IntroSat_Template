#pragma once

class BaseStepper {
protected:
	double _current_angle_deg = 0.0;

public:
	BaseStepper() = default;

	virtual double rotate(double angle) = 0;
	virtual double rotateTo(double angle) = 0;

	double getCurrentAngle() const { return _current_angle_deg; }
};
