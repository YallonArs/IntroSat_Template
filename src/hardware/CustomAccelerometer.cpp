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

vector3d<float> CustomAccelerometer::readAccelerationAveraged() {
	static constexpr uint8_t NUM_SAMPLES = 10;
	vector3d<float> data_sum;

	for (uint8_t i = 0; i < NUM_SAMPLES; i++) {
		vector3d<float> sample = readAcceleration();
		data_sum += sample;
		delay(10);
	}

	return data_sum / NUM_SAMPLES;
}

double CustomAccelerometer::getInclination(Axis target_axis) {
	vector3d<float> accel_data = readAccelerationAveraged();
	double d = accel_data.magnitude();

	double target_axis_value = accel_data[target_axis];
	return degrees(acos(target_axis_value / d));
}
