#pragma once

#include <Wire.h>

#include <AccelerometerV2.h>

#include "utils/vector3d.h"
#include "utils/Axis.h"

class CustomAccelerometer : private IntroSatLib::AccelerometerV2 {
public:
	CustomAccelerometer(TwoWire &hi2c = Wire);

	vector3d<float> readAcceleration();
	double getInclination(Axis target_axis);
	
	using IntroSatLib::AccelerometerV2::Init;
};
