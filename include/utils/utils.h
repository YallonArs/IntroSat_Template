#pragma once

#include <cstdint>

#define FILE_REWRITE (O_READ | O_WRITE | O_CREAT | O_TRUNC)

double shortestAngleDiff(double target, double current);
double round(double num, uint16_t precision);
