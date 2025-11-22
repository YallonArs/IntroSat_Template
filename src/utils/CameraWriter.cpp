#include <Arduino.h>
#include <SD.h>

#include "utils/CameraWriter.h"
#include "utils/utils.h"

CameraWriter::CameraWriter(Camera& camera, SDClass* sd)
	: _camera(camera), _sd(sd) {}

void CameraWriter::captureAndSaveImage(String filename) {
	ImageProperties props = _camera.getProperties();

	Serial1.println("Capturing image...");
	_camera.capture();
	Serial1.println("Image captured.");
	Serial1.println("Saving image to SD card...");

	File imageFile = _sd->open(filename, FILE_REWRITE);
	if (!imageFile) {
		Serial1.println("Error opening " + filename + " for writing");
		return;
	}

	for (uint16_t i = 0; i < props.numberOfChunks; i++) {
		Chunk chunk = _camera.getNextChunk();
		imageFile.write(chunk.payload, chunk.payloadLength);
	}
	imageFile.close();
	Serial1.println("Image saved to SD card.");

	Serial1.print("Captured image: ");
	Serial1.print(props.width);
	Serial1.print("x");
	Serial1.print(props.height);
	Serial1.println(" pixels.");
}
