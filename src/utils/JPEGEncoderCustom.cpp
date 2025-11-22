#include "utils/JPEGEncoderCustom.h"

File JPEGEncoderCustom::outFile;

JPEGEncoderCustom::JPEGEncoderCustom(SDClass *sd) : _sd(sd) {}

void *JPEGEncoderCustom::myOpen(const char *filename) {
	outFile = SD.open(filename, FILE_WRITE);
	return (void *)&outFile;
}

void JPEGEncoderCustom::myClose(JPEGE_FILE *p) {
	File *f = (File *)p->fHandle;
	if (f) f->close();
}

int32_t JPEGEncoderCustom::myRead(JPEGE_FILE *p, uint8_t *buffer, int32_t length) {
	File *f = (File *)p->fHandle;
	return f->read(buffer, length);
}

int32_t JPEGEncoderCustom::myWrite(JPEGE_FILE *p, uint8_t *buffer, int32_t length) {
	File *f = (File *)p->fHandle;
	return f->write(buffer, length);
}

int32_t JPEGEncoderCustom::mySeek(JPEGE_FILE *p, int32_t position) {
	File *f = (File *)p->fHandle;
	return f->seek(position);
}

bool JPEGEncoderCustom::encode(String inputFilename, String outputFilename, uint16_t imageWidth, uint16_t imageHeight) {
	// Serial.println("JPEGENC raw->jpg encoder start");

	File inFile = _sd->open(inputFilename.c_str(), FILE_READ);
	if (!inFile) {
		// Serial.print("Unable to open input file: ");
		// Serial.println(inputFilename);
		return false;
	}

	uint32_t expectedSize = (uint32_t)imageWidth * (uint32_t)imageHeight;
	if ((uint32_t)inFile.size() < expectedSize) {
		// Serial.print("Warning: input file smaller than width*height (expected ");
		// Serial.print(expectedSize);
		// Serial.println(")");
	}

	int rc = jpg.open(outputFilename.c_str(), myOpen, myClose, myRead, myWrite, mySeek);
	if (rc != JPEGE_SUCCESS) {
		// Serial.print("jpg.open failed: ");
		// Serial.println(rc);
		inFile.close();
		return false;
	}

	JPEGENCODE enc;
	rc = jpg.encodeBegin(&enc, imageWidth, imageHeight, JPEGE_PIXEL_GRAYSCALE, JPEGE_SUBSAMPLE_444, JPEGE_Q_HIGH);
	if (rc != JPEGE_SUCCESS) {
		// Serial.print("encodeBegin failed: ");
		// Serial.println(rc);
		inFile.close();
		jpg.close();
		return false;
	}

	int mcu_w = enc.cx;
	int mcu_h = enc.cy;
	int mcuSize = mcu_w * mcu_h;
	if (mcuSize > 256) {
		// Serial.println("MCU too large for static buffer");
		inFile.close();
		jpg.close();
		return false;
	}
	uint8_t ucMCU[256];

	int mcusX = (imageWidth + mcu_w - 1) / mcu_w;
	int mcusY = (imageHeight + mcu_h - 1) / mcu_h;

	// Serial.print("Encoding ");
	// Serial.print(imageWidth);
	// Serial.print("x");
	// Serial.print(imageHeight);
	// Serial.print(" MCU ");
	// Serial.print(mcu_w);
	// Serial.print("x");
	// Serial.println(mcu_h);

	for (int my = 0; my < mcusY; my++) {
		for (int mx = 0; mx < mcusX; mx++) {
			for (int row = 0; row < mcu_h; row++) {
				int srcY = my * mcu_h + row;
				int dstOffset = row * mcu_w;
				if (srcY >= imageHeight) {
					for (int c = 0; c < mcu_w; c++) ucMCU[dstOffset + c] = 0;
					continue;
				}

				int srcX = mx * mcu_w;
				if (srcX >= imageWidth) {
					for (int c = 0; c < mcu_w; c++) ucMCU[dstOffset + c] = 0;
					continue;
				}

				int available = imageWidth - srcX;
				int toRead = (available > mcu_w) ? mcu_w : available;
				uint32_t pos = (uint32_t)srcY * (uint32_t)imageWidth + (uint32_t)srcX;
				if (!inFile.seek(pos)) {
					// Serial.print("Seek failed to ");
					// Serial.println(pos);
					inFile.close();
					jpg.close();
					return false;
				}
				int got = inFile.read(&ucMCU[dstOffset], toRead);
				if (got != toRead) {
					for (int c = got; c < toRead; c++) ucMCU[dstOffset + c] = 0;
				}
				for (int c = toRead; c < mcu_w; c++) ucMCU[dstOffset + c] = 0;
			}
			rc = jpg.addMCU(&enc, ucMCU, mcu_w);
			if (rc != JPEGE_SUCCESS) {
				// Serial.print("addMCU failed: ");
				// Serial.println(rc);
				inFile.close();
				jpg.close();
				return false;
			}
		}
	}

	int outSize = jpg.close();
	inFile.close();
	Serial.print("JPEG saved to ");
	Serial.print(outputFilename);
	Serial.print(" size=");
	Serial.println(outSize);

	return true;
}
