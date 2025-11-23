#pragma once

#include <cstdint>

#include <SD.h>

#define FILE_REWRITE (O_READ | O_WRITE | O_CREAT | O_TRUNC)

double shortestAngleDiff(double target, double current);
double round(double num, uint8_t precision);

enum State {
	Disabled = 0,
	Enabled = 1
};

enum class Axis {
	X,
	Y,
	Z
};
