#pragma once

#include <cstdint>

#include "utils/vector3d.h"
#include "utils/utils.h"

template <uint16_t N>
class SlidingAverage {
private:
	double samples[N];
	uint16_t index;
	uint16_t count;

public:
	SlidingAverage();
	void update(double _new);
	double get() const;
	double calculate(double _new);
};

template <uint16_t N>
class SlidingAverage3D {
private:
	SlidingAverage<N> xAverage;
	SlidingAverage<N> yAverage;
	SlidingAverage<N> zAverage;

public:
	SlidingAverage3D();
	void update(vector3d<double> _new);
	double get(Axis axis) const;
	vector3d<double> get() const;
	vector3d<double> calculate(vector3d<double> _new);
};
