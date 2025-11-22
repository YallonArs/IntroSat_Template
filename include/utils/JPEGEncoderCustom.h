#pragma once

#include <Arduino.h>
#include <JPEGENC.h>
#include <SD.h>

class JPEGEncoderCustom {
private:
	SDClass* _sd;
	JPEGENC jpg;
	static File outFile;
	static void* myOpen(const char* filename);
	static void myClose(JPEGE_FILE* p);
	static int32_t myRead(JPEGE_FILE* p, uint8_t* buffer, int32_t length);
	static int32_t myWrite(JPEGE_FILE* p, uint8_t* buffer, int32_t length);
	static int32_t mySeek(JPEGE_FILE* p, int32_t position);

public:
	JPEGEncoderCustom(SDClass* sd);
	bool encode(String inputFilename, String outputFilename, uint16_t imageWidth, uint16_t imageHeight);
};
