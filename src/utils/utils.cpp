#include "utils/utils.h"

#include <cmath>

double shortestAngleDiff(double target, double current) {
	double diff = target - current;
	while (diff > 180.0) diff -= 360.0;
	while (diff < -180.0) diff += 360.0;
	return diff;
}

double round(double num, uint8_t precision) {
	return std::round(num * pow(10, precision)) / pow(10, precision);
}
