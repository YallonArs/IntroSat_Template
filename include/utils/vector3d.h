#pragma once

#include <initializer_list>

#include "utils/Axis.h"

template <typename T>
struct vector3d {
	T x, y, z;

	// constructors
	vector3d<T>();
	vector3d<T>(std::initializer_list<T> _a);
	vector3d<T>(const vector3d<T> &other);

	T magnitude() const;

	// getter
	T operator[](Axis axis);

	// assignment operators
	vector3d<T> operator=(vector3d<T> _a);
	vector3d<T> operator=(std::initializer_list<T> _a);

	// unary operators
	vector3d<T> operator-();

	// arithmetic operators with another vector3d
	vector3d<T> operator+(vector3d<T> _a);
	vector3d<T> operator+=(vector3d<T> _a);

	vector3d<T> operator-(vector3d<T> _a);
	vector3d<T> operator-=(vector3d<T> _a);

	// arithmetic operators with a scalar
	template <typename T2>
	vector3d<T> operator*(T2 _a);
	template <typename T2>
	vector3d<T> operator*=(T2 _a);

	template <typename T2>
	vector3d<T> operator/(T2 _a);
	template <typename T2>
	vector3d<T> operator/=(T2 _a);

	// cast operator
	template <typename T2>
	operator vector3d<T2>();
};
