#pragma once

#include <cstdint>

#include "TinyGPSPlus.h"

struct GPSCoord {
	double latitude = 0.0,
		   longitude = 0.0;
	bool valid = false;

	GPSCoord() = default;
	GPSCoord(double latitude, double longitude, bool valid = true) : latitude(latitude), longitude(longitude), valid(valid) {}

	inline GPSCoord &operator=(const GPSCoord &other) {
		latitude = other.latitude;
		longitude = other.longitude;
		valid = other.valid;
		return *this;
	}
};

class GPSData {
private:
	static GPSCoord baseCoord;
	GPSCoord coord;

public:
	GPSData() = default;
	GPSData(GPSCoord coord) : coord(coord) {}

	GPSCoord getCoord() const { return coord; }
	static void setBaseCoord(GPSCoord base);
	double distanceToBase();
	double courseToBase();

	GPSData &operator=(const GPSData &other);

	static GPSData obtainGPSData(TinyGPSPlus &gps);
};
