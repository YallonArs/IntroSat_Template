#pragma once

#include <Arduino.h>
// #include <cstdint>
#include <initializer_list>

struct ImageProperties {
	uint16_t height, width;
	uint16_t vStart, hStart;
	uint16_t colorspace; // not using
	uint16_t exposure;
	uint32_t length;
	uint16_t numberOfChunks;
};

struct Chunk {
	uint16_t chunkID, payloadLength;
	bool isLastChunk;
	uint8_t payload[240];
	uint8_t checksum;
};

class Camera {
protected:
	const uint32_t _baudrate = 230400;
	const uint8_t parity = SERIAL_8N1;

	HardwareSerial *UART;
	uint32_t _timeoutMs;

	int timedRead();
	bool waitForBytes(std::initializer_list<uint8_t> bytes);
	void waitForPreamble();
	void waitForPostamble();
	void readBytes(uint8_t *buf, uint16_t length);

public:
	Camera(HardwareSerial *_UART);

	void setTimeout(uint32_t timeoutMs);

	void begin();
	bool capture();
	ImageProperties getProperties();
	Chunk getNextChunk();
	void changeImageSize(uint16_t width, uint16_t height);
	void changeExposure(uint16_t exposure);
};
