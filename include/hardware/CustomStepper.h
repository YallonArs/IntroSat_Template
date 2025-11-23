#pragma once

#include <Arduino.h>

#include "hardware/BaseStepper.h"

class CustomStepper : public BaseStepper {
public:
	enum DirectionMode {
		NORMAL = 0,
		REVERSED = 1
	};

protected:
	static constexpr float STEP_ANGLE_DEG = 1.8; // degrees per step

	uint8_t _dir_pin;
	uint8_t _step_pin;
	uint8_t _enable_pin;
	uint8_t _gear_ratio;
	
	DirectionMode _direction_mode = NORMAL;

public:
	CustomStepper(uint8_t dir_pin, uint8_t step_pin, uint8_t enable_pin, uint8_t gear_ratio = 1);

	void setDirection(DirectionMode mode) { _direction_mode = mode; }
	double rotate(double angle_deg) override;
	double rotateTo(double angle_deg) override;

	void start(bool dir, uint16_t velocity = 100);
	void stop();
};
