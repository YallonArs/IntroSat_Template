#include "hardware/CustomStepper.h"

CustomStepper::CustomStepper(uint8_t dir_pin, uint8_t step_pin, uint8_t enable_pin, uint8_t gear_ratio)
	: _dir_pin(dir_pin), _step_pin(step_pin), _enable_pin(enable_pin), _gear_ratio(gear_ratio) {
	pinMode(dir_pin, OUTPUT);
	pinMode(step_pin, OUTPUT);
	pinMode(enable_pin, OUTPUT);

	digitalWrite(enable_pin, LOW);
}

double CustomStepper::moveByAngle(float angle_deg) {
	if (angle_deg > 0)
		digitalWrite(_dir_pin, !_direction_mode);
	else
		digitalWrite(_dir_pin, _direction_mode);

	uint16_t step_number = abs(angle_deg) / STEP_ANGLE_DEG * _gear_ratio;

	for (uint16_t x = step_number; x > 0; x--) {
		uint16_t delay_time = 3000 - x * (2000 / step_number);

		digitalWrite(_step_pin, HIGH);
		delayMicroseconds(delay_time);
		digitalWrite(_step_pin, LOW);
		delayMicroseconds(delay_time);
	}

	_current_angle_deg += (angle_deg > 0) ? step_number * STEP_ANGLE_DEG /_gear_ratio : -step_number * STEP_ANGLE_DEG/_gear_ratio;
	return _current_angle_deg;
}

double CustomStepper::moveToTarget(float target_deg) {
	float delta = target_deg - _current_angle_deg;
	
	return moveByAngle(delta);
}

void CustomStepper::start(bool dir, uint16_t velocity) {
	digitalWrite(_dir_pin, dir);

	// TODO: implement velocity control
	float t = 3000.;

	PinName step_pin_name = digitalPinToPinName(_step_pin);
	uint32_t frequency = 1000000.00 / (t * 2);
	static uint16_t value = 50; // 50% duty cycle
	static TimerCompareFormat_t resolution = PERCENT_COMPARE_FORMAT;
	
	pwm_start(step_pin_name, frequency, value, resolution);
}

void CustomStepper::stop() {
	pwm_stop(digitalPinToPinName(_step_pin));
}
