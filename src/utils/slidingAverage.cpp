#include "utils/slidingAverage.h"

// SLIDING AVERAGE ------------------------

template <uint16_t N>
SlidingAverage<N>::SlidingAverage() : index(0), count(0) {
	for (uint16_t i = 0; i < N; i++)
		samples[i] = 0.0;
}

template <uint16_t N>
void SlidingAverage<N>::update(double _new) {
	samples[index] = _new;

	index = (index + 1) % N;

	if (count < N)
		count++;
}

template <uint16_t N>
double SlidingAverage<N>::get() const {
	double sum = 0.0;
	for (uint16_t i = 0; i < count; i++)
		sum += samples[i];

	return count > 0 ? sum / count : 0.0;
}

template <uint16_t N>
double SlidingAverage<N>::calculate(double _new) {
	update(_new);
	return get();
}

// 3-DIMENSIONAL VERSION ------------------

template <uint16_t N>
SlidingAverage3D<N>::SlidingAverage3D() {}

template <uint16_t N>
void SlidingAverage3D<N>::update(vector3d<double> _new) {
	update(_new.x, _new.y, _new.z);
}

template <uint16_t N>
double SlidingAverage3D<N>::get(Axis axis) const {
	switch (axis) {
		case Axis::X:
			return xAverage.get();
		case Axis::Y:
			return yAverage.get();
		case Axis::Z:
			return zAverage.get();
	}
	return 0.0;
}

template <uint16_t N>
vector3d<double> SlidingAverage3D<N>::get() const {
	return vector3d(
		xAverage.get(),
		yAverage.get(),
		zAverage.get()
	);
}

template <uint16_t N>
vector3d<double> SlidingAverage3D<N>::calculate(vector3d<double> _new) {
	update(_new);
	return get();
}


template class SlidingAverage<5>;
template class SlidingAverage3D<5>;
