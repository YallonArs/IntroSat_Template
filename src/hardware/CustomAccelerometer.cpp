#include "hardware/CustomAccelerometer.h"

CustomAccelerometer::CustomAccelerometer(TwoWire &hi2c)
	: IntroSatLib::AccelerometerV2(hi2c) {}

vector3d<float> CustomAccelerometer::readAcceleration() {
	vector3d<float> data;

	data.x = X();
	data.y = Y();
	data.z = Z();

	return data;
}

double CustomAccelerometer::getInclination(Axis target_axis) {
	vector3d<float> accel_data = readAcceleration();
	double d = accel_data.magnitude();

	double target_axis_value = accel_data[target_axis];
	return degrees(acos(target_axis_value / d));
}
