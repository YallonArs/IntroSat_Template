#pragma once

#include <Arduino.h>

#include "hardware/GPIOTool.h"
#include "utils/Logger.h"

class TempControl {
private:
	String _name;
	Logger _logger;
	GPIOTool &_heater;

public:
	TempControl(String controlName, Logger logger, GPIOTool &heater);

	void apply(float currentTemp, float minTemp);
	void disable();
};
