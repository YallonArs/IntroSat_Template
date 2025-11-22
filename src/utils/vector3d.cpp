#include "utils/vector3d.h"

template <typename T>
vector3d<T>::vector3d() {
	x = 0;
	y = 0;
	z = 0;
}

template <typename T>
vector3d<T>::vector3d(std::initializer_list<T> _a) {
	x = _a.begin()[0];
	y = _a.begin()[1];
	z = _a.begin()[2];
}

template <typename T>
vector3d<T>::vector3d(const vector3d<T> &other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

template <typename T>
T vector3d<T>::magnitude() const {
	return sqrt(sq(x) + sq(y) + sq(z));
}

template <typename T>
T vector3d<T>::operator[](Axis axis) {
	switch (axis) {
		case Axis::X:
			return x;
		case Axis::Y:
			return y;
		case Axis::Z:
			return z;
	}
	return 0;
}

template <typename T>
vector3d<T> vector3d<T>::operator=(vector3d<T> _a) {
	x = _a.x;
	y = _a.y;
	z = _a.z;
	return *this;
}

template <typename T>
vector3d<T> vector3d<T>::operator=(std::initializer_list<T> _a) {
	x = _a.begin()[0];
	y = _a.begin()[1];
	z = _a.begin()[2];
	return *this;
}

template <typename T>
vector3d<T> vector3d<T>::operator-() {
	return vector3d<T>(-x, -y, -z);
}

template <typename T>
vector3d<T> vector3d<T>::operator+(vector3d<T> _a) {
	return vector3d<T>(x + _a.x, y + _a.y, z + _a.z);
}

template <typename T>
vector3d<T> vector3d<T>::operator+=(vector3d<T> _a) {
	*this = (*this) + _a;
	return *this;
}

template <typename T>
vector3d<T> vector3d<T>::operator-(vector3d<T> _a) {
	return *this + -_a;
}

template <typename T>
vector3d<T> vector3d<T>::operator-=(vector3d<T> _a) {
	*this = (*this) - _a;
	return *this;
}

template <typename T>
template <typename T2>
vector3d<T> vector3d<T>::operator*(T2 _a) {
	return vector3d<T>(x * _a, y * _a, z * _a);
}

template <typename T>
template <typename T2>
vector3d<T> vector3d<T>::operator*=(T2 _a) {
	*this = (*this) * _a;
	return *this;
}

template <typename T>
template <typename T2>
vector3d<T> vector3d<T>::operator/(T2 _a) {
	return *this * (1 / _a);
}

template <typename T>
template <typename T2>
vector3d<T> vector3d<T>::operator/=(T2 _a) {
	*this = (*this) / _a;
	return *this;
}

template <typename T>
template <typename T2>
vector3d<T>::operator vector3d<T2>() {
	return vector3d<T2>(
		static_cast<T2>(x),
		static_cast<T2>(y),
		static_cast<T2>(z)
	);
}
