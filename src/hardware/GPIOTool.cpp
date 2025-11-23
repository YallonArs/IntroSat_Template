#include <Arduino.h>

#include "hardware/GPIOTool.h"

GPIOTool::GPIOTool(uint16_t pin, bool inverted) : _pin(pin), _inverted(inverted) {
	// if (_pin == 0) return; // no pin set

	pinMode(_pin, OUTPUT);
	off();
}

void GPIOTool::on() {
	digitalWrite(_pin, _inverted ? LOW : HIGH);
	_state = Enabled;
}

void GPIOTool::off() {
	digitalWrite(_pin, _inverted ? HIGH : LOW);
	_state = Disabled;
}

void GPIOTool::toggle() {
	if (_state == Enabled) off();
	else on();
}

void GPIOTool::pulse(uint32_t delayMs) {
	on();
	delay(delayMs);
	off();
}

void GPIOTool::startPWM(uint16_t frequency, uint8_t dutyCycle) const {
	pwm_start(
		digitalPinToPinName(_pin), 
		frequency, 
		dutyCycle, 
		PERCENT_COMPARE_FORMAT
	);
}

void GPIOTool::stopPWM() const {
	pwm_stop(digitalPinToPinName(_pin));
}

bool GPIOTool::isOn() const {
	return _state == Enabled;
}
