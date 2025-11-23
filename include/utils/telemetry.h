#pragma once

#include "hardware/GPS.h"
#include "utils/vector3d.h"

#define DS_AMOUNT 3
#define BUTTONS_AMOUNT 9

struct telemetry {
	float temp_ds[DS_AMOUNT];
	vector3d<float> accel, gyro, mag;
	float temp_mpu, temp_baro;
	float pressure;
	float height_baro;
	GPSData gpsData;
	bool is_heater_motor_on;
	bool is_heater_accum_on;
    bool is_antenna_expanded;
	bool button_states[BUTTONS_AMOUNT];
	float motor1_angle, motor2_angle;
};
