#include "hardware/CustomStepperA4988.h"

CustomStepperA4988::CustomStepperA4988(uint8_t steps, uint8_t dir_pin, uint8_t step_pin, uint8_t ms1_pin, uint8_t ms2_pin, uint8_t ms3_pin)
	: A4988(steps, dir_pin, step_pin, ms1_pin, ms2_pin, ms3_pin) {}

double CustomStepperA4988::rotate(double angle) {
	_current_angle_deg += angle;
	_current_angle_deg = fmod(_current_angle_deg, 360.0); // keep it within 0-360
	
	A4988::rotate(angle);

	return _current_angle_deg;
}

double CustomStepperA4988::rotateTo(double angle) {
	double delta = angle - _current_angle_deg;

	// Normalize delta to the range [-180, 180]
	if (delta > 180.0)
		delta -= 360.0;
	else if (delta < -180.0)
		delta += 360.0;
	
	rotate(delta);

	return _current_angle_deg;
}
