#include "hardware/Camera.h"

Camera::Camera(HardwareSerial* _UART) : UART(_UART) {}

void Camera::begin() {
	UART->begin(_baudrate, parity);
	setTimeout(2000);
	
	delay(100);
}

void Camera::setTimeout(uint32_t timeoutMs) {
	_timeoutMs = timeoutMs;
}

int Camera::timedRead() {
    uint32_t start = millis();
    while ((millis() - start) < _timeoutMs) {
        if (UART->available()) {
            int v = UART->read();
            if (v >= 0) return v;
        }
        yield(); // on ESP/Arduino, let system run other tasks
    }
    return -1;
}

// void Camera::waitForBytes(std::initializer_list<uint8_t> bytes, uint16_t length) {
// 	auto it = bytes.begin();
// 	for (uint16_t i = 0; i < length && it != bytes.end(); i++, ++it)
// 		while (UART->read() != *it);
// }

bool Camera::waitForBytes(std::initializer_list<uint8_t> bytes) {
	auto it = bytes.begin();
	for (size_t i = 0; i < bytes.size(); ++i, ++it) {
		int c;
		do {
			c = timedRead();
			if (c < 0) return false; // timeout
		} while (static_cast<uint8_t>(c) != *it);
	}
	return true;
}

void Camera::waitForPreamble() {
	waitForBytes({0xFF, 0xFF, 0x00});
}

void Camera::waitForPostamble() {
	waitForBytes({0x00, 0xFF, 0x00});
}

void Camera::readBytes(uint8_t *buffer, uint16_t length) {
	waitForPreamble();
	UART->readBytes(buffer, length);
	waitForPostamble();
}

bool Camera::capture() {
	UART->write(0x74);

	return waitForBytes({0xFF, 0x00, 0xFF});
}

ImageProperties Camera::getProperties() {
	UART->write(0x70);

	ImageProperties props;
	uint16_t buf_length = sizeof(ImageProperties);

	readBytes(reinterpret_cast<uint8_t*>(&props), buf_length);
	
	return props;
}

Chunk Camera::getNextChunk() {
	UART->write(0x6e);

	Chunk props;
	uint16_t buf_length = sizeof(Chunk);

	readBytes(reinterpret_cast<uint8_t*>(&props), buf_length);

	return props;
}

void Camera::changeImageSize(uint16_t width, uint16_t height) {
	UART->write(0x73);
	UART->write(reinterpret_cast<uint8_t*>(&width), sizeof(width));
	UART->write(reinterpret_cast<uint8_t*>(&height), sizeof(height));
}

void Camera::changeExposure(uint16_t exposure) {
	UART->write(0x65);
	UART->write(reinterpret_cast<uint8_t*>(&exposure), sizeof(exposure));
}
