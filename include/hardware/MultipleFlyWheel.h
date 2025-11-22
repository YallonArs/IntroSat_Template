#pragma once

#include <Wire.h>
#include <cstdint>
#include <initializer_list>

#include <MotorFlyWheel.h>

class MultipleFlyWheel {
private:
	TwoWire &_hi2c;
	std::initializer_list<uint8_t> _addresses;
	uint8_t _numMotors;
public:
	MultipleFlyWheel(std::initializer_list<uint8_t> addresses, TwoWire &hi2c = Wire);

	bool Init();
	void NeedSpeed(int16_t needSpeed);
	int16_t CurrentSpeed(uint8_t idx);
	int16_t CurrentSpeedAveraged();
};
