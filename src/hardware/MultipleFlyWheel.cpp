#include "hardware/MultipleFlyWheel.h"

MultipleFlyWheel::MultipleFlyWheel(std::initializer_list<uint8_t> addresses, TwoWire &hi2c)
	: _hi2c(hi2c), _addresses(addresses), _numMotors(addresses.size()) {}

bool MultipleFlyWheel::Init() {
	for (auto address : _addresses) {
		IntroSatLib::MotorFlyWheel motor(_hi2c, address);
		bool status = motor.Init();
		
		if (!status) return false;
	}

	return true;
}

void MultipleFlyWheel::NeedSpeed(int16_t needSpeed) {
	for (auto address : _addresses) {
		IntroSatLib::MotorFlyWheel motor(_hi2c, address);
		motor.NeedSpeed(needSpeed);
	}
}

int16_t MultipleFlyWheel::CurrentSpeed(uint8_t idx) {
	auto it = _addresses.begin();
	std::advance(it, idx);
	
	IntroSatLib::MotorFlyWheel motor(_hi2c, *it);
	return motor.CurrentSpeed();
}

int16_t MultipleFlyWheel::CurrentSpeedAveraged() {
	int32_t totalSpeed = 0;

	for (uint8_t idx = 0; idx < _numMotors; ++idx)
		totalSpeed += CurrentSpeed(idx);

	if (_numMotors == 0) return 0;
	return (int16_t)(totalSpeed / _numMotors);
}
