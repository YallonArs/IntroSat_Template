#pragma once

#include <Wire.h>
#include <LightSensor.h>

#include "utils/slidingAverage.h"

using IntroSatLib::LightSensor;

class OpticalArray {
private:
	static constexpr uint8_t NUM_OPTICALS = 4;
	static constexpr uint8_t addr0 = 0x50;
	SlidingAverage<5> lightAverages[NUM_OPTICALS];
	TwoWire &i2c;

public:
	OpticalArray(TwoWire &hi2c = Wire);
	bool Init();
	float GetLight(uint8_t idx);
	void GetLight(uint16_t output[NUM_OPTICALS]);
	
	double normalizeLightValue(uint16_t light);
	
	double GetLightNormalized(uint8_t idx);
	void GetLightNormalized(double output[NUM_OPTICALS]);
	
	double GetLightAngle(); // in degrees
};
