#include "hardware/GPS.h"

GPSCoord GPSData::baseCoord;

void GPSData::setBaseCoord(GPSCoord base) {
	baseCoord = GPSCoord(base.latitude, base.longitude);
}

// https://chatgpt.com/share/68c2bde3-65c4-8013-91cf-6b9322921e12
double GPSData::distanceToBase() {
	return TinyGPSPlus::distanceBetween(coord.latitude, coord.longitude, baseCoord.latitude, baseCoord.longitude);
}

double GPSData::courseToBase() {
	return TinyGPSPlus::courseTo(coord.latitude, coord.longitude, baseCoord.latitude, baseCoord.longitude);
}

GPSData GPSData::obtainGPSData(TinyGPSPlus &gps) {
	if (gps.location.isUpdated()) {
		GPSCoord newCoord(gps.location.lat(), gps.location.lng(), gps.location.isValid());
		return GPSData(newCoord);
	}
	return GPSData();
}

GPSData &GPSData::operator=(const GPSData &other) {
	this->coord = other.coord;
	return *this;
}
