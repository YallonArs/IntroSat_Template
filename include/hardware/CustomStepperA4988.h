#pragma once

#include <Arduino.h>
#include "A4988.h"

#include "hardware/BaseStepper.h"

class CustomStepperA4988 : protected A4988, public BaseStepper {
public:
	CustomStepperA4988(uint8_t steps, uint8_t dir_pin, uint8_t step_pin, uint8_t ms1_pin, uint8_t ms2_pin, uint8_t ms3_pin);

	double rotate(double angle) override;
	double rotateTo(double angle) override;
};
