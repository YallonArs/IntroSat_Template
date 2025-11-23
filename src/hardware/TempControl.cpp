#include "hardware/TempControl.h"

TempControl::TempControl(String name, Logger logger, GPIOTool &heater) : _name(name), _logger(logger), _heater(heater) {
	_logger.info(name + F(" TempControl initialized"));
}

void TempControl::apply(float current_temp, float target_temp) {
	static bool prevState = false; // false = OFF, true = ON

	bool newState = current_temp < target_temp;
	if (newState != prevState) {
		if (newState) {
			_heater.on();
			_logger.warn(_name + F(" heater turned ON"));
		} else {
			_heater.off();
			_logger.warn(_name + F(" heater turned OFF"));
		}
		prevState = newState;
	}
}

void TempControl::disable() {
	_heater.off();
	_logger.warn(_name + F(" heater disabled"));
}
