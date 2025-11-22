#include "hardware/OpticalArray.h"

OpticalArray::OpticalArray(TwoWire &hi2c) : i2c(hi2c) {}

bool OpticalArray::Init() {
	for (uint8_t i = 0; i < NUM_OPTICALS; i++)
		if (LightSensor(i2c, addr0 + i).Init())
			return true;

	return false;
}

float OpticalArray::GetLight(uint8_t idx) {
	if (idx >= NUM_OPTICALS)
		return 0.0f;

	uint16_t light = LightSensor(i2c, addr0 + idx).GetLight();
	return lightAverages[idx].calculate(light);
}

void OpticalArray::GetLight(uint16_t output[NUM_OPTICALS]) {
	for (uint8_t i = 0; i < NUM_OPTICALS; i++)
		output[i] = GetLight(i);
}

double OpticalArray::normalizeLightValue(uint16_t light) {
	static const double R_FIXED = 10000.0;	// 10k ohm fixed resistor
	static const double MAX_LIGHT = 2048.0; // maximum light sensor reading (11-bit ADC)
	static const double MAX_VOLTAGE = 3.3;
	static const double COEFF = -1 / 0.372;

	double U = (double)light * (MAX_VOLTAGE / MAX_LIGHT);
	double R_L = R_FIXED * (U / (MAX_VOLTAGE - U));
	double L = pow(R_L, COEFF) * 100000.0; // empirical formula to convert resistance to light intensity in lux
	return L;
}

double OpticalArray::GetLightNormalized(uint8_t idx) {
	uint16_t light = GetLight(idx);
	return normalizeLightValue(light);
}

void OpticalArray::GetLightNormalized(double output[NUM_OPTICALS]) {
	for (uint8_t i = 0; i < NUM_OPTICALS; i++)
		output[i] = GetLightNormalized(i);
}

double OpticalArray::GetLightAngle() {
	// uint16_t L[NUM_OPTICALS];
	// GetLight(L);

	double L[NUM_OPTICALS];
	GetLightNormalized(L);

	double x_comp = L[0] - L[2]; // L1 - L3
	double y_comp = L[1] - L[3]; // L2 - L4

	// small threshold relative to signal to detect ambiguity / symmetry / noise
	const double EPS = 1e-6; // absolute threshold
	const double mag = std::hypot(x_comp, y_comp);
	if (mag < EPS) {
		Serial1.println("Optical readings too weak or ambiguous for angle calculation.");
		return 0.0f;
	}

	double theta = std::atan2(y_comp, x_comp); // radians, -pi..pi
	double theta_deg = theta * 180.0 / M_PI;
	if (theta_deg < 0.0) theta_deg += 360.0;

	return theta_deg;
}
