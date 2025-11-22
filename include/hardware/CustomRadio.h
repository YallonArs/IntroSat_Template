#pragma once

#include <cstdint>
#include <cc1101.h>

using CC1101::Status;
using CC1101::Radio;

class CustomRadio : private Radio {
public:
	CustomRadio(uint8_t csPin, uint8_t gd0);
	Status begin();
	using Radio::transmit;
	using Radio::receive;
};
